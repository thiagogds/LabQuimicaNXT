#include "cube.h"
#include "app.h"
#include "substance.h"
#include "calculators.h"

//########### Constructors ############
CubePipete::CubePipete(CubeID cube, App* app) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);
}

CubeSubstance::CubeSubstance(CubeID cube, App* app) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);

    substances[0] = &hcl;
    substances[1] = &hbr;
    substances[2] = &naoh;
    substances[3] = &koh;
}

CubeBecher::CubeBecher(CubeID cube, App* app) : dropTicker(9), liquidTicker(7.5) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);

    move = false;

    LiquidAnimation liquidAnim = {0, 0, false};
    DropAnimation dropAnim = {0, false};

    SubstanceVolumeWrapper hclWrapper = {&hcl,0};
    SubstanceVolumeWrapper hbrWrapper = {&hbr, 0};
    SubstanceVolumeWrapper naohWrapper = {&naoh, 0};
    SubstanceVolumeWrapper kohWrapper = {&koh, 0};

    substances[0] = hclWrapper;
    substances[1] = hbrWrapper;
    substances[2] = naohWrapper;
    substances[3] = kohWrapper;

    SubstanceVolumeWrapper mixedWrapper = {&mixedSubstance, 0};

}

CubePhIndicator::CubePhIndicator(CubeID cube, App* app) : ticker(1){
    mCube = cube;
    mApp = app;
    vid.attach(cube);

    ph= 0.0f;
    calculateOn = false;
}

//########### Inits #################
void CubePipete::init(){
    vid.initMode(BG0_SPR_BG1);

    const auto &pipete = vid.sprites[0];
    pipete.setImage(Pipete, 0);
    pipete.move(0,0);
}

void CubeSubstance::init(){
    vid.initMode(BG0_SPR_BG1);
    const auto &substance = vid.sprites[0];
    substance.setImage(Substances, activeSubstance);
    substance.move(0,0);
}

void CubeBecher::init(){
    vid.initMode(BG0_SPR_BG1);
    vid.bg0.image(vec(0,0), Background);

    const auto &becher = vid.sprites[0];
    const auto &liquid = vid.sprites[1];
    const auto &drop = vid.sprites[2];

    becher.setImage(FlaskBkg, 0);
    becher.move(0,0);

    liquid.setImage(Liquid, 0);
    //Posição inicial do liquido, para não aparecer na tela
    //Se a imagem mudar tem que mudar isso
    liquid.move(0,80);
    liquidAnim.lastY = liquid.y();

    drop.setImage(Drop, dropAnim.frame);
    //Não entendemos por que o eixo Y é -6 e não -32.
    drop.move(64 - (drop.width()/2),-6);
}

void CubeBecher::animate(float dt){
    if(move){
        const auto &liquid = vid.sprites[1];
        const auto &drop = vid.sprites[2];

        for(int t = dropTicker.tick(dt); t ; t--) {
            //Teste para saber quando a gota chegou no liquido
            //Se a posição inicial do liquido mudar tem que alterar o erro do lastY
            if (drop.y() - 32 < liquidAnim.lastY + 8) {
                drop.move(drop.x(), drop.y() + 10);//Velocidade que a gota desce
                dropAnim.frame = (dropAnim.frame + 1) % Drop.numFrames();
                drop.setImage(Drop, dropAnim.frame);
            } else {
                dropAnim.animated = true;
                if (liquidAnim.animated) {
                    liquidAnim.animated = false;
                }
            }
        }


        if (dropAnim.animated) {
            for(int t = liquidTicker.tick(dt); t ; t--) {
                if(liquidAnim.frame < Liquid.numFrames()){
                    liquid.setImage(Liquid, liquidAnim.frame);
                    liquidAnim.frame++;

                    if(liquid.y() > 0){
                        liquid.move(liquid.x(), liquid.y() - 5)//velocidade que o liquido sobe;
                    }
                } else {
                    liquidAnim.frame = 0;
                    liquid.setImage(Liquid, liquidAnim.frame);
                    liquidAnim.lastY = liquid.y();
                    liquidAnim.animated = true;
                    drop.move(drop.x(), -6);
                    dropAnim.animated = false;
                    move = false;
                }
            }
        }
    }
}

void CubePhIndicator::init(){
    vid.initMode(BG0_ROM);

    String<20> str;
    str << "I am cube\n";
    str << "pH Indicator\n\n";
    vid.bg0rom.text(vec(1,2), str);
}

//######## Get/Set/Others ##############

Substance* CubeSubstance::getCurrentSubstance() {
    return substances[activeSubstance];
}

bool CubePipete::isSameSubstance(Substance* substance){
    if(currentSubstance){
        if(currentSubstance == substance){
            return 1;
        }
        return 0;
    }
    else {
        return 1;
    };
}

void CubeBecher::printSubstance(unsigned index) {
    int line = 4 + index;
    vid.bg0rom.text(vec(1, line), "                 ");
    String<20> substanceNameVolume;
    substanceNameVolume << substances[index].substance->name << ": " <<  FixedFP(substances[index].volume, 1, 5);
    vid.bg0rom.text(vec(1, line), substanceNameVolume);
}

void CubeBecher::addSubstance(Substance* substance, float volume) {
    for(unsigned i = 0 ; i < 4 ; i++) {
        if(substances[i].substance->name == substance->name) {
            substances[i].volume += volume;
            Calculator::mixTwoSubstances(mApp->cubeBecher, i);
            move = true;
            break;
        }
    }
}

//######## onTouch Events ############
void CubeSubstance::rotate() {
    activeSubstance = (activeSubstance + 1) % 4;
}

void CubeSubstance::onTouch(unsigned id) {
    CubeID cube(id);

    if(cube.isTouching()){
        rotate();
        const auto &substance = vid.sprites[0];
        substance.setImage(Substances, activeSubstance);
    }
}
void CubePipete::onTouch(unsigned id) {
    CubeID cube(id);
    Substance* connectedSubstance = mApp->cubeSubstance->getCurrentSubstance();
    float currentVolume;

    if(cube.isTouching()){
        if(connectedToSubstance && isSameSubstance(connectedSubstance)){
            currentVolume = volume + GET_VOLUME;
            if(currentVolume <= MAX_VOLUME) {
                volume += GET_VOLUME;

                //vid.bg0rom.text(vec(1,4), "                  ");

                String<30> str;
                str << "Volume: " << FixedFP(volume, 1, 5);
                //vid.bg0rom.text(vec(1,4), str);

                currentSubstance = connectedSubstance;
                //vid.bg0rom.text(vec(1,5), "                  ");
                //vid.bg0rom.text(vec(1,5), currentSubstance->name);
            }
        } else if (connectedToBecher && currentSubstance) {
            volume -= SET_VOLUME;

            mApp->cubeBecher->addSubstance(currentSubstance, SET_VOLUME);

            if(volume < 0){
                volume = 0.0f;
                currentSubstance = 0;
                //vid.bg0rom.text(vec(1,5), "                  ");
            }

            String<30> str;
            str << "Volume: " << FixedFP(volume, 1, 5);
            //vid.bg0rom.text(vec(1,4), str);
        }
    }
}

void CubePhIndicator::calculate(float dt) {
    for(int t = ticker.tick(dt); t ; t--) {
        if(calculateOn) {
            ph = Calculator::calculatePh(mApp->cubeBecher);

            vid.bg0rom.text(vec(1,5), "             ");
            vid.bg0rom.text(vec(1,6), "             ");
            String<20> str;
            str << "pH: " << FixedFP(ph, 2, 3) << "\n";
            str << "M: " <<  FixedFP(mApp->cubeBecher->mixedSubstance.molar, 2, 3) << "\n";
            vid.bg0rom.text(vec(1,5), str);


        }
    }
}

//######## onNeighborAdd Events ############

void CubePipete::onNeighborAdd(unsigned pipeteID,
                               unsigned pipeteSide,
                               unsigned neighborID,
                               unsigned neighborSide){
    if(neighborID == 1 && neighborSide == TOP && pipeteSide == BOTTOM){
        connectedToSubstance = true;
    }
    if(neighborID == 2 && neighborSide == TOP && pipeteSide == BOTTOM){
        connectedToBecher = true;
    }
}

void CubePhIndicator::onNeighborAdd(unsigned indicatorID,
                                    unsigned indicatorSide,
                                    unsigned neighborID,
                                    unsigned neighborSide){
    calculateOn = true;
}

//######## onNeighborRemove Events ############

void CubePipete::onNeighborRemove(unsigned pipeteID,
                               unsigned pipeteSide,
                               unsigned neighborID,
                               unsigned neighborSide){
    if(connectedToSubstance){
        connectedToSubstance = false;
    }

    if(connectedToBecher){
        connectedToBecher = false;
    }

}

void CubePhIndicator::onNeighborRemove(unsigned indicatorID,
                                       unsigned indicatorSide,
                                       unsigned neighborID,
                                       unsigned neighborSide){
    calculateOn = false;
}

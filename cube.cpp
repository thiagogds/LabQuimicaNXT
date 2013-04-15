#include "cube.h"
#include "app.h"
#include "substance.h"
#include "calculators.h"

//########### Constructors ############
CubePipete::CubePipete(CubeID cube, App* app)
    : liquidTicker(7.5), move(false), getLiquid(false),
      textSpeed(0.2f), GET_VOLUME(0.0050f), MAX_VOLUME(0.0100f),
      SET_VOLUME(0.0005f), volume(0.0f), currentSubstance(0),
      connectedToSubstance(false), connectedToBecher(false){
    mCube = cube;
    mApp = app;
    vid.attach(cube);
    motion[cube].attach(cube);

    static Float2 text;
    static Float2 textTarget;
}

CubeSubstance::CubeSubstance(CubeID cube, App* app)
    : hcl("HCl", 1.0f, 1),
      hcl01("HCl01", 0.1f, 1),
      hbr("HBr", 1.0f, 1),
      hbr005("HBr005", 0.05f, 1),
      naoh("NaOH", 1.0f, 1),
      naoh01("NaOH01", 0.1f, 1),
      koh("KOH", 1.0f, 1),
      koh005("KOH005", 0.05f, 1),
      h2o("H2O", 0.0f, 0, 0) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);
    motion[cube].attach(cube);

    substances[0] = &hcl;
    substances[1] = &hcl01;
    substances[2] = &hbr;
    substances[3] = &hbr005;
    substances[4] = &naoh;
    substances[5] = &naoh01;
    substances[6] = &koh;
    substances[7] = &koh005;
    substances[8] = &h2o;


    static unsigned activeSubstance;
}

CubeBecher::CubeBecher(CubeID cube, App* app)
    : dropTicker(9), liquidTicker(7.5), move(false),
      textSpeed(0.2f), mixedSubstance("", 0.0f, 0, 0){
    mCube = cube;
    mApp = app;
    vid.attach(cube);
    motion[cube].attach(cube);

    static Substance hcl = Acid("HCl", 1.0f, 1);
    static Substance hcl01 = Acid("HCl01", 0.1f, 1);
    static Substance hbr = Acid("HBr", 1.0f, 1);
    static Substance hbr005 = Acid("HBr005", 0.05f, 1);
    static Substance naoh = Base("NaOH", 1.0f, 1);
    static Substance naoh01 = Base("NaOH01", 0.1f, 1);
    static Substance koh = Base("KOH", 1.0f, 1);
    static Substance koh005 = Base("KOH005", 0.05f, 1);
    static Substance h2o = Substance("H2O", 0.0f, 0, 0);

    static SubstanceVolumeWrapper hclWrapper = {&hcl,0};
    static SubstanceVolumeWrapper hcl01Wrapper = {&hcl01,0};
    static SubstanceVolumeWrapper hbrWrapper = {&hbr, 0};
    static SubstanceVolumeWrapper hbr005Wrapper = {&hbr005, 0};
    static SubstanceVolumeWrapper naohWrapper = {&naoh, 0};
    static SubstanceVolumeWrapper naoh01Wrapper = {&naoh01, 0};
    static SubstanceVolumeWrapper kohWrapper = {&koh, 0};
    static SubstanceVolumeWrapper koh005Wrapper = {&koh005, 0};
    static SubstanceVolumeWrapper h2oWrapper = {&h2o, 0};

    substances[0] = hclWrapper;
    substances[1] = hcl01Wrapper;
    substances[2] = hbrWrapper;
    substances[3] = hbr005Wrapper;
    substances[4] = naohWrapper;
    substances[5] = naoh01Wrapper;
    substances[6] = kohWrapper;
    substances[7] = koh005Wrapper;
    substances[8] = h2oWrapper;

    static SubstanceVolumeWrapper mixedWrapper = {&mixedSubstance, 0};

}

CubePhIndicator::CubePhIndicator(CubeID cube, App* app) : ticker(1){
    mCube = cube;
    mApp = app;
    vid.attach(cube);
    motion[cube].attach(cube);

    static float ph = 0.0f;
    static bool calculateOn = false;
}

//########### Inits #################
void CubePipete::init(){
    vid.initMode(BG0_SPR_BG1);
    vid.bg0.image(vec(0,0), Background);
    vid.bg1.setMask(BG1Mask::filled(vec(5,14), vec(4,2)));
    vid.bg1.text(vec(5,14), Font, "    ");

    const auto &pipete = vid.sprites[0];
    const auto &liquid = vid.sprites[1];

    pipete.setImage(Pipete, 0);
    pipete.move(0,0);

    liquid.setImage(Liquid, 0);
    //Posição inicial do liquido, para não aparecer na tela
    //Se a imagem mudar tem que mudar isso
    liquid.move(0,72);
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

    vid.bg1.setMask(BG1Mask::filled(vec(5,14), vec(4,2)));
    vid.bg1.text(vec(5,14), Font, "    ");

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

void CubePhIndicator::init(){
    vid.initMode(BG0_SPR_BG1);
    vid.bg0.image(vec(0,0), Ph);

    const auto &calculator = vid.sprites[0];

    // Allocate 16x2 tiles on BG1 for text at the bottom of the screen
    vid.bg1.setMask(BG1Mask::filled(vec(5,12), vec(8,2)));

    calculator.setImage(Pointer, 0);
    calculator.move(0,72);

    vid.bg1.text(vec(5,12), Font, "ph: 0.00");
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

void CubePipete::writeText(const char *str) {
    vid.bg1.text(vec(5,14), Font, str);
}

void CubeBecher::writeText(const char *str) {
    vid.bg1.text(vec(5,14), Font, str);
}

void CubeBecher::addSubstance(Substance* substance, float volume) {
    for(unsigned i = 0 ; i < SUBSTANCES_NUMBER ; i++) {
        if(substances[i].substance->name == substance->name) {
            substances[i].volume += volume;
            Calculator::mixTwoSubstances(mApp->cubeBecher, i);
            move = true;
            break;
        }
    }
}

//######## Animations ############
void CubeBecher::animate(float dt){
    if(move){
        const auto &liquid = vid.sprites[1];
        const auto &drop = vid.sprites[2];

        for(int t = dropTicker.tick(dt); t ; t--) {
            //Teste para saber quando a gota chegou no liquido
            //Se a posição inicial do liquido mudar tem que alterar o erro do lastY
            //Inversamente proporcional
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
                        liquid.move(liquid.x(), liquid.y() - 5);//velocidade que o liquido sobe
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

void CubePipete::animate(float dt){
    for(int t = liquidTicker.tick(dt); t ; t--) {
        text += (textTarget - text) * textSpeed;
        vid.bg1.setPanning(text.round());
        if(move){
            const auto &liquid = vid.sprites[1];

                if(liquidAnim.frame < Liquid.numFrames()){
                    liquid.setImage(Liquid, liquidAnim.frame);
                    liquidAnim.frame++;

                    if (getLiquid){
                        //maximo = 80
                        liquid.move(liquid.x(), liquid.y() - 40);//velocidade que o liquido sobe
                        writeText("50mL");
                        text.set(5, 0);
                        textTarget.set(5, 128);
                    } else {
                        liquid.move(liquid.x(), liquid.y() + 4);//velocidade que o liquido desce
                        writeText(" 5mL");
                        text.set(5, 128);
                        textTarget.set(5, -20);
                    }
                } else {
                    liquidAnim.frame = 0;
                    liquid.setImage(Liquid, liquidAnim.frame);
                    move = false;
                }
            }
    }
}

//######## onTouch Events ############
void CubeSubstance::rotate() {
    activeSubstance = (activeSubstance + 1) % SUBSTANCES_NUMBER;
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

    if(!move && !mApp->cubeBecher->move && cube.isTouching()){
        if(connectedToSubstance && isSameSubstance(connectedSubstance)){
            currentVolume = volume + GET_VOLUME;
            if(currentVolume <= MAX_VOLUME) {
                volume += GET_VOLUME;

                currentSubstance = connectedSubstance;

                getLiquid = true;
                move = true;
            }
        } else if (connectedToBecher && currentSubstance) {
            volume -= SET_VOLUME;

            mApp->cubeBecher->addSubstance(currentSubstance, SET_VOLUME);

            if(volume < 0){
                volume = 0.0f;
                currentSubstance = 0;
            }

            getLiquid = false;
            move = true;
        }
    }
}

void CubePhIndicator::calculate(float dt) {
    for(int t = ticker.tick(dt); t ; t--) {
        if(calculateOn) {
            ph = Calculator::calculatePh(mApp->cubeBecher);

            const auto &calculator = vid.sprites[0];

            calculator.setImage(Pointer, round(ph));
            calculator.move(0,72);

            String<20> str;
            str << "pH:" << FixedFP(ph, 2, 2) << "\n";
            vid.bg1.text(vec(5,12), Font, str);


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
//######## onAccelChange Events ############
void CubePipete::onAccelChange(unsigned id)
{
    const auto &liquid = vid.sprites[1];

    unsigned changeFlags = motion[id].update();
    if (changeFlags) {
        if (motion[id].shake) {
            volume = 0.0f;
            currentSubstance = 0;

            liquid.setImage(Liquid, 0);
            //Posição inicial do liquido, para não aparecer na tela
            //Se a imagem mudar tem que mudar isso
            liquid.move(0,72);
        }
    }
}

void CubeBecher::onAccelChange(unsigned id)
{
    unsigned changeFlags = motion[id].update();
    if (changeFlags) {
        if (motion[id].shake) {
            const auto &liquid = vid.sprites[1];

            liquid.setImage(Liquid, 0);
            liquid.move(0,80);

            liquidAnim.frame =  0 ;
            liquidAnim.lastY = liquid.y();
            liquidAnim.animated = false;

            dropAnim.frame = 0;
            dropAnim.animated = false;

            for (int i = 0 ; i < SUBSTANCES_NUMBER ; i++) {
                substances[i].volume = 0.0f;
            }

            mixedWrapper.volume = 0.0f;

            mixedSubstance.name = "";
            mixedSubstance.molar = 0.0f;
            mixedSubstance.h = 0;
            mixedSubstance.oh = 0;
        }
    }
}

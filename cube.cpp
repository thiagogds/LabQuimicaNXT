#include "cube.h"
#include "app.h"
#include "substance.h"

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

CubeBecher::CubeBecher(CubeID cube, App* app) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);

    SubstanceVolumeWrapper hclWrapper = {&hcl,0};
    SubstanceVolumeWrapper hbrWrapper = {&hbr, 0};
    SubstanceVolumeWrapper naohWrapper = {&naoh, 0};
    SubstanceVolumeWrapper kohWrapper = {&koh, 0};

    substances[0] = hclWrapper;
    substances[1] = hbrWrapper;
    substances[2] = naohWrapper;
    substances[3] = kohWrapper;
}

CubePhIndicator::CubePhIndicator(CubeID cube, App* app) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);
}

//########### Inits #################
void CubePipete::init(){
    vid.initMode(BG0);
    vid.bg0.image(vec(0,0), Pipete);
}

void CubeSubstance::init(){
    vid.initMode(BG0_ROM);

    String<20> str;
    str << "I am cube\n";
    str << "Substance\n\n";
    vid.bg0rom.text(vec(1,2), str);
    vid.bg0rom.text(vec(1,5), substances[activeSubstance]->name);
}

void CubeBecher::init(){
    vid.initMode(BG0_ROM);

    String<20> str;
    str << "I am cube\n";
    str << "Becher\n\n";
    vid.bg0rom.text(vec(1,2), str);
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
            printSubstance(i);
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
        vid.bg0rom.text(vec(1,5), "                  ");
        vid.bg0rom.text(vec(1,5), substances[activeSubstance]->name);
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

                vid.bg0rom.text(vec(1,4), "                  ");

                String<30> str;
                str << "Volume: " << FixedFP(volume, 1, 5);
                vid.bg0rom.text(vec(1,4), str);

                currentSubstance = connectedSubstance;
                vid.bg0rom.text(vec(1,5), "                  ");
                vid.bg0rom.text(vec(1,5), currentSubstance->name);
            }
        } else if (connectedToBecher && currentSubstance) {
            volume -= SET_VOLUME;

            mApp->cubeBecher->addSubstance(currentSubstance, SET_VOLUME);

            if(volume < 0){
                volume = 0.0f;
                currentSubstance = 0;
                vid.bg0rom.text(vec(1,5), "                  ");
            }

            String<30> str;
            str << "Volume: " << FixedFP(volume, 1, 5);
            vid.bg0rom.text(vec(1,4), str);
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

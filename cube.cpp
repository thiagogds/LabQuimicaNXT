#include "cube.h"
#include "app.h"


//########### Constructors ############
CubePipete::CubePipete(CubeID cube, App* app) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);
    motion.attach(cube);
}

CubeSubstance::CubeSubstance(CubeID cube, App* app) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);
    motion.attach(cube);

    substances[0] = &hcl;
    substances[1] = &hbr;
    substances[2] = &naoh;
    substances[3] = &koh;
}

CubeBecher::CubeBecher(CubeID cube, App* app) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);
    motion.attach(cube);
}

CubePhIndicator::CubePhIndicator(CubeID cube, App* app) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);
    motion.attach(cube);
}

//########### Inits #################
void CubePipete::init(){
    vid.initMode(BG0_ROM);

    String<20> str;
    str << "I am cube\n";
    str << "Pipete\n\n";
    vid.bg0rom.text(vec(1,2), str);
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

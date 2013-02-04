#include "app.h"
#include "cube.h"

App::App() {
    CubePipete cPipete = CubePipete(0,this);
    this->cubePipete = &cPipete;

    CubeSubstance cSubstance = CubeSubstance(1,this);
    this->cubeSubstance = &cSubstance;

    CubeBecher cBecher = CubeBecher(2,this);
    this->cubeBecher = &cBecher;

    //CubePhIndicator cPhIndicator = CubePhIndicator(3,this);
    //this->cubePhIndicator = &cPhIndicator;
}

void App::init() {
    cubePipete->init();
    cubeSubstance->init();
    cubeBecher->init();
    //cubePhIndicator->init();

    Events::cubeTouch.set(&App::onTouch, this);
    Events::cubeAccelChange.set(&App::onAccelChange, this);
    Events::neighborAdd.set(&App::onNeighborAdd, this);
    Events::neighborRemove.set(&App::onNeighborRemove, this);
}

void App::animate(float dt){
    cubeBecher->animate(dt);
}

void App::run() {
    TimeStep ts;
    while(true) {
        animate(ts.delta());
        System::paint();
        ts.next();
    }
}

void App::onTouch(unsigned id) {
    switch(id) {
        default: ; break ;
        case 0: cubePipete->onTouch(id); break ;
        case 1: cubeSubstance->onTouch(id); break ;
    };
}

void App::onAccelChange(unsigned id) {
    //switch(id) {
    //    default: ; break ;
    //    case 0: cubePipete->onAccelChange(id); break ;
    //};
}

void App::onNeighborAdd(unsigned firstID,
                        unsigned firstSide,
                        unsigned secondID,
                        unsigned secondSide) {
    switch(firstID) {
        default: ; break ;
        case 0:
            cubePipete->onNeighborAdd(firstID,
                                      firstSide,
                                      secondID,
                                      secondSide);
            break ;
    };

    switch(secondID) {
        case 0:
            cubePipete->onNeighborAdd(secondID,
                                      secondSide,
                                      firstID,
                                      firstSide);
            break ;
    };
}

void App::onNeighborRemove(unsigned firstID,
                           unsigned firstSide,
                           unsigned secondID,
                           unsigned secondSide) {
    switch(firstID) {
        default: ; break ;
        case 0:
            cubePipete->onNeighborRemove(firstID,
                                         firstSide,
                                         secondID,
                                         secondSide);
            break ;
    };

    switch(secondID) {
        case 0:
            cubePipete->onNeighborRemove(secondID,
                                         secondSide,
                                         firstID,
                                         firstSide);
            break ;
    };
}




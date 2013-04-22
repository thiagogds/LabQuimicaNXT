#include "app.h"
#include "cube.h"

App::App() : cubePipete(0),
             cubeSubstance(0),
             cubeBecher(0),
             cubePhIndicator(0){
}

void App::init() {
    static CubePipete cPipete = CubePipete(0,this);
    cubePipete = &cPipete;

    static CubeSubstance cSubstance = CubeSubstance(1,this);
    cubeSubstance = &cSubstance;

    static CubeBecher cBecher = CubeBecher(2,this);
    cubeBecher = &cBecher;

    static CubePhIndicator cPhIndicator = CubePhIndicator(3,this);
    cubePhIndicator = &cPhIndicator;

    cubePipete->init();
    cubeSubstance->init();
    cubeBecher->init();
    cubePhIndicator->init();

    Events::cubeTouch.set(&App::onTouch, this);
    Events::cubeAccelChange.set(&App::onAccelChange, this);
    Events::neighborAdd.set(&App::onNeighborAdd, this);
    Events::neighborRemove.set(&App::onNeighborRemove, this);
}

void App::animate(float dt){
    this->cubeBecher->animate(dt);
    this->cubePipete->animate(dt);
}

void App::calculate() {
    this->cubePhIndicator->calculate();
}

void App::run() {
    TimeStep ts;
    while(true) {
        animate(ts.delta());
        calculate();
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
    switch(id) {
        default: ; break ;
        case 0: cubePipete->onAccelChange(id); break ;
        case 2: cubeBecher->onAccelChange(id); break ;
    };
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
        case 3:
            cubePhIndicator->onNeighborAdd(firstID,
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
        case 3:
            cubePhIndicator->onNeighborAdd(secondID,
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
        case 3:
            cubePhIndicator->onNeighborRemove(firstID,
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
        case 3:
            cubePhIndicator->onNeighborRemove(secondID,
                                              secondSide,
                                              firstID,
                                              firstSide);
            break ;
    };
}

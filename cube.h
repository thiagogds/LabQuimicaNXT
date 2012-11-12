#ifndef _CUBE_H
#define _CUBE_H

#include "app.h"

using namespace Sifteo;

class App;

class CubePipete{
public:
    CubePipete(CubeID cube, App* app);

    CubeID mCube;
    App* mApp;

    VideoBuffer vid;
    TiltShakeRecognizer motion;


    void init();
    void onTouch(unsigned id);
    void onAccelChange(unsigned id);
    void onNeighborAdd(unsigned firstID, 
                       unsigned firstSide, 
                       unsigned secondID, 
                       unsigned secondSide);
    void onNeighborRemove(unsigned firstID, 
                          unsigned firstSide,
                          unsigned secondID, 
                          unsigned secondSide);


};

class CubeSubstance{
public:
    CubeSubstance(CubeID cube, App* app);

    CubeID mCube;
    App* mApp;

    VideoBuffer vid;
    TiltShakeRecognizer motion;

    void init();
    void onTouch(unsigned id);
    void onAccelChange(unsigned id);
    void onNeighborAdd(unsigned firstID, 
                       unsigned firstSide, 
                       unsigned secondID, 
                       unsigned secondSide);
    void onNeighborRemove(unsigned firstID, 
                          unsigned firstSide,
                          unsigned secondID, 
                          unsigned secondSide);

};

class CubeBecher{
public:
    CubeBecher(CubeID cube, App* app);

    CubeID mCube;
    App* mApp;

    VideoBuffer vid;
    TiltShakeRecognizer motion;

    void init();
    void onTouch(unsigned id);
    void onAccelChange(unsigned id);
    void onNeighborAdd(unsigned firstID, 
                       unsigned firstSide, 
                       unsigned secondID, 
                       unsigned secondSide);
    void onNeighborRemove(unsigned firstID, 
                          unsigned firstSide,
                          unsigned secondID, 
                          unsigned secondSide);

};

class CubePhIndicator{
public:
    CubePhIndicator(CubeID cube, App* app);

    CubeID mCube;
    App* mApp;

    TiltShakeRecognizer motion;
    VideoBuffer vid;

    void init();
    void onTouch(unsigned id);
    void onAccelChange(unsigned id);
    void onNeighborAdd(unsigned firstID, 
                       unsigned firstSide, 
                       unsigned secondID, 
                       unsigned secondSide);
    void onNeighborRemove(unsigned firstID, 
                          unsigned firstSide,
                          unsigned secondID, 
                          unsigned secondSide);

};

#endif


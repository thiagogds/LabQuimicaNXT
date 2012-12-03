#ifndef _CUBE_H
#define _CUBE_H

#include "app.h"
#include "substance.h"

using namespace Sifteo;

class App;

class CubePipete{
public:
    CubePipete(CubeID cube, App* app);

    CubeID mCube;
    App* mApp;

    VideoBuffer vid;

    const float GET_VOLUME = 0.0050f;
    const float MAX_VOLUME = 0.0100f;
    const float SET_VOLUME = 0.0005f;
    float volume = 0.0f;
    Substance *currentSubstance;
    bool connectedToSubstance;
    bool connectedToBecher;

    void init();
    bool isSameSubstance(Substance* substance);
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

    unsigned activeSubstance = 0;
    Substance *substances[4];

    Substance hcl = Acid("HCl", 1.0f, 1);
    Substance hbr = Acid("HBr", 1.0f, 1);
    Substance naoh = Base("NaOH", 1.0f, 1);
    Substance koh = Base("KOH", 1.0f, 1);

    void init();
    void rotate();
    Substance* getCurrentSubstance();
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

struct SubstanceVolumeWrapper {
    Substance *substance;
    float volume;
};

class CubeBecher{
public:
    CubeBecher(CubeID cube, App* app);

    CubeID mCube;
    App* mApp;

    VideoBuffer vid;

    SubstanceVolumeWrapper substances[4];

    Substance hcl = Acid("HCl", 1.0f, 1);
    Substance hbr = Acid("HBr", 1.0f, 1);
    Substance naoh = Base("NaOH", 1.0f, 1);
    Substance koh = Base("KOH", 1.0f, 1);

    void init();
    void addSubstance(Substance* substance, float volume);
    void printSubstance(unsigned index);
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


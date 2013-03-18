#ifndef _CUBE_H
#define _CUBE_H

#include "app.h"
#include "substance.h"

using namespace Sifteo;

const int SUBSTANCES_NUMBER = 5;

static TiltShakeRecognizer motion[CUBE_ALLOCATION];

class App;

struct SubstanceVolumeWrapper {
    Substance *substance;
    float volume;
};

struct LiquidAnimation {
    int lastY;
    int frame;
    bool animated;
};

struct DropAnimation {
    int frame;
    bool animated;
};


class CubePipete{
public:
    CubePipete(CubeID cube, App* app);

    CubeID mCube;
    App* mApp;

    VideoBuffer vid;

    TimeTicker liquidTicker;

    LiquidAnimation liquidAnim;

    bool move;
    bool getLiquid;

    const float GET_VOLUME = 0.0050f;
    const float MAX_VOLUME = 0.0100f;
    const float SET_VOLUME = 0.0005f;
    float volume = 0.0f;
    Substance *currentSubstance;
    bool connectedToSubstance;
    bool connectedToBecher;

    void init();
    bool isSameSubstance(Substance* substance);
    void animate(float dt);
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
    Substance *substances[SUBSTANCES_NUMBER];

    Substance hcl = Acid("HCl", 1.0f, 1);
    Substance hbr = Acid("HBr", 1.0f, 1);
    Substance naoh = Base("NaOH", 1.0f, 1);
    Substance koh = Base("KOH", 1.0f, 1);
    Substance h2o = Substance("H2O", 0.0f, 0, 0);

    void init();
    void rotate();
    Substance* getCurrentSubstance();
    void onTouch(unsigned id);
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

    TimeTicker dropTicker;
    TimeTicker liquidTicker;

    bool move;

    LiquidAnimation liquidAnim;
    DropAnimation dropAnim;

    SubstanceVolumeWrapper substances[SUBSTANCES_NUMBER];
    SubstanceVolumeWrapper mixedWrapper;

    Substance hcl = Acid("HCl", 1.0f, 1);
    Substance hbr = Acid("HBr", 1.0f, 1);
    Substance naoh = Base("NaOH", 1.0f, 1);
    Substance koh = Base("KOH", 1.0f, 1);
    Substance h2o = Substance("H2O", 0.0f, 0, 0);

    Substance mixedSubstance = Substance("", 0.0f, 0, 0);

    void init();
    void animate(float dt);
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

    float ph;
    bool calculateOn;
    TimeTicker ticker;

    void init();
    void calculate(float dt);
    void onTouch(unsigned id);
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


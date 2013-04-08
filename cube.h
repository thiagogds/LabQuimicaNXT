#ifndef _CUBE_H
#define _CUBE_H

#include "app.h"
#include "substance.h"

using namespace Sifteo;

static const int SUBSTANCES_NUMBER = 9;

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

    bool move = false;
    bool getLiquid = true;

    static const float textSpeed = 0.2f;
    static const float GET_VOLUME = 0.0050f;
    static const float MAX_VOLUME = 0.0100f;
    static const float SET_VOLUME = 0.0005f;

    Float2 text = {0, 0};
    Float2 textTarget = {0, 0};

    float volume = 0.0f;
    Substance *currentSubstance;
    bool connectedToSubstance = false;
    bool connectedToBecher = false;

    void init();
    void writeText(const char *str);
    bool isSameSubstance(Substance* substance);
    void animate(float dt);
    void animateText(float dt);
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
    Substance *substances[SUBSTANCES_NUMBER] = {0, 0, 0, 0};

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

    bool move = false;
    static const float textSpeed = 0.2f;

    Float2 text = {0, 0};
    Float2 textTarget = {0, 0};

    LiquidAnimation liquidAnim = {0, 0, false};
    DropAnimation dropAnim = {0, false};

    Substance mixedSubstance;

    SubstanceVolumeWrapper substances[SUBSTANCES_NUMBER];
    SubstanceVolumeWrapper mixedWrapper;

    void init();
    void animate(float dt);
    void writeText(const char *str);
    void addSubstance(Substance* substance, float volume);
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

    float ph = 0.0f;
    bool calculateOn = false;
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


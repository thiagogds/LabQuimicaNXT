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

    bool move;
    bool getLiquid;

    float textSpeed;
    float GET_VOLUME;
    float MAX_VOLUME;
    float SET_VOLUME;

    Float2 text;
    Float2 textTarget;

    float volume;
    Substance *currentSubstance;
    bool connectedToSubstance;
    bool connectedToBecher;

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

    unsigned activeSubstance;
    Substance *substances[SUBSTANCES_NUMBER];

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
    float textSpeed;

    Float2 text;
    Float2 textTarget;

    LiquidAnimation liquidAnim;
    DropAnimation dropAnim;

    Substance mixedSubstance;

    //Pode ser que tenhamos que colocar como ponteiro para usar static.
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


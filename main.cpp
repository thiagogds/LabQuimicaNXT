/*
 * Sifteo SDK Example.
 */

#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;

static Metadata M = Metadata()
    .title("Sifteo Chemistry Lab")
    .package("moleque.lab.quimica", "0.1")
    .icon(Icon)
    .cubeRange(4, 4);

static VideoBuffer vid[4];
static TiltShakeRecognizer motion[4];

const unsigned PIPETE = 0;
const unsigned SUBSTANCE = 1;
const unsigned BECHER  = 2;
const unsigned PH_INDICATOR = 3;

class CubePipete{
public:
    const float GET_VOLUME = 0.002;
    const float MAX_VOUME = 0.01;

    float volume = 0.0;

    void install(){
        vid[PIPETE].initMode(BG0_ROM);
        vid[PIPETE].attach(PIPETE);
        motion[PIPETE].attach(PIPETE);

        String<128> str;
        str << "I am cube\n";
        str << "Pipete \n\n";
        vid[PIPETE].bg0rom.text(vec(1,2), str);
    }
    

private:

};

class CubeSubstance{
public:
    const float GET_VOLUME = 0.002;
    const float MAX_VOUME = 0.01;

    float volume = 0.0;

    void install(){
        vid[SUBSTANCE].initMode(BG0_ROM);
        vid[SUBSTANCE].attach(SUBSTANCE);
        motion[SUBSTANCE].attach(SUBSTANCE);

        String<128> str;
        str << "I am cube\n";
        str << "Substance \n\n";
        vid[SUBSTANCE].bg0rom.text(vec(1,2), str);
    }
    

private:

};

class CubeBecher{
public:
    const float GET_VOLUME = 0.002;
    const float MAX_VOUME = 0.01;

    float volume = 0.0;

    void install(){
        vid[BECHER].initMode(BG0_ROM);
        vid[BECHER].attach(BECHER);
        motion[BECHER].attach(BECHER);

        String<128> str;
        str << "I am cube\n";
        str << "Becher \n\n";
        vid[BECHER].bg0rom.text(vec(1,2), str);
    }
    

private:

};

class CubePhIndicator{
public:
    const float GET_VOLUME = 0.002;
    const float MAX_VOUME = 0.01;

    float volume = 0.0;

    void install(){
        vid[PH_INDICATOR].initMode(BG0_ROM);
        vid[PH_INDICATOR].attach(PH_INDICATOR);
        motion[PH_INDICATOR].attach(PH_INDICATOR);

        String<128> str;
        str << "I am cube\n";
        str << "pH Indicator \n\n";
        vid[PH_INDICATOR].bg0rom.text(vec(1,2), str);
    }
    

private:

};

class Substance{
public:
    String<32> name;
    float molar;
    int h;
    int oh;

    Substance (String<32> name, float molar, int h, int oh){
        this->name = name;
        this->molar = molar;
        this->h = h;
        this->oh = oh;
    }

    float mol (float volume){
        return this->molar * volume;
    }

    bool isBase (){
        return (this->oh > 0);
    }

    bool isAcid (){
        return (this->h > 0);
    }

    bool isSameType (Substance *subs){
        //Retorna verdadeiro para apenas no caso de ambos falsos ou ambos verdadeiros
        //TODO: Verificar o operador de XOR para esse caso
        return !(this->h > 0 ^ subs->h > 0);
    }
};


class Acid : public Substance
{
public:
    Acid (String<> name, double molar, int h) : base(name, molar, h, 0){
    }
};

class Base : public Substance
{
public:
    Base (String name, double molar, int oh) : base(name, molar, 0, oh){
    }
};

void main()
{
    static CubePipete cubePipete;
    static CubeSubstance cubeSubstance;
    static CubeBecher cubeBecher;
    static CubePhIndicator cubePhIndicator;

    cubePipete.install();
    cubeSubstance.install();
    cubeBecher.install();
    cubePhIndicator.install();

    // We're entirely event-driven. Everything is
    // updated by SensorListener's event callbacks.
    while (1)
        System::paint();
}

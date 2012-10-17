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

class Substance{
public:
    const char *name;
    float molar;
    int h;
    int oh;

    Substance (const char *name, float molar, int h, int oh){
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
    Acid (const char *name, float molar, int h) : Substance(name, molar, h, 0){
    }
};

class Base : public Substance
{
public:
    Base (const char *name, float molar, int oh) : Substance(name, molar, 0, oh){
    }
};

class CubePipete{
public:
    const float GET_VOLUME = 0.002;
    const float MAX_VOUME = 0.01;

    float volume = 0.0;

    void install(){
        vid[PIPETE].initMode(BG0_ROM);
        vid[PIPETE].attach(PIPETE);
        motion[PIPETE].attach(PIPETE);

        String<32> str;
        str << "I am cube\n";
        str << "Pipete \n\n";
        vid[PIPETE].bg0rom.text(vec(1,2), str);
    }


private:

};

class CubeSubstance{
public:
    unsigned activeSubstance = 0;
    Substance *substances[4];

    void install(){
        Events::cubeTouch.set(&CubeSubstance::onTouch, this);

        vid[SUBSTANCE].initMode(BG0_ROM);
        vid[SUBSTANCE].attach(SUBSTANCE);
        motion[SUBSTANCE].attach(SUBSTANCE);

        Substance hcl = Acid("HCl", 1.0f, 1);
        Substance hbr = Acid("HBr", 1.0f, 1);
        Substance naoh = Base("NaOH", 1.0f, 1);
        Substance coco = Base("CoCo", 1.0f, 1);

        this->substances[0] = &hcl;
        this->substances[1] = &hbr;
        this->substances[2] = &naoh;
        this->substances[3] = &coco;

        String<32> str;
        str << "I am cube\n";
        str << "Substance \n\n";
        vid[SUBSTANCE].bg0rom.text(vec(1,2), str);
    }


private:

    void rotate() {
        this->activeSubstance = (this->activeSubstance + 1) % 4;
    }
    void onTouch(unsigned id) {
        CubeID cube(id);

        if(cube.isTouching()){
            vid[SUBSTANCE].bg0rom.text(vec(1,6), "        ");
            vid[SUBSTANCE].bg0rom.text(vec(1,6), this->substances[activeSubstance]->name);
            this->rotate();
        }
    }
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

        String<32> str;
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

        String<32> str;
        str << "I am cube\n";
        str << "pH Indicator \n\n";
        vid[PH_INDICATOR].bg0rom.text(vec(1,2), str);
    }


private:

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

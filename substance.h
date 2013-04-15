#ifndef _SUBSTANCE_H
#define _SUBSTANCE_H

#include <sifteo.h>

using namespace Sifteo;

class Substance {
    public:
        Substance(const char *name, float molar, int h, int oh);

        String<8> name;
        float molar;
        int h;
        int oh;

        float mol(float volume);
        bool isBase();
        bool isAcid();
        bool isNeutral();
        bool isSameType(Substance* substance);
};

class Acid : public Substance {
    public:
        Acid (const char *name, float molar, int h) : Substance(name, molar, h, 0){
        }
};

class Base : public Substance {
    public:
        Base (const char *name, float molar, int oh) : Substance(name, molar, 0, oh){
        }
};

#endif


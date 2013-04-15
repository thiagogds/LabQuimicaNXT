#include "substance.h"

Substance::Substance (const char *name, float molar, int h, int oh){
    this->name << name;
    this->molar = molar;
    this->h = h;
    this->oh = oh;
}

float Substance::mol (float volume){
    return this->molar * volume;
}

bool Substance::isBase (){
    return (this->oh > 0);
}

bool Substance::isAcid (){
    return (this->h > 0);
}

bool Substance::isNeutral (){
    return (this->h == 0 && this->oh == 0);
}

bool Substance::isSameType (Substance *substance){
    return !(this->h > 0 ^ substance->h > 0);
}

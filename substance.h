#ifndef _APP_H
#define _APP_H

class Substance {
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


#include "app.h"
#include "cube.h"
#include "substance.h"

class Calculator{
public:
    void mixSubstances();
    static float calculatePh(CubeBecher *becher);
};

float Calculator::calculatePh(CubeBecher *becher) {
    Substance &substance = becher->mixedSubstance;

    // Marreta bionica da quimica!
    if (substance.molar == 0) {
        return 7;
    }

    float e = 2.30258509299404;
    float ph = -(Sifteo::log (substance.molar)/e);

    if (substance.oh) {
        ph = 14 - ph;
    }

    return ph;
}

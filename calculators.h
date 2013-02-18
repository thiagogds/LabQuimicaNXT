#include "app.h"
#include "cube.h"
#include "substance.h"

class Calculator{
public:
    static void mixSubstances(CubeBecher *becher);
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

    if (substance.isBase()) {
        ph = 14 - ph;
    }

    return ph;
}

void Calculator::mixSubstances(CubeBecher *becher){
    Substance *first_substance = becher->substances[0].substance;
    float first_volume = becher->substances[0].volume;

    Substance *second_substance = becher->substances[2].substance;
    float second_volume = becher->substances[2].volume;

    float volume = first_volume + second_volume;

    float mols = 0.0;
    float molar = 0.0;

    if (first_substance->isSameType (second_substance)) {
        mols = first_substance->mol (first_volume) + second_substance->mol (second_volume);
        if (first_substance->isBase()) {
            mols = mols * -1;
        }
    } else if (first_substance->isAcid ()) {
        mols = first_substance->mol (first_volume) - second_substance->mol (second_volume);
    } else {
        mols = second_substance->mol (second_volume) - first_substance->mol (first_volume);
    }

    if (mols < 0) {
        mols = mols * -1;
        molar = mols / volume;

        becher->mixedSubstance.molar = molar;
        becher->mixedSubstance.name = "Mixed";
        becher->mixedSubstance.oh = 1;
        becher->mixedWrapper.volume = volume;
    } else {
        molar = mols / volume;

        becher->mixedSubstance.molar = molar;
        becher->mixedSubstance.name = "Mixed";
        becher->mixedSubstance.h = 1;
        becher->mixedWrapper.volume = volume;
    }
}

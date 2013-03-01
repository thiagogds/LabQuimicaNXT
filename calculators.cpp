#include "app.h"
#include "cube.h"
#include "substance.h"
#include "calculators.h"

float Calculator::calculatePh(CubeBecher *becher) {
    Substance &substance = becher->mixedSubstance;

    if (substance.isNeutral()) {
        return 7;
    }

    float e = 2.30258509299404;
    float ph = -(Sifteo::log (substance.molar)/e);

    if (substance.isBase()) {
        ph = 14 - ph;
        }

    return ph;
}

void Calculator::mixTwoSubstances(CubeBecher *becher, unsigned firstWrapperIndex){
    Substance *first_substance = becher->substances[firstWrapperIndex].substance;
    float first_volume = becher->substances[firstWrapperIndex].volume;

    Substance second_substance = becher->mixedSubstance;
    float second_volume = becher->mixedWrapper.volume;

    float volume = first_volume + second_volume;

    if (volume > 0) {
        float mols = 0.0;
        float molar = 0.0;

        if (second_substance.isSameType (first_substance)) {
            mols = first_substance->mol (first_volume) + second_substance.mol (second_volume);
            if (first_substance->isBase()) {
                mols = mols * -1;
            }
        } else if (first_substance->isAcid ()) {
            mols = first_substance->mol (first_volume) - second_substance.mol (second_volume);
        } else {
            mols = second_substance.mol (second_volume) - first_substance->mol (first_volume);
        }

        if (mols < 0) {
            mols = mols * -1;
            molar = mols / volume;

            becher->mixedSubstance.molar = molar;
            becher->mixedSubstance.name = "Mixed";
            becher->mixedSubstance.oh = 1;
            becher->mixedSubstance.h = 0;
            becher->mixedWrapper.volume = volume;
        } else if (mols > 0) {
            molar = mols / volume;

            becher->mixedSubstance.molar = molar;
            becher->mixedSubstance.name = "Mixed";
            becher->mixedSubstance.h = 1;
            becher->mixedSubstance.oh = 0;
            becher->mixedWrapper.volume = volume;
        } else {
            molar = mols / volume;

            becher->mixedSubstance.molar = molar;
            becher->mixedSubstance.name = "Mixed";
            becher->mixedSubstance.oh = 0;
            becher->mixedSubstance.h = 0;
            becher->mixedWrapper.volume = volume;
        }
    }
}

#ifndef SLABWISEBILLCALCULATOR___
#define SLABWISEBILLCALCULATOR___

#include <map>

/**
 * Utility class to compute rate based on slabs of conmsumption
 **/
class SlabWiseBillCalculator
{
    typedef std::map<int, int> SlabUpperLimitToRateMap;

    SlabUpperLimitToRateMap slab_rates;
    int flat_rate; // The rate for consumption above the defined slabs

public:
    SlabWiseBillCalculator(int flat_rate_ = 1)
    {}

    void addSlab(int upto, int rate);
    void setFlatRate(int rate) { flat_rate = rate; }
    int calculate(int consumption) const;

    // TODO: Add APIs to reconfigure the slabs and rates
};
#endif //SLABWISEBILLCALCULATOR___

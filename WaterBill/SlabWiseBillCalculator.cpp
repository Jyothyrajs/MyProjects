#include "SlabWiseBillCalculator.h"

void SlabWiseBillCalculator::addSlab(int upto,int rate)
{
    slab_rates[upto] = rate;
    // NOTE: calling this function with existing slab will cause updating the existing rate
}

int SlabWiseBillCalculator::calculate(int consumption) const
{
    SlabUpperLimitToRateMap::const_iterator iter = slab_rates.begin(), iterEnd = slab_rates.end();
    int last_upto = 0;
    int sum = 0;

    // compute the rate for each slab
    for(; iter != iterEnd; iter++ )
    {
        int curr_slab_width = iter->first - last_upto;
        int consumption_in_this_slab = (consumption <= curr_slab_width) ? consumption : iter->first - last_upto;

        sum += (consumption_in_this_slab * iter->second);

        last_upto = iter->first;
        consumption -= consumption_in_this_slab;
    }

    // rate for exceeding consumption
    if( consumption > 0 )
    {
            sum += (consumption * flat_rate); 
    }
    return sum;
}

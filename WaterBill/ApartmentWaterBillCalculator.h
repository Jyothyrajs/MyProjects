#ifndef APARTMENTWATERBILLCALCULATOR___
#define APARTMENTWATERBILLCALCULATOR___

#include "SlabWiseBillCalculator.h"


class ApartmentWaterBillCalculator
{

public:
    struct BillingConfig
    {
        typedef std::map<int, int> AptTypeToOccupancyMap;
        AptTypeToOccupancyMap aptTypeToOccupancyMap;
        SlabWiseBillCalculator slab_rate_calculator;
        float borewell_rate;
        float corporation_rate;
        int per_head_allowance;

        void display();
    };

    // Function to create a standard billing configuration
    // More such functions can be added if required to support
    // more configurations
    static BillingConfig* createDefaultConfig();

private:
    const BillingConfig& config;
    int apt_type; //num beds 2, 3,...
    int num_guests;

    // Part of bill going to borewell or apartment
    float borewell_factor;
    float corporation_factor;

    int calculateMemberConsumption();
    int calculateGuestConsumption();

public:
    ApartmentWaterBillCalculator(const BillingConfig& config_, int apt_type_, float borewell_factor_, float corporation_factor_);

    void addGuest(int n) { num_guests += n; }
    void calculateBill();
};
#endif

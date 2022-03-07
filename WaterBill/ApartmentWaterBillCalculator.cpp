#include "ApartmentWaterBillCalculator.h"

#include <iostream>

ApartmentWaterBillCalculator::ApartmentWaterBillCalculator(const BillingConfig& config_, int apt_type_, float borewell_factor_, float corporation_factor_)
    : config(config_)
    , apt_type(apt_type_)
    , borewell_factor(borewell_factor_)
    , corporation_factor(corporation_factor_)
    , num_guests(0)
{
}

void ApartmentWaterBillCalculator::BillingConfig::display()
{
    std::cout <<"Allowance per head: " <<  per_head_allowance << std::endl;
    std::cout <<"Borewell_rate:" <<  borewell_rate << std::endl;
    std::cout <<"Corporation rate:" <<  corporation_rate << std::endl;
}

ApartmentWaterBillCalculator::BillingConfig* ApartmentWaterBillCalculator::createDefaultConfig()
{
    BillingConfig* p = new BillingConfig();
    p->aptTypeToOccupancyMap[2] = 3;
    p->aptTypeToOccupancyMap[3] = 5;
    p->borewell_rate = 1.5;
    p->corporation_rate = 1;
    p->per_head_allowance = 10;

    // Add billing slabs for the tanker water billing
    p->slab_rate_calculator.addSlab(500, 2);
    p->slab_rate_calculator.addSlab(1500, 3);
    p->slab_rate_calculator.addSlab(3000, 5);
    p->slab_rate_calculator.setFlatRate(8);
    return p;
}

int ApartmentWaterBillCalculator::calculateMemberConsumption()
{
    return config.aptTypeToOccupancyMap.at(apt_type) * config.per_head_allowance  * 30;
}

int ApartmentWaterBillCalculator::calculateGuestConsumption()
{
    return num_guests * config.per_head_allowance * 30;
}


void ApartmentWaterBillCalculator::calculateBill()
{
    int member_consumption = calculateMemberConsumption();

    int amount = member_consumption * corporation_factor * config.corporation_rate; // amount for corporation water
    amount +=  member_consumption * borewell_factor * config.borewell_rate; // amount for borewell water

    // Compute the tanker water charge for the guests
    int guest_consumption = calculateGuestConsumption();

    amount += config.slab_rate_calculator.calculate(guest_consumption);

    std::cout << member_consumption + guest_consumption <<" " << amount << std::endl;
}

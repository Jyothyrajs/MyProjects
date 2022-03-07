#include "ApartmentWaterBillCalculator.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    ApartmentWaterBillCalculator *pCalc = nullptr;
    ApartmentWaterBillCalculator::BillingConfig* p= ApartmentWaterBillCalculator::createDefaultConfig();

    std::ifstream ifs(argv[1]);
    while(ifs.peek() != EOF)
    {
        std::string s;
        ifs >> s;

        if ( s == "ALLOT_WATER" )
        {
            int apt_type;
            std::string ratio;

            ifs >> apt_type;
            int a, b;
            char c;
            ifs >> a >>c >>  b;
            float corp_fact = (float)a/(a+b);
            float bore_fact = (float)b/(a+b);
            if(pCalc != nullptr)    // This is a new set of commands starting with new ALLOT_WATER, delete the previous calculator
                delete pCalc;
            pCalc = new ApartmentWaterBillCalculator(*p, apt_type, bore_fact, corp_fact);

        }
        else if (s == "ADD_GUESTS")
        {
            int guest;
            ifs >> guest;
            if( pCalc != nullptr )
            {
                pCalc->addGuest(guest);
            }
        }
        else if (s == "BILL")
        {
            if( pCalc != nullptr )
            {
                pCalc->calculateBill();
            }
        }

    }

    
    return 0;
}


//
//  components.h
//  AC Circuits
//
//  Created by Brett Yang on 17/4/18.
//  Copyright © 2018 Brett Yang. All rights reserved.
//

#ifndef components_h
#define components_h

#include <iostream>
#include "complex.h"


using namespace std;

class component
{
public:
    virtual ~component() = default;
    virtual void set_frequency(const double freq)=0;
    virtual double get_frequency()=0;
    virtual complex get_impedance()=0;
    virtual double get_magnitudeimpedance()=0;
    virtual double get_phasedifference()=0;
    virtual string get_name()=0;
    virtual string get_type()=0;
    virtual double get_info()=0; // The return values are resistance, capacitance or inductance, depending on component type
    virtual void print_info()=0;
};


#endif /* components_h */

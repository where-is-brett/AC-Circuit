//
//  composed.h
//  AC Circuits
//
//  Created by Brett Yang on 01/05/2018.
//  Copyright © 2018 Brett Yang. All rights reserved.
//
//  This class stores the properties
//
//

#ifndef composed_h
#define composed_h

#include <iostream>
#include <string>
#include "component.h"
#include "complex.h"

using namespace std;

class composed : virtual public component
{
private:
    string name, type="composed";
    double inductance, capacitance, resistance, frequency, magnitude_impedance, phase_difference;
    complex impedance;
public:
    // Default constructor
    composed() : inductance(0), capacitance(0), resistance(0), frequency(0), magnitude_impedance(0), phase_difference(0), name("") {}
    // Parameterised constructor
    composed(const double freq, const double phs_diff, const double res, const double cap, const double ind, complex imp) : inductance(ind), capacitance(cap), resistance(res), frequency(freq), phase_difference(phs_diff), impedance(imp)
    {
        // Use getMod() function from complex class definition to return the magnitude of impedance
        magnitude_impedance = imp.getMod();
    }
    // Destructor
    ~composed(){}
    
    
    // Function to set frequency and name
    void set_frequency(double freq) { frequency=freq; } // Despite the redundancy, this is needed for class to be non-abstract
    void set_name(string name_tag) { name=name_tag; }
    
    // Access functions
    double get_frequency() { return frequency; }
    complex get_impedance() { return impedance; }
    double get_magnitudeimpedance() { return magnitude_impedance; }
    double get_phasedifference() { return phase_difference; }
    string get_name() { return name; }
    string get_type() { return type; }
    double get_info() { return 0; }
    
};


#endif /* composed_h */

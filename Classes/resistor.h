//
//  resistor.h
//  AC Circuits
//
//  Created by Brett Yang on 17/4/18.
//  Copyright © 2018 Brett Yang. All rights reserved.
//

#ifndef resistor_h
#define resistor_h

#include <iostream>
#include <string>
#include "component.h"
#include "complex.h"

using namespace std;

class resistor : public component
{
private:
    string name, type="resistor";
    double resistance, frequency, magnitude_impedance, phase_difference;
    complex impedance;
public:
    // Default constructor
    resistor() : resistance(0), frequency(0), magnitude_impedance(0), phase_difference(0), name("resistor") {}
    // Parameterised constructor
    resistor(const string tname_tag, const double res, const double freq) : resistance(res), frequency(freq)
    {
        // Set name for this component
        name = tname_tag;
        // The inductance of a resistor is just the resistance
        // This is because the current accross the resistor in a AC circuit is in phase with the voltage
        // Set the impedance using "setReal()" function from complex class definition
        impedance.setReal(res);
        // Set the magnitude of impedance using 'getMod()' function from complex class definition
        magnitude_impedance = impedance.getMod();
        // Calculate the phase difference from impedance
        // The phase difference is given by: atan(imp_im/imp_re)
        // However division by zero is restricted, here we calculate phase difference by cases:
        const double imp_im = impedance.getImg(), imp_re = impedance.getReal();
        // If the real part of impedance is zero and imaginery part is negative, arctan approaches -π/2
        if (imp_re==0 && imp_im<0) { phase_difference = -PI/2; }
        // If the real part of impedance is zero and imaginery part is positive, arctan approaches π/2
        else if (imp_re==0 && imp_im>0) { phase_difference = PI/2; }
        // And for the defined range of arctan function, use 'atan' from standard math library
        else { phase_difference = atan(imp_im/imp_re); }
        
    }
    // Destructor
    ~resistor(){ cout<<"Destroying resistor: "<<this->get_name()<<endl; }
    
    // Function to set frequency
    void set_frequency(const double freq) { frequency = freq; }
    // Function to return the impedance
    complex get_impedance() { return impedance; }
    // Function to return the frequency
    double get_frequency() { return frequency; }
    // Function to return the magnitude of impedance/resistance (note: the resistance has the same value as the impedance_magnitude)
    double get_magnitudeimpedance() { return magnitude_impedance; }
    // Function to return phase difference
    double get_phasedifference() { return phase_difference; }
    // Function to return component name
    string get_name() { return name; }
    // Function to return resistance
    double get_info(){ return resistance; }
    // Function to return the type
    string get_type() { return type; }
    // Function to print info
    void print_info(){ cout<<resistance<<" Ohm(s)"<<endl; }
    
};


#endif /* resistor_h */

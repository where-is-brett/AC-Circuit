//
//  capacitor.h
//  AC Circuits
//
//  Created by Brett Yang on 18/4/18.
//  Copyright © 2018 Brett Yang. All rights reserved.
//

#ifndef capacitor_h
#define capacitor_h

#include <iostream>
#include <string>
#include "component.h"
#include "complex.h"

using namespace std;


class capacitor : public component
{
private:
    string name, type="capacitor";
    double capacitance, frequency, magnitude_impedance, phase_difference;
    complex impedance;
public:
    // Default constructor
    capacitor() : capacitance(0), frequency(0), magnitude_impedance(0), phase_difference(-PI/2) {}
    // Parameterised constructor
    capacitor(const string name_tag, const double cap, const double freq) : capacitance(cap), frequency(freq)
    {
        // Set name for this component
        name = name_tag;
        // The impedace pof a capcitor is given by Z = 1/(i*w*C) = -i/(w*C), where w=2πf
        impedance.setImg(-1/(2*PI*cap*freq));
        // Call to "getMod()" function to get the magnitude of impedance
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
    ~capacitor(){ cout<<"Destroying capacitor: "<<this->get_name()<<endl; }
    
    // Function to set frequency
    void set_frequency(const double freq)
    {
        // Update the impedance as its dependence on frequency
        frequency = freq;
        impedance.setImg(-1/(2*PI*freq*capacitance));
        magnitude_impedance = impedance.getMod();
    }
    // Function to return capacitance
    double get_info() { return capacitance; }
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
    // Function to return the type
    string get_type() { return type; }
    // Function to print info
    void print_info(){ cout<<capacitance<<" Farad(s)"<<endl; }
};

#endif /* capacitor_h */

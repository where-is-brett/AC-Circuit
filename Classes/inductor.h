//
//  inductor.h
//  AC Circuits
//
//  Created by Brett Yang on 17/4/18.
//  Copyright © 2018 Brett Yang. All rights reserved.
//

#ifndef inductor_h
#define inductor_h

#include <iostream>
#include <string>
#include "component.h"
#include "complex.h"

using namespace std;


class inductor  : public component
{
private:
    string name, type="inductor";
    double inductance, frequency, magnitude_impedance, phase_difference;
    complex impedance;
public:
    // Default constructor
    inductor() : inductance(0), frequency(0), magnitude_impedance(0), phase_difference(PI/2) {}
    // Parameterised constructor
    inductor(const string name_tag, const double ind, const double freq) : inductance(ind), frequency(freq)
    {
        // Set name for this component
        name = name_tag;
        // The inductance of a inductor in an AC circuit is given by: Z = i*w*L
        // This is because the current accross the inductor in a AC circuit is in PI/2 out of phase with the voltage
        // Set the impedance using "setImg()" from complex class definition
        impedance.setImg(2*PI*freq*ind);
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
    ~inductor(){ cout<<"Destroying inductor: "<<this->get_name()<<endl; }
    
    // Function to set frequency
    void set_frequency(const double freq)
    {
        // Update the impedance as its dependence on frequency
        frequency = freq;
        impedance.setImg(2*PI*freq*inductance);
        magnitude_impedance = impedance.getMod();
    }
    // Function to return inductance
    double get_info() { return inductance; }
    // Function to return the impedance
    complex get_impedance() { return impedance; }
    // Function to return the frequency
    double get_frequency() { return frequency; }
    // Function to return the magnitude of impedance
    double get_magnitudeimpedance() { return magnitude_impedance; }
    // Function to return phase difference
    double get_phasedifference() { return phase_difference; }
    // Function to return component name
    string get_name() {return name;}
    // Function to return the type
    string get_type() { return type; }
    // Function to print info
    void print_info(){ cout<<inductance<<" Henry(s)"<<endl; }
    
};


#endif /* inductor_h */

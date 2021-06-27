//
//  series_connect.h
//  AC Circuits
//
//  Created by Brett Yang on 07/05/2018.
//  Copyright © 2018 Brett Yang. All rights reserved.
//

#ifndef series_connect_h
#define series_connect_h

#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h> // for c style exit
#include <vector>
#include "component.h"
#include "complex.h"
#include "resistor.h"
#include "inductor.h"
#include "capacitor.h"
#include "slot.h"
#include "composed.h"


using namespace std;


// This function takes in a vector of components in a series and adds up components of the same type
// The function returns a vector of three component
vector<component*> sum_components(vector<component*> &lib){
    // Declare a vector of pointers
    vector<component*> series_lib;
    
    // Declare variables
    double composed_resistance=0, inverse_capacitance=0, composed_inductance=0;
    
    // Get frequency
    double frequency = lib[0]->get_frequency();
    
    // Iterate through the component library "lib" and categorise components
    for(auto vector_it=lib.begin(); vector_it<lib.end(); vector_it++){
        if((*vector_it)->get_type()=="resistor"){
            composed_resistance += (*vector_it)->get_info();
        }
        else if((*vector_it)->get_type()=="capacitor"){
            inverse_capacitance += 1/((*vector_it)->get_info());
        }
        else{
            composed_inductance += (*vector_it)->get_info();
        }
    }
    
    // If a type of component exists in the library, add it to 'series_lib'
    if(composed_resistance>0){
        series_lib.push_back(new resistor("composed_resistor", composed_resistance, frequency));
    }
    if(inverse_capacitance>0){
        series_lib.push_back(new capacitor("composed_capacitor", 1/(inverse_capacitance), frequency));
    }
    if(composed_inductance>0){
        series_lib.push_back(new inductor("composed_inductor", composed_inductance, frequency));
    }
    
    return series_lib;
}


void series_connect(vector<component*> &series_lib, vector<slot*> &slots_lib, const int floor, const double freq, const double v_peak, const double t){
    // Declare a vector of slots
    vector<slot*> series;
    
    const double w = 2*PI*freq; // angular frequency
    
    //string series_type;
    bool RC=false, RL=false, LC=false, RLC=false, R=false, C=false, L=false;
    
    // Determine series type
    if(series_lib.size()==3){
        RLC=true;
    }
    else if(series_lib.size()==2){
        // If there are only two components AND the first is not resistor (given that the components were stored in the order R,C,L), the circuit is LC, necesarily
        if((series_lib[0]->get_type())!="resistor"){
            LC=true;
        }
        // Following above argument, if the first is a resistor and the second is an inductor, the circuit is RL
        else if((series_lib[1]->get_type())=="inductor"){
            RL=true;
        }
        // Similarly, if the second component is a capacitor, the circuit is RC
        else if((series_lib[1]->get_type())=="capacitor"){
            RC=true;
        }
    }
    else if(series_lib.size()==1){
        if(series_lib[0]->get_type()=="resistor"){
            R=true;
        }
        else if(series_lib[0]->get_type()=="capacitor"){
            C=true;
        }
        else if(series_lib[0]->get_type()=="inductor"){
            L=true;
        }
    }
    

    // If RL circuit
    if(RL){
        const double L = series_lib[1]->get_info(), R = series_lib[0]->get_info();
        const double tau = L/R; // Time constant
        const double phi = atan(w*tau); // Phase difference
        double v_resistor = (v_peak/sqrt(1+pow(w*tau, 2)))*cos(w*t-phi);
        double v_inductor = ((v_peak*w*tau)/sqrt(1+pow(w*tau, 2)))*sin(w*t-phi);
        double i_circuit = ((v_peak/R)/sqrt(1+pow(w*tau, 2)))*cos(w*t-phi);
        complex circuit_impedance = series_lib[0]->get_impedance() + series_lib[1]->get_impedance();
        const double circuit_impedancemagnitude = circuit_impedance.getMod();
        series.push_back(new slot());
    }
    
    else if(RC){
        const double C = series_lib[1]->get_info(), R = series_lib[0]->get_info();
        const double phi = atan(1/(R*C*w));
        const double v_resistor = v_peak*cos(w*t+phi)*(R*C*w)/sqrt(1+pow(R*C*w,2));
        const double v_capacitor = v_peak*sin(w*t+phi)/sqrt(1+pow(R*C*w,2));
        const double i_circuit = v_resistor/R;
        complex circuit_impedance = series_lib[0]->get_impedance() + series_lib[1]->get_impedance();
        const double circuit_impedancemagnitude = circuit_impedance.getMod();
    }
    
//    else if(LC){
//        const double C = series_lib[0]->get_info(), L = series_lib[1]->get_info();
//        const double phi = atan(1/sqrt(L*C));
//        const double
//        complex circuit_impedance = series_lib[0]->get_impedance() + series_lib[1]->get_impedance();
//    }
    
    else if(RLC){
        const double R = series_lib[0]->get_info(), L = series_lib[1]->get_info(), C = series_lib[2]->get_info();
        const double w0 = 1/sqrt(L*C);
        const double beta = R/(2*L);
        const double delta = atan((w0*w0-w*w)/(2*beta*w));
        const double i_circuit = (v_peak*w/L)*cos(w*t+delta)/sqrt(pow(w0*w0-w*w,2)+pow(2*beta*w,2));
        const double v_resistor = i_circuit*R;
        const double v_capacitor = v_peak*w0*w0*sin(w*t+delta)/sqrt(pow(w0*w0-w*w,2)+pow(2*beta*w,2));
        const double v_inductor = v_peak*w*w*sin(w*t+delta)/sqrt(pow(w0*w0-w*w,2)+pow(2*beta*w,2));
        complex circuit_impedance = series_lib[0]->get_impedance() + series_lib[1]->get_impedance() + series_lib[2]->get_impedance();
        const double circuit_impedancemagnitude = circuit_impedance.getMod();
        
    }
    else if(R){
        const double R = series_lib[0]->get_info();
        const double v_resistor = v_peak*sin(w*t);
        const double i_resistor = v_resistor/R;
        complex circuit_impedance = series_lib[0]->get_impedance();
    }
    else if (C){
        const double C = series_lib[0]->get_info();
        complex circuit_impedance = series_lib[0]->get_impedance();
        const double circuit_impedancemagnitude = circuit_impedance.getMod();
    }
    
}








#endif /* series_connect_h */

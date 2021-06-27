//
//  main.cpp
//  AC Circuits
//
//  Created by Brett Yang on 17/4/18.
//  Copyright © 2018 Brett Yang. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <stdio.h> // for c style exit
#include <vector>
#include "component.h"
#include "complex.h"
#include "resistor.h"
#include "inductor.h"
#include "capacitor.h"
#include "slot.h"
#include "circuit.h"

using namespace std;

int main() {
    
    cout<<"..............AC Circuits.............."<<endl<<endl;
    // First create a circuit object
    // Declare variables
    double peak_voltage, frequency;
    // Let user select peak voltage and check inputs
    cout<<"Please select a power supply:"<<endl<<"What is the peak supply voltage (in Volts)?"<<endl;
    cin>>peak_voltage;
    while(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<"Error: please enter a numerical value."<<endl;
        cin>>peak_voltage;
    }
    // Let user select AC frequency and check inputs
    cout<<"What is the frequency (in Hertz)?"<<endl;
    cin>>frequency;
    while(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<"Error: please enter a numerical value."<<endl;
        cin>>frequency;
    }
    // Create a circuit object with above information
    circuit c(frequency, peak_voltage);
    
    int choice=10;
    
    while(choice){

        // Print out the menu
        if((c.get_library()).size()==0){
            cout<<"Menu: "<<endl;
            cout<<"1. Create component(s)."<<endl;
            cout<<"0. Exit."<<endl;
            // Let user choose from the menu
            cin>>choice;
            // Check input validity
            while(cin.fail() || choice<0 || choice>1){
                cin.clear();
                cin.ignore();
                cout<<"Error: please enter an integer between 0 and 1."<<endl;
                cin>>choice;
            }
        }
        else if ((c.get_slots()).size()==0) {
            cout<<"Menu: "<<endl;
            cout<<"1. Create component(s)."<<endl;
            cout<<"2. Assemble the circuit with existing components."<<endl;
            cout<<"0. Exit."<<endl;
            // Take user input
            cin>>choice;
            // Check input validity
            while(cin.fail() || choice<0 || choice>2){
                cin.clear();
                cin.ignore();
                cout<<"Error: please enter an integer between 0 and 2."<<endl;
                cin>>choice;
            }
        }
        else{
            cout<<"Menu: "<<endl;
            cout<<"1. Create component(s)."<<endl;
            cout<<"2. Assemble/re-assemble the circuit with existing components."<<endl;
            cout<<"3. Print circuit details."<<endl;
            cout<<"4. Print circuit diagram."<<endl;
            cout<<"0. Exit."<<endl;
            // Take user input
            cin>>choice;
            // Check input validity
            while(cin.fail() || choice<0 || choice>4){
                cin.clear();
                cin.ignore();
                cout<<"Error: please enter an integer between 0 and 4."<<endl;
                cin>>choice;
            }
        }


        // Perform approprate operations according to user's choice
        if (choice==1){
            c.add_components();
        }
        else if (choice==2){
            c.build_circuit();
        }
        else if (choice==3){
            c.print_circuit_info();
        }
        else if (choice==4){
            c.print_diagram();
        }
        else if (choice==0){
            exit(0);
        }
    }

    
    return(0);
}

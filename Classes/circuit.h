//
//  circuit.h
//  AC Circuits
//
//  Created by Brett Yang on 17/4/18.
//  Copyright © 2018 Brett Yang. All rights reserved.
//

#ifndef circuit_h
#define circuit_h

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

using namespace std;


void print_dashes(int num){
    for(int i=0; i<num; i++){
        cout<<"-";
    }
}

class circuit //: public component
{
private:
    double frequency, peak_voltage, magnitude_impedance, phase_difference; // Assume SI units
    vector<component*> circuit_lib; // Store compoenents in a vector of pointers
    vector<slot*> build_lib;
    complex circuit_impedance;
    int floor_count=0;
public:
    // Default constructor
    circuit() : frequency(0), peak_voltage(0) {}
    // Parameterised constructor
    circuit(const double freq, const double vpeak) : frequency(freq), peak_voltage(vpeak) {}
    // Destructor
    ~circuit(){
        // Delete pointers
        for(auto vectorit=circuit_lib.begin(); vectorit<circuit_lib.end(); ++vectorit){
            delete *vectorit;
        }
        for(auto vectorit=build_lib.begin(); vectorit<build_lib.end(); ++vectorit){
            delete *vectorit;
        }
        cout<<"Destroying circuit"<<endl;
    }
    
    
    // Function to search components by name, and returns its index+1 if exists.
    // Otherwise returns 0, which has boolean value false
    int search(const string input_name){
        // Iterate through the circuit list
        for (int i=0; i<circuit_lib.size(); i++) {
            if(input_name==circuit_lib[i]->get_name()){
                return i+1;
            }
        }
        return(1);
    }
    
    // Function to determine if a component exists in the current circuit library
    bool exist(const string input_name){
        // Iterate through the circuit list
        for (int i=0; i<circuit_lib.size(); i++) {
            if(input_name==circuit_lib[i]->get_name()){
                return true;
            }
        }
        return(false);
    }
    
    // Function to set the power supply of the circuit
    // Function to set components
    void add_components() {
        // Declare local variables
        int component_name, component_count;
        
        // Ask user to enter the number of components
        cout<<"How many components would you like to add? Please enter an integer: "<<endl;
        cin>>component_count;
        // Check input validity
        while(cin.fail()){
            // Clear and ignore false values in the input stream
            cin.clear();
            cin.ignore();
            // Ask user to re-enter until correct value is entered
            cout<<"Error: please enter an integer:"<<endl;
            cin>>component_count;
        }
        
        // Iterate using a for loop to ask user choose 'component_count' many components for the circuit
        for(int i=0; i<component_count; i++) {
            cout<<"Please choose the type of component you would like to add: Enter 1 for capacitor, 2 for resistor, 3 for inductor"<<endl;
            cin>>component_name;
            // Check input validity with a while loop
            while(cin.fail() || component_name<1 || component_name>3){
                // Clear and ignore false values in the input stream
                cin.clear();
                cin.ignore();
                // Ask user to re-enter until correct value is entered
                cout<<"Error: please enter an integer within the range [1,3]:"<<endl;
                cin>>component_name;
            }
            
            // Take store components by cases
            if(component_name==1){ // add capacitor
                // Ask user to set name for this component
                string name_tag;
                cout<<"Please enter a name for your capacitor: "<<endl;
                cin>>name_tag;
                // Check input
                if(circuit_lib.size()==0){
                    while(cin.fail()){
                        // Clear and ignore false values in the input stream
                        cin.clear();
                        cin.ignore();
                        // Ask user to re-enter until correct value is entered
                        cout<<"Error: the name you entered already exists in this circuit, please enter a different name:"<<endl;
                        cin>>name_tag;
                    }
                }
                else{
                    while(cin.fail() || (circuit_lib[(this->search(name_tag))-1]->get_name()==name_tag)){
                        // Clear and ignore false values in the input stream
                        cin.clear();
                        cin.ignore();
                        // Ask user to re-enter until correct value is entered
                        cout<<"Error: the name you entered already exists in this circuit, please enter a different name:"<<endl;
                        cin>>name_tag;
                    }
                }
                // Ask user to enter capacitance of the capacitor
                double cap;
                cout<<"Please enter the capacitance (unit: Farrad): "<<endl;
                cin>>cap;
                // Check input validity
                while(cin.fail()){
                    // Clear and ignore false values in the input stream
                    cin.clear();
                    cin.ignore();
                    // Ask user to re-enter until correct value is entered
                    cout<<"Error: please enter a numeric value:"<<endl;
                    cin>>cap;
                }
                // Construct capacitor object using parameterised constructor and add to library
                circuit_lib.push_back(new capacitor(name_tag, cap, frequency));
            }
            
            else if(component_name==2){ // add resistor
                // Ask user to set name for this component
                string name_tag;
                cout<<"Please enter a name for your resistor: "<<endl;
                cin>>name_tag;
                // Check input
                if(circuit_lib.size()==0){
                    while(cin.fail()){
                        // Clear and ignore false values in the input stream
                        cin.clear();
                        cin.ignore();
                        // Ask user to re-enter until correct value is entered
                        cout<<"Error: the name you entered already exists in this circuit, please enter a different name:"<<endl;
                        cin>>name_tag;
                    }
                }
                else{
                    while(cin.fail() || (circuit_lib[(this->search(name_tag))-1]->get_name()==name_tag)){
                        // Clear and ignore false values in the input stream
                        cin.clear();
                        cin.ignore();
                        // Ask user to re-enter until correct value is entered
                        cout<<"Error: the name you entered already exists in this circuit, please enter a different name:"<<endl;
                        cin>>name_tag;
                    }
                }
                // Ask user to enter the resistancse of the resistor
                double res;
                cout<<"Please enter the resistance (unit: Ohm): "<<endl;
                cin>>res;
                // Check input validity
                while(cin.fail()){
                    // Clear and ignore false values in the input stream
                    cin.clear();
                    cin.ignore();
                    // Ask user to re-enter until correct value is entered
                    cout<<"Error: please enter a numeric value: "<<endl;
                    cin>>res;
                }
                // Construct resistor object using parameterised constructor and add to library
                circuit_lib.push_back(new resistor(name_tag, res, frequency));
            }
            
            else{ // add inductor
                // Ask user to set name for this component
                string name_tag;
                cout<<"Please enter a name for your inductor: "<<endl;
                cin>>name_tag;
                // Check input
                if(circuit_lib.size()==0){
                    while(cin.fail()){
                        // Clear and ignore false values in the input stream
                        cin.clear();
                        cin.ignore();
                        // Ask user to re-enter until correct value is entered
                        cout<<"Error: the name you entered already exists in this circuit, please enter a different name:"<<endl;
                        cin>>name_tag;
                    }
                }
                else{
                    while(cin.fail() || (circuit_lib[(this->search(name_tag))-1]->get_name()==name_tag)){
                        // Clear and ignore false values in the input stream
                        cin.clear();
                        cin.ignore();
                        // Ask user to re-enter until correct value is entered
                        cout<<"Error: the name you entered already exists in this circuit, please enter a different name:"<<endl;
                        cin>>name_tag;
                    }
                }
                // Ask user to enter the inductance of the inductor
                double ind;
                cout<<"Please enter the inductance (unit: Henry): "<<endl;
                cin>>ind;
                // Check input validity
                while(cin.fail()){
                    // Clear and ignore false values in the input stream
                    cin.clear();
                    cin.ignore();
                    // Ask user to re-enter until correct value is entered
                    cout<<"Error: please enter a numeric value:"<<endl;
                    cin>>ind;
                }
                // Construct inductor object using parameterised constructor and add to library
                circuit_lib.push_back(new inductor(name_tag, ind, frequency));
            }
        }
    }
    
    // Function to assemble the circuit
    void build_circuit() {
        // First delete existing objects (if there is any)
        for(auto vectorit=build_lib.begin(); vectorit<build_lib.end(); ++vectorit){
            delete *vectorit;
        }
        
        // Ask user to choose the number of loops to build
        int choice;
        cout<<"Please enter the number of loops you would like to wire to the power supply (for parallel circuit, please enter an integer greater than 1): "<<endl;
        cin>>choice;
        // Check input
        while(cin.fail() || choice>=10 || choice<1){
            // Clear and ignore false values in the input stream
            cin.clear();
            cin.ignore();
            // Ask user to re-enter until correct value is entered
            cout<<"Error: please enter a positive integer less than 10."<<endl;
            cin>>choice;
        }
        
        // Set the number of loops
        floor_count=choice;
        
        cout<<"..... Buiding circuit ....."<<endl;
        
        // First create an empty slot for power source
        build_lib.push_back(new slot(*new resistor(), 0));
        
        int slot_count=0;
        for(int loop_count=0; loop_count<choice; loop_count++){
            int floor = loop_count+1;
            
            cout<<"Loop number "<<loop_count+1<<": "<<endl;
            
            // Ask user to choose which components to add
            string comp_name;
            cout<<"Which component would you like to add in this loop? (enter a name) "<<endl;
            cin>>comp_name;
            // Check input validity
            while(cin.fail() || !(this->exist(comp_name))){
                // Clear and ignore false values in the input stream
                cin.clear();
                cin.ignore();
                // Ask user to re-enter until correct value is entered
                cout<<"Error: please enter a component within the current circuit library: "<<endl;
                for(auto vectorit=circuit_lib.begin(); vectorit<circuit_lib.end(); vectorit++){
                    cout<<(*vectorit)->get_name()<<"\t";
                }
                cout<<endl;
                cin>>comp_name;
            }
            
            // Add component to the circuit
            build_lib.push_back(new slot(*circuit_lib[(this->search(comp_name))-1], floor));
            slot_count++;
            // Point the first component to the power source
            build_lib[slot_count]->join_tail(*build_lib[0]);
            
            // Ask user to add another component
            int more; // Index_count is used to locate 'slots' in vector build_lib
            cout<<"Would you like to add another component? Enter 0 to exit, or any other key to continue: "<<endl;
            cin>>more;
            if(cin.fail()){
                // Clear and ignore false values in the input stream
                cin.clear();
                cin.ignore();
                more=1;
            }
            while(more!=0){
                // Ask user to choose the components
                cout<<"Which component would you like to add in this loop? (enter a name) "<<endl;
                cin>>comp_name;
                // Check input validity
                while(cin.fail() || !(this->exist(comp_name))){
                    // Clear and ignore false values in the input stream
                    cin.clear();
                    cin.ignore();
                    // Ask user to re-enter until correct value is entered
                    cout<<"Error: please enter a component within the current circuit library: "<<endl;
                    for(auto vectorit=circuit_lib.begin(); vectorit<circuit_lib.end(); vectorit++){
                        cout<<(*vectorit)->get_name()<<"\t\t";
                    }
                    cout<<endl;
                    cin>>comp_name;
                }
                
                // Add component to the circuit (build_lib)
                build_lib.push_back(new slot(*circuit_lib[(this->search(comp_name))-1], floor));
                // Increase slot_count by 1
                slot_count++;
                // Point the previous slot's head to this slot
                build_lib[slot_count-1]->join_head(*build_lib[slot_count]);
                // Point this slot's tail to the previous slot
                build_lib[slot_count]->join_tail(*build_lib[slot_count-1]);
                
                
                cout<<"Would you like to add another component? Enter 0 to exit or any other key to continue: "<<endl;
                cin>>more;
            }
            // At the end of each loop, point the last slot's head to the power source
            build_lib[slot_count-1]->join_head(*build_lib[0]);
            
        }
        
        // Calculate the impedance and phase differences by cases:
        // If the circuit contains only one loop (series)
        if(choice==1){
            for(auto vectorit=circuit_lib.begin(); vectorit<circuit_lib.end(); vectorit++){
                // The total impedance is the sum of each component's impedance
                circuit_impedance = circuit_impedance + (*vectorit)->get_impedance();
            }
        }
        // If the circuit contains more than one loop (parallel)
        else if(choice!=1){
            complex reciprocal_impedance; // The inverse of Z: 1/Z
            complex unity(1,0); // This is equivalent to the 1+0i but as a complex object
            // The total impedance is the reciprocal of the sum of the reciprocal of each component's impedance
            // Z = 1/SUM(1/Zi)
            for(auto vectorit=circuit_lib.begin(); vectorit<circuit_lib.end(); vectorit++){
                reciprocal_impedance = reciprocal_impedance + unity/((*vectorit)->get_impedance());
            }
            circuit_impedance = unity/reciprocal_impedance;
        }
        
        // Assign values to magnitude_impedance
        magnitude_impedance = circuit_impedance.getMod();
        
        // Calculate the total phase shift of the circuit from impedance
        // The phase difference is given by: atan(imp_im/imp_re)
        // However division by zero is restricted, here we calculate phase difference by cases:
        const double imp_im = circuit_impedance.getImg(), imp_re = circuit_impedance.getReal();
        // If the real part of impedance is zero and imaginery part is negative, arctan approaches -π/2
        if (imp_re==0 && imp_im<0) { phase_difference = -PI/2; }
        // If the real part of impedance is zero and imaginery part is positive, arctan approaches π/2
        else if (imp_re==0 && imp_im>0) { phase_difference = PI/2; }
        // And for the defined range of arctan function, use 'atan' from standard math library
        else { phase_difference = atan(imp_im/imp_re); }
        
    }
    
    
    // Function to print circuit diagram
    void print_diagram(){
        
        // Declare a vector to store the number of components in each floor
        vector<int> floor_lib;
        for(int f=0; f<=floor_count; f++) {
            int this_floor=0;
            // Iterate through the list and find the number of components in this loop
            for(auto vectorit=build_lib.begin(); vectorit<build_lib.end(); vectorit++){
                if((*vectorit)->get_floor()==f){ this_floor++; }
            }
            // Append this info to the vector
            floor_lib.push_back(this_floor); // Note: this library can be indexed directly by floor numbers
        }
        
        // Declare constant 'longest' - the number of components in the longest loop
        int longest=0;
        
        // Here we will print out the diagram in a rectangular shape
        // The length of each loop depends on the longest loop
        // Find the longest loop if the circuit is parallel
        for(auto vectorit=floor_lib.begin(); vectorit<floor_lib.end(); vectorit++){
            if((*vectorit)>longest) { longest=(*vectorit); }
        }
        
        // Calculate the size (number of characters) of the rectanglular diagram width
        int width = (longest+1)*4+longest*2; // Each component takes up two characters
        
        // We will print out four dashes between each component, as well as vertices
        // Example:
        //          ----R2----L2----C2----
        //          |                    |
        //          ------R1------L1------
        //          |                    |
        //          ----------V-----------
        
        
        // Now print the circuit from top floor to the 1st floor, leave out the source
        for(int f=floor_count;f>0;f--){
            const int slot_count = floor_lib[f];
            int wire_segament_length = ((width-(slot_count*2))-((width-(slot_count*2))%(slot_count+1)))/(slot_count+1);
            int char_count = 0;
            
            cout<<"\t\t\t";
            
            // Print from left to right the components and wire segaments
            for(auto vectorit=build_lib.begin(); vectorit<build_lib.end(); vectorit++){
                if((*vectorit)->get_floor()==f){
                    const string type_char = (((*vectorit)->get_component())->get_type()).substr(0,1);
                    const int floor_num = (*vectorit)->get_floor();
                    for(int j=0;j<wire_segament_length; j++) { cout<<"-"; char_count++; }
                    cout<<type_char<<floor_num; char_count+=2;
                }
            }
            
            // Print the right-most wire segament and end this line
            print_dashes(width-char_count);
            cout<<endl;
            
            // Now print wires in the transverse direction
            cout<<"\t\t\t"<<"|";
            for(int k=0; k<width-2; k++) { cout<<" "; }
            cout<<"|"<<endl;
        }
        
        
        
        // Finally, print out the power source
        cout<<"\t\t\t";
        // If width is an odd number
        if((width%2)) {
            const int wire_segament = (width-1)/2;
            print_dashes(wire_segament);
            cout<<"V";
            print_dashes(wire_segament);
        }
        else {
            const int wire_segament = (width-2)/2;
            print_dashes(wire_segament);
            cout<<"V-";
            print_dashes(wire_segament);
        }
        cout<<endl;
    }
    
    
    void print_circuit_info(){
        cout<<"Circuit:"<<endl;
        // Print out info for power supply
        cout<<"\t\t"<<"Power Supply: "<<endl<<"\t\tPeak Volatage: "<<peak_voltage<<" Volt(s)\tPeak Current: "<<peak_voltage/magnitude_impedance<<" Amp(s)\tFrequency: "<<frequency<<" Hz"<<endl;
        cout<<"\t\t\t"<<"Magnitude of impedance: "<<magnitude_impedance<<"\tPhase shift: "<<phase_difference<<endl<<endl;
        
        // Then print out each component's info
        for(auto vectorit=build_lib.begin(); vectorit<build_lib.end(); vectorit++){
            const string type_char = (((*vectorit)->get_component())->get_type()).substr(0,1);
            const string name_char = ((*vectorit)->get_component())->get_name();
            const int floor_num = (*vectorit)->get_floor();
            if(floor_num>0){
                cout<<"\t\t"<<name_char<<" ("<<type_char<<floor_num<<"): "<<endl;
                component* comp_pointer = (*vectorit)->get_component();
                cout<<"\t\t\t"; comp_pointer->print_info();
                cout<<"\t\t\tMagnitude of impedance"<<comp_pointer->get_magnitudeimpedance()<<" Ohm(s)\tPhase shift: "<<comp_pointer->get_phasedifference()<<" Rad"<<endl<<endl;
            }
        }
    }
    
    
    // Access functions
    vector<component*> get_library() {
        return circuit_lib;
    }
    vector<slot*> get_slots() {
        return build_lib;
    }
    
    
};





#endif /* circuit_h */

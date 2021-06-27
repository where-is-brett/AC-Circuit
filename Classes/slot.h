//
//  slot.h
//  AC Circuits
//
//  Created by Brett Yang on 01/05/2018.
//  Copyright © 2018 Brett Yang. All rights reserved.
//
//  An object of this class points to a component within a circuit and stores all the connections between this component and other components.
//  Such connections are stored as pointers within one slot's 'head' or 'tail' to other slot's 'head' or 'tail'
//  This allows the constructions of a circuit in the similar fashion as a real circuit, as each component has one 'head' and 'tail' in reality
//

#ifndef slot_h
#define slot_h

#include <iostream>
#include <vector>
#include "component.h"


using namespace std;

class slot {
    // Friend function to overload operator<<
    friend ostream & operator<<(ostream &os, const slot &s);
private:
    component *component_pointer;
    vector<slot*> head, tail;
//    double vpeak_left, ipeak_left, phasediff_left;
    int floor=0; // This identifies the series in a parallel circuit where the slot is located
    
public:
    // Default constructor
    slot() : floor(0) {}
    // Parameterised constructor
    slot(component &comp, const int fl) :  floor(fl)
    {
        component_pointer = &comp;
    }
    // Destructor
    ~slot(){
        // Delete all pointers
//        delete component_pointer;
//        for(auto vectorit=head.begin(); vectorit<head.end(); ++vectorit){
//            delete *vectorit;
//        }
//        for(auto vectorit=tail.begin(); vectorit<tail.end(); ++vectorit){
//            delete *vectorit;
//        }
    }
    
    
    // Access functions
    int get_floor() { return floor; }
    vector<slot*> get_head(){
        return head;
    }
    vector<slot*> get_tail(){
        return tail;
    }
    component * get_component(){
        return component_pointer;
    }
    // The following functions should only been called once head and tails had been set
    int head_length(){
        return head.size();
    }
    int tail_length(){
        return tail.size();
    }
    
    // Copy constructor
    slot(slot &s){
        floor = s.get_floor();
        component_pointer = s.get_component();
        head = s.get_head();
        tail = s.get_tail();
    }
    
    // Functions to set/alter heads and tails
    void join_tail(slot &s){
        tail.push_back(new slot(s));
    }
    void join_head(slot &s){
        head.push_back(new slot(s));
    }
    
};

// Overload insertion to output stream for matrices
ostream & operator<<(ostream &os, slot &s)
{
    const string type = (s.get_component())->get_type();
    if(type=="resistor") { os<<"R"; }
    else if(type=="capacitor") { os<<"C"; }
    else if(type=="inductor") { os<<"L"; }
    os<<s.get_floor();
    return os;
}

#endif /* slot_h */

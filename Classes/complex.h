//
//  complex.h
//  AC Circuits
//
//  Created by Brett Yang on 17/4/18.
//  Copyright © 2018 Brett Yang. All rights reserved.
//
//
//  This header file contains a complex class definition which allows the manipulation of complex objects and
//
//

#ifndef complex_h
#define complex_h


#include<iostream>
#include<cmath>
#include<string>

using namespace std;

const double PI = 3.1415926535897932384626433832795028; // Define PI - from Wolfram

class complex
{
    // Make function to overload operator<< a friend
    friend ostream & operator<<(ostream &os, const complex &z);
    
    // Make function to overload operator>> a friend
    friend istream& operator>>(istream &is, complex &z);
    
private:
    double re,im;
    
public:
    // Constructors & destructor
    complex(){re=im=0;}
    complex(double r, double i){re=r; im=i;}
    ~complex(){cout << "Destroying..." << endl;}
    
    // Return real component
    double getReal() const {return re;}
    
    // Return imaginary component
    double getImg() const {return im;}
    
    // Function to set the real part of a complex object
    void setReal(double realPart){
        re = realPart;
    }
    
    // Function to set the imaginary part of a complex object
    void setImg(double imaginaryPart){
        im = imaginaryPart;
    }
    
    // Return modulus
    double getMod() const {return sqrt(re*re + im*im);}
    
    // Return argument
    double getArg() const
    {
        if (re==im==0) {
            return false;
        }
        else if (re>0 && im==0) {
            return 0;
        }
        else if (re<0 && im==0) {
            return PI;
        }
        else {
            return 2*atan((sqrt(re*re+im*im)-re)/(im));
        }
    }
    
    // Return complex number
    complex show() const {
        complex cplxNum(re, im);
        return cplxNum;
    }
    
    // Return complex conjugate
    complex getConjugate() const {
        complex conjugate(re, -im);
        return conjugate;
    }
    
    // Overload + operator for addition
    complex operator+(const complex &v) const {
        complex cplxNum(re+v.getReal(), im+v.getImg());
        return cplxNum;
    }
    
    // Overload - operator for subtraction
    complex operator-(const complex &v) const {
        complex cplxNum(re-v.getReal(), im-v.getImg());
        return cplxNum;
    }
    
    // Overload * operator for multiplication, z1*z2
    complex operator*(const complex &v) const {
        complex cplxNum(re*v.getReal()-im*v.getImg(), im*v.getReal()+re*v.getImg());
        return cplxNum;
    }
    
    // Overload / operator for division, z1/z2
    complex operator/(const complex &v) const {
        const double c = v.getReal();
        const double d = v.getImg();
        const double a = re;
        const double b = im;
        complex cplxNum((a*c+b*d)/(c*c+d*d), (b*c-a*d)/(c*c+d*d));
        return cplxNum;
    }
};

// To get cout to accept a complex object after the insertion operator, overload the insertion operator to recognise an ostream object on the left and a comple on the right.
// The overloaded << operator function must then be declared as a friend of class complex so it can access the private data within a complex object.
ostream& operator<<(ostream &os, const complex &z)
{
    if (z.im >= 0)
    {
        os << z.re << "+" << z.im << "i" << endl;
    }
    else
    {
        os << z.re << z.im << "i" << endl;
    }
    return os;
}

// Similarly for input stream
istream& operator>>(istream &is, complex &z)
{
    // Declare variables
    double realPart, imaginaryPart;
    // Extract real and imaginary parts from istream and save to above variables
    is >> realPart >> imaginaryPart;
    // Check if input has the correct type, retake inputs if not
    while(cin.fail())
    {
        cout<<"Error: please enter numerical values only."<<endl;
        is.clear();
        is.ignore();
        is >> realPart >> imaginaryPart;
    }
    // Assign values to real and imaginary parts of a complex number in istream
    z.setReal(realPart);
    z.setImg(imaginaryPart);
    return is;
}

#endif /* complex_h */

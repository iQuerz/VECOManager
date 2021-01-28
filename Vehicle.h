#pragma once
#include "Refill.h"
#include <iostream>

using namespace std;

class Vehicle {

private:
    Refill* _refills;
    int _len;
    string _manufacturer;
    string _model;

public:
    Vehicle(string manufacturer, string model);
    Vehicle(){}
    ~Vehicle();
    inline string getManufacturer(){ return _manufacturer; }
    inline string getModel(){ return _model; }
    void refill(Refill refill) { _refills[_len++] = refill; }
    double lastAvg(){ return _refills[_len-1].getAvg(); }
    double lastDist(){return _refills[_len-1].getDist();}
    inline int len() { return _len; }
    Refill* getRefills() { return _refills; }
    double getAvg();
    double getDist();

};
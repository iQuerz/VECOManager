#include "Vehicle.h"

Vehicle::Vehicle(string manufacturer, string model){
    _refills = new Refill[100];
    _manufacturer = manufacturer;
    _model = model;
    _len = 0;
}
Vehicle::~Vehicle(){
    delete[] _refills;
}

double Vehicle::getAvg(){
    double sum = 0;
    for(int i = 0;i<_len;i++){
        sum += _refills[i].getAvg();
    }
    return sum/3;
}
double Vehicle::getDist(){
    double sum = 0;
    for(int i = 0;i<_len;i++){
        sum+=_refills[i].getDist();
    }
    return sum;
}
#pragma once
#include "Vehicle.h"
#include <string>

class Manager {

private:
    Vehicle* _vehicles;
    int _len;
    int _index;

    void cars();
    void select(int index);
    void help();
    void print();
    void refill(); //command func
    void refill(Refill r) { _vehicles[_index].refill(r); } //actual execution

public:
    Manager();
    ~Manager();
    void command(string com);
    void load();
    void save();
    void add(string manufacturer, string model);

};

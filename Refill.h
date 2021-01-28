#pragma once
class Refill{
    
private:
    double _amount;
    double _distance;
    double _cost;

public:
    Refill(double amount, double distance, double cost)
    :_amount(amount),_distance(distance),_cost(cost){}
    Refill()
    :_amount(0),_distance(0),_cost(0){}

    inline double getAmt()  { return _amount; }
    inline double getDist() { return _distance; }
    inline double getCost() { return _cost; }
    inline double getAvg()  { return (_amount/_distance) * 100; }
};
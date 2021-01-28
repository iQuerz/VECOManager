#include "Manager.h"
#include <fstream>
#include "Windows.h"
#include <iostream>

using namespace std;

Manager::Manager(){
    _vehicles = new Vehicle[10];
    _len = -1;
    _index = 0;
}
Manager::~Manager(){
    delete[] _vehicles;
}

void Manager::command(string com){
    if(com == "help"){
        Manager::help();
        return;
    }
    else if(com == "cars"){
        Manager::cars();
        return;
    }
    else if(com == "print"){
        Manager::print();
        return;
    }
    else if(com == "refill"){
        Manager::refill();
        return;
    }
    else if(com == "exit" || com == "end"){
        cout << "   Write \'" << com << "\' again to close the application." << endl;
        return;
    }
    else{
        cout << "   \'" << com << "\' is not recognised as an internal command. For additional help type \'help\'." << endl << endl;
        return;
    }
}

void Manager::help(){
    cout << endl;
    cout << "Welcome to help panel. Note that, if you have any further troubles with" << endl;
    cout << "your app, you can always contact the developer: nikola.rasic@elfak.rs" << endl;
    cout << endl << "| list of available commands(version 1.2):" << endl;
    cout << "| \'help\' - Brings up the help panel." << endl;
    cout << "| \'cars\' - Prints out all available cars. This allows you to change your selected car." << endl;
    cout << "| \'refill\' - Allows you to add a new refill to your selected car." << endl;
    cout << "| \'print\' - Prints out stats for the selected car." << endl;
    cout << "| \'exit\' - Saves changes and exits the application." << endl;
    cout << "| \'end\' - Saves changes and exits the application." << endl << endl;
}
void Manager::cars(){
    cout << endl;
    cout << "Index      Car name" << endl;
    cout << "-----      --------" << endl;
    for(int i = 0;i<_len+1;i++){
        cout << " #" << i+1 << "        " << _vehicles[i].getManufacturer() << " " << _vehicles[i].getModel() << endl;    
    }
    cout << endl << "To select a different car, use command \'select <index>\' (ex. select 2)." << endl;
    while(true){
        cout << endl << "VECO>";
        string command;
        getline(cin, command);
        if(command.substr(0,6) == "select"){
            command.erase(0,7);
            try{
                int index = stoi(command);
                if(index < 1){
                    cout << "   \'" << command << "\' is not a valid index." << endl;
                }
                else if(index - 1 > _len){
                    cout << "   Silly! You don't have that much cars!" << endl;
                }
                else {
                    Manager::select(index);
                    return;
                }
            }
            catch(exception e){
                cout << "   \'" << command << "\' is not a valid index." << endl;
            }
        }
        else{
            Manager::command(command);
            return;
        }
    }
}
void Manager::select(int index){
    _index = index-1;
    cout << "\'" << _vehicles[_index].getManufacturer() << " " << _vehicles[_index].getModel() << "\' is now the selected vehicle." << endl << endl;
}
void Manager::print(){
    cout << endl << "Displaying data for " << _vehicles[_index].getManufacturer() << " " << _vehicles[_index].getModel() << ": " << endl;
    cout << "   You've traveled " << _vehicles[_index].getDist() << "km since you own it."<<endl;
    cout << "   Your overall average fuel consumption is " << _vehicles[_index].getAvg() << "L per 100km." << endl;
    cout << "   You drove for " << _vehicles[_index].lastDist() << "km on your last trip and consumed, on average, " << _vehicles[_index].lastAvg() << "L per 100km." << endl;
    cout << endl;
}
void Manager::refill(){
    cout << "   You are about to add new data to your cars. Make sure you have selected the right car." << endl;
    cout << "The changes you are about to make are irreversible[ver1.0]. Please make sure you are not making any errors." << endl;
    cout << "Currently selected car: \'" << _vehicles[_index].getManufacturer() << " " << _vehicles[_index].getModel() << "\'." << endl;
    cout << endl << "Are you sure you want to continue?[Y/N]:";
    string command;
    
    while(true){
        getline(cin,command);
        if(command == "Y" || command == "y"){
            cout << "Enter refill data, in format <amount> <distance> <cost>" << endl;
            cout << "   example: \'40.56 912.2 5400.0" << endl << "VECO>";
            double amt, dist, cost;
            try{
                cin >> amt >> dist >> cost;
                cout << endl;
                Refill temp(amt,dist,cost);
                Manager::refill(temp);
                break;
            }
            catch(exception e){
                cout << "   Wrong format. Please try again." << endl <<"VECO>";
                ofstream log("log.txt",ofstream::app);
                log << e.what() << endl;
                log.close();
            }
        }
        else if(command == "N" || command == "n"){
            cout << "   Action aborted." << endl << endl;
            return;
        }
        else{
            cout << "\'" << command << "\' is not recognised as a valid answer, please try again.[Y/N]:";
        }
    }
}

void Manager::load(){
    string s = "data.txt";
    ifstream is(s);
    while(!is.eof()){
        getline(is, s);
        if(s[0] == '%'){
            _len++;
            string temp;
            s.erase(0,1);
            getline(is,temp);
            _vehicles[_len] = Vehicle(s,temp);
        }
        if(s[0] == '-'){
            s.erase(0,1);

            //amt
            int temp1 = s.find(' ');
            string t = s.substr(0,temp1);
            double amt = stod(t);
            s.erase(0,temp1+1);
            //dist
            temp1 = s.find(' ');
            t = s.substr(0, temp1);
            double dist = stod(t);
            s.erase(0,temp1+1);
            //cost
            temp1 = s.find(' ');
            t = s.substr(0,temp1);
            double cost = stod(t);

            Refill temp(amt,dist,cost);
            _vehicles[_len].refill(temp);
        }
    }
    is.close();
}
void Manager::save(){
    string s = "data.txt";
    ofstream os(s);
    for(int i = 0;i<=_len;i++){
        os << "%" << _vehicles[i].getManufacturer() << endl;
        os << _vehicles[i].getModel() << endl;
        for(int j = 0;j<_vehicles[i].len();j++){
            os << "-" << _vehicles[i].getRefills()[j].getAmt() << " ";
            os << _vehicles[i].getRefills()[j].getDist() << " ";
            os << _vehicles[i].getRefills()[j].getCost() << endl;
        }

    }
    os.close();
}
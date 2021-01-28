#include "Manager.h"
#include <iostream>
#include <string>

using namespace std;

// int main(){
//     string s = "37 700 5750";
//     int temp = s.find(' ');
//     string t = s.substr(0,temp);
//     s.erase(0,temp+1);
//     cout<<t<<endl << s;
//     return 0;
// }


int main(){
    bool success;
    Manager manager;
    cout << "loading data..." << endl;
    manager.load();
    cout << "done!" << endl;
    cout << "-------- Vehicle Economy version 1.2 --------" << endl;
    cout <<"------ for additional help type \'help\' ------" << endl;
    string command;
    cout << "VECO>";
    getline(cin,command);
    
    while(command != "exit" && command != "end"){
        manager.command(command);
        cout << "VECO>";
        getline(cin, command);
    }
    
    manager.save();
    return 0;
}
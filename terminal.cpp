#include <iostream>
#include "terminal.h"
#include "network.h"
#include <sstream>

using namespace std;

commands get_command(string command){
    if(command == "create_network") return create_network;
    if(command == "create_router") return create_router;
    if(command == "remove_router") return remove_router;
    if(command == "access_router") return access_router;
    return unknown;
}

bool check_number(string str){
    for(int i = 0; i < str.size(); i++){
        if(!isdigit(str[i])){
            return false;
        }
    }
    return true;
}

void run_program(){
    Network *network = new Network(1);
    string input;
    string command_str;
    commands command;
    string ip;
    string arg;
    int port_id;
    int router_id = -1;

    while(true){
        cout << ">>> ";
        getline(cin, input);
        istringstream iss(input);
        iss >> command_str;
        command = get_command(command_str);
        cout << command_str << endl;
        switch (command){
            case create_router:
                iss >> arg;
                if(!check_number(arg)){
                    cout << "A valid router ID must be provided\n";
                    break;
                }
                router_id = stoi(arg);
                // Router *router = new Router(router_id);
                network->add_router(router_id);
                
                break;
            default:
                break;
        }
    }
}
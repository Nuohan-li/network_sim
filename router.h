#pragma once

#include <iostream>
#include <string>

using namespace std;

#define LINK_UP true
#define LINK_DOWN false

class Router{

private:
    int router_id;
    string ip_addr;
    bool ports[20];

public:
    Router(int router_id);
    ~Router();

    // control functions
   
    // port functions
    void print_port_status();
    bool *get_ports();
    void set_port_status(int port_id, bool status);
    bool get_port_status(int port_id);
    void connect_link(int port_id, Router *remote_router, int remote_port_id);
    void remove_link();

    // getter and setter
    int get_router_id();
    void set_router_id(int id);
    string get_ip();
    void set_ip(string ip);
    
};




#pragma once

#include <iostream>
#include <string>

using namespace std;

#define LINK_UP true
#define LINK_DOWN false

struct MAC_table_entry{
    string remote_end_ip;
    int ingress_port;
    int egress_port;
};

class Router{

private:
    int router_id;
    string ip_addr;
    bool ports[20];
    string buffer;
    MAC_table_entry mtable[20]; // this is not an actual MAC table, as MAC addresses for ports are not implemented yet
    int mtable_entry_num;
public: 
    // router function
    Router(int router_id);
    ~Router();
    void send(Router *remote_end, string msg);
    void receive(Router *remote_end);
    void add_mtable_entry(string remote_end_ip, int ingress_port, int egress_port);
    void print_MAC_table();
    // control functions

    // port functions
    void print_port_status();
    bool *get_ports();
    void set_port_status(int port_id, bool status);
    bool get_port_status(int port_id);

    // getter and setter
    int get_router_id();
    void set_router_id(int id);
    string get_ip();
    void set_ip(string ip);
    
};




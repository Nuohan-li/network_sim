#include "router.h"
// #include "network.h"
#include <cstring>

// router functions

Router::Router(int router_id){
    memset(ports, 0, sizeof(ports));
    set_router_id(router_id);
}

Router::~Router(){
    
}

// ports 
bool * Router::get_ports(){
    return ports;
}

bool Router::get_port_status(int port_id){
    return ports[port_id - 1];
}

void Router::set_port_status(int port_id, bool status){
    ports[port_id - 1] = status;
}

void Router::print_port_status(){
    cout << "===============================================================\n";
    cout << "Router " << get_router_id() << " port status\n";
    cout << "===============================================================\n";
    cout << "Port number        " << "Link status       \n";
    cout << "  1                " << "  " << (get_port_status(0) == LINK_UP ? "up" : "down") << endl; 
    cout << "  2                " << "  " << (get_port_status(1) == LINK_UP ? "up" : "down") << endl; 
    cout << "  3                " << "  " << (get_port_status(2) == LINK_UP ? "up" : "down") << endl; 
    cout << "  4                " << "  " << (get_port_status(3) == LINK_UP ? "up" : "down") << endl; 
    cout << "  5                " << "  " << (get_port_status(4) == LINK_UP ? "up" : "down") << endl; 
    cout << "  6                " << "  " << (get_port_status(5) == LINK_UP ? "up" : "down") << endl; 
    cout << "  7                " << "  " << (get_port_status(6) == LINK_UP ? "up" : "down") << endl; 
    cout << "  8                " << "  " << (get_port_status(7) == LINK_UP ? "up" : "down") << endl; 
    cout << "  9                " << "  " << (get_port_status(8) == LINK_UP ? "up" : "down") << endl; 
    cout << "  10               " << "  " << (get_port_status(9) == LINK_UP ? "up" : "down") << endl; 
    cout << "  11               " << "  " << (get_port_status(10) == LINK_UP ? "up" : "down") << endl; 
    cout << "  12               " << "  " << (get_port_status(11) == LINK_UP ? "up" : "down") << endl; 
    cout << "  13               " << "  " << (get_port_status(12) == LINK_UP ? "up" : "down") << endl; 
    cout << "  14               " << "  " << (get_port_status(13) == LINK_UP ? "up" : "down") << endl; 
    cout << "  15               " << "  " << (get_port_status(14) == LINK_UP ? "up" : "down") << endl; 
    cout << "  16               " << "  " << (get_port_status(15) == LINK_UP ? "up" : "down") << endl; 
    cout << "  17               " << "  " << (get_port_status(16) == LINK_UP ? "up" : "down") << endl; 
    cout << "  18               " << "  " << (get_port_status(17) == LINK_UP ? "up" : "down") << endl; 
    cout << "  19               " << "  " << (get_port_status(18) == LINK_UP ? "up" : "down") << endl; 
    cout << "  20               " << "  " << (get_port_status(19) == LINK_UP ? "up" : "down") << endl; 
    cout << endl;
}

// getters and setters
void Router::set_ip(string ip){
    ip_addr = ip;
}

string Router::get_ip(){
    return ip_addr;
}

void Router::set_router_id(int id){
    router_id = id;
}

int Router::get_router_id(){
    return router_id;
}


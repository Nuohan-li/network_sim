#include "port.h"

Port::Port(){

}

Port::~Port(){
    
}

int Port::get_port_id(){
    return port_id;
}
void Port::set_port_id(int id){
    port_id = id;
}

string Port::get_MAC_addr(){
    return MAC_addr;
}

void Port::set_MAC_addr(string mac){
    MAC_addr = mac;
}
bool Port::get_port_status(){
    return port_status;
}

void Port::set_port_status(bool status){
    port_status = status;
}
#include "port.h"
#include "misc.h"
#include <string.h>

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

uint8_t* Port::get_MAC_addr(){
    return MAC_addr;
}

void Port::set_MAC_addr(uint8_t *mac){
    memcpy(MAC_addr, mac, 6);
}
bool Port::get_port_status(){
    return port_status;
}

void Port::set_port_status(bool status){
    port_status = status;
}

void Port::print_port_state(){
    cout << "Port ID : " << port_id << endl;
    if(port_status){
        cout << "State: UP\n";
    } else{
        cout << "State: DOWN\n";
    }
    print_byte_array(MAC_addr, 6);
}
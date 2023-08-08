#include "router.h"
#include <cstring>
#include <thread>

// router functions

Router::Router(int router_id){
    // memset(ports, 0, sizeof(ports));
    // memset(arp_table, 0, sizeof(arp_table));
    ports.clear();
    init_ports();
    arp_table.clear();
    set_router_id(router_id);
    arp_table_entry_num = 0;    
}

Router::~Router(){
    free_ARP_table();
    free_ports();
    free_routing_table();
}

void Router::init_ports(){
    for(int i = 0; i < NUM_PORTS; i++){
        Port *port = new Port();
        port->set_MAC_addr(to_string(i)); // using ID - 1 as MAC address for now
        port->set_port_id(i+1);
        port->set_port_status(LINK_DOWN);
        ports[i+1] = port;
    }
}

void Router::free_ports(){
    for(auto& port : ports){
        delete port.second;
    }
    ports.clear();
}

int Router::send(string dst_ip, string msg){
    if(routing_table.count(dst_ip) == 0){
        cout << "No route to destination " << dst_ip << endl;
        return -1;
    }
    int port_id = routing_table[dst_ip]->interface_id; 
    if(get_port_status(port_id) == LINK_DOWN){
        cout << "Interface is down - Interface-ID: " << port_id << endl;
        return -2; 
    }
    int size = 0;
    frame *frame1 = new frame;
    frame1->dst_mac = arp_table[dst_ip]->neighbor_MAC;
    frame1->payload = msg;
    frame1->src_mac = get_port_MAC(port_id);
    size = frame1->dst_mac.size() + frame1->src_mac.size() + frame1->payload.size();
    frame_to_byte(frame1, send_buffer);
    delete frame1;
    
    // cout << "test send " << send_buffer.dst_mac << endl;
    return size;
}

void Router::add_arp_table_entry(string remote_end_ip, string remote_end_mac){
    ARP_table_entry *new_entry = new ARP_table_entry;
    new_entry->neighbor_IP = remote_end_ip;
    new_entry->neighbor_MAC = remote_end_mac;
    arp_table[remote_end_ip] = new_entry;
    arp_table_entry_num++;
}

int Router::remove_arp_table_entry(string ip){
    return arp_table.erase(ip);
}

void Router::print_ARP_table(){
    cout << "===============================================================\n";
    cout << "Router " << get_router_id() << " ARP table\n";
    cout << "===============================================================\n";
    cout << "IP                " << "MAC       " << endl;
    for(const auto& entry : arp_table){
        cout << entry.second->neighbor_IP << "       " << entry.second->neighbor_MAC << endl;
    }
    cout << "===============================================================\n\n";
}

void Router::free_ARP_table() {
    for (auto& entry : arp_table) {
        delete entry.second;
    }
    arp_table.clear();
    arp_table_entry_num = 0;
}

void Router::add_routing_table_entry(string dst_ip, int interface_id){
    routing_table_entry *new_entry = new routing_table_entry;
    new_entry->dst_IP= dst_ip;
    new_entry->interface_id = interface_id;
    routing_table[dst_ip] = new_entry;
}

int Router::remove_routing_table_entry(string dst_ip){
    return routing_table.erase(dst_ip);
}

void Router::print_routing_table(){
    cout << "===============================================================\n";
    cout << "Router " << get_router_id() << " Routing table\n";
    cout << "===============================================================\n";
    cout << "IP                " << "Interface       " << endl;
    for(const auto& entry : routing_table){
        cout << entry.second->dst_IP << "       " << entry.second->interface_id << endl;
    }
    cout << "===============================================================\n\n";
}

void Router::free_routing_table(){
    for(auto& entry : routing_table){
        delete entry.second;
    }
    routing_table.clear();
}

// ################################################
// #
// #        Ports
// #
// ################################################
unordered_map<int, Port*> Router::get_ports(){
    return ports;
}

bool Router::get_port_status(int port_id){
    return ports[port_id]->get_port_status();
}

void Router::set_port_status(int port_id, bool status){
    ports[port_id]->set_port_status(status);
}

void Router::print_port_status(){
    cout << "===============================================================\n";
    cout << "Router " << get_router_id() << " port status\n";
    cout << "===============================================================\n";
    cout << "Port number        " << "Link status       \n";
    cout << "  1                " << "  " << (get_port_status(1) == LINK_UP ? "up" : "down") << endl; 
    cout << "  2                " << "  " << (get_port_status(2) == LINK_UP ? "up" : "down") << endl; 
    cout << "  3                " << "  " << (get_port_status(3) == LINK_UP ? "up" : "down") << endl; 
    cout << "  4                " << "  " << (get_port_status(4) == LINK_UP ? "up" : "down") << endl; 
    cout << "  5                " << "  " << (get_port_status(5) == LINK_UP ? "up" : "down") << endl; 
    cout << "  6                " << "  " << (get_port_status(6) == LINK_UP ? "up" : "down") << endl; 
    cout << "  7                " << "  " << (get_port_status(7) == LINK_UP ? "up" : "down") << endl; 
    cout << "  8                " << "  " << (get_port_status(8) == LINK_UP ? "up" : "down") << endl; 
    cout << "  9                " << "  " << (get_port_status(9) == LINK_UP ? "up" : "down") << endl; 
    cout << "  10               " << "  " << (get_port_status(10) == LINK_UP ? "up" : "down") << endl; 
    cout << "  11               " << "  " << (get_port_status(11) == LINK_UP ? "up" : "down") << endl; 
    cout << "  12               " << "  " << (get_port_status(12) == LINK_UP ? "up" : "down") << endl; 
    cout << "  13               " << "  " << (get_port_status(13) == LINK_UP ? "up" : "down") << endl; 
    cout << "  14               " << "  " << (get_port_status(14) == LINK_UP ? "up" : "down") << endl; 
    cout << "  15               " << "  " << (get_port_status(15) == LINK_UP ? "up" : "down") << endl; 
    cout << "  16               " << "  " << (get_port_status(16) == LINK_UP ? "up" : "down") << endl; 
    cout << "  17               " << "  " << (get_port_status(17) == LINK_UP ? "up" : "down") << endl; 
    cout << "  18               " << "  " << (get_port_status(18) == LINK_UP ? "up" : "down") << endl; 
    cout << "  19               " << "  " << (get_port_status(19) == LINK_UP ? "up" : "down") << endl; 
    cout << "  20               " << "  " << (get_port_status(20) == LINK_UP ? "up" : "down") << endl; 
    cout << "===============================================================\n";
    cout << endl;
}

void Router::set_port_MAC(int port_id, string mac_addr){
    ports[port_id]->set_MAC_addr(mac_addr);
}

string Router::get_port_MAC(int port_id){
    return ports[port_id]->get_MAC_addr();
}

// ################################################
// #
// #        getters and setters
// #
// ################################################
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

uint8_t* Router::get_send_buffer(){
    return send_buffer;
}

uint8_t* Router::get_recv_buffer(){
    return recv_buffer;
}

// ################################################
// #
// #        Other
// #
// ################################################

void Router::frame_to_byte(frame *f, uint8_t *byte_array){
    int offset = 0;

    memcpy(byte_array + offset, f->dst_mac.c_str(), f->dst_mac.size());
    offset += f->dst_mac.size();

    memcpy(byte_array + offset, f->src_mac.c_str(), f->src_mac.size());
    offset += f->src_mac.size();

    memcpy(byte_array + offset, f->payload.c_str(), f->payload.size());
}

void Router::print_byte_array(uint8_t *byte_array, int size_byte){
    uint16_t bytes_counter = 0;
    int num_of_lines = 0;
    int num_bytes_to_print = 0;
    int remainder = size_byte % 32;
    if(remainder == 0){
        num_of_lines = size_byte / 32;
    } else{
        num_of_lines = size_byte / 32 + 1;
    }
    for(int i = 0; i < num_of_lines; i++){
        printf("%04u     ", bytes_counter);
        if(i == num_of_lines - 1 && remainder != 0){ 
            num_bytes_to_print = remainder;
        } else{
            num_bytes_to_print = 32;
        }
        // printing the hex value 
        for(int j = 0; j < num_bytes_to_print; j++){
            printf("%02X ", byte_array[(i * num_bytes_to_print) + j]);
            if(j == 15){
                printf(" ");
            }
        }
        printf(" ");
        // upon reaching last line, add padding to hex values so that characters align
        if(i == num_of_lines - 1){
            int padding = 32 - num_bytes_to_print;
            for (int j = 0; j < padding; j++) {
                printf("   ");
            }
        }
        // printing characters
        for (int j = 0; j < num_bytes_to_print; j++) {
            uint8_t value = byte_array[i * 32 + j];
            if (isprint(value)) {
                printf("%c", value);
            } else {
                printf(".");
            }
        }
        printf("\n");
        bytes_counter += num_bytes_to_print;
    }

}



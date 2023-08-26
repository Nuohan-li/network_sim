#include "router.h"
#include "misc.h"
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
    memset(&send_buf, 0, sizeof(send_buffer)); 
    memset(&recv_buf, 0, sizeof(recv_buffer)); 
    ready_to_recv = false;
    ready_to_send = false;
}

Router::~Router(){
    free_ARP_table();
    free_ports();
    free_routing_table();
}

void Router::init_ports(){
    for(int i = 0; i < NUM_PORTS; i++){
        Port *port = new Port();
        // port->set_MAC_addr(to_string(i));
        port->set_port_id(i+1);
        port->set_port_status(LINK_DOWN);

        uint64_t val = i & ((1 << 48) - 1);  // using ID as init MAC address for now

        ports[i+1] = port;
    }
}

void Router::free_ports(){
    for(auto& port : ports){
        delete port.second;
    }
    ports.clear();
}

int Router::populate_send_buffer(uint8_t *dst_ip, string msg){
    uint32_t dst_ip_32 = bytes_to_word(dst_ip);
    if(routing_table.count(dst_ip_32) == 0){
        cout << "No route to destination " << dst_ip << endl;
        return -1;
    }
    int port_id = routing_table[dst_ip_32]->interface_id; 
    if(get_port_status(port_id) == LINK_DOWN){
        cout << "Interface is down - Interface-ID: " << port_id << endl;
        return -2; 
    }
    int size = 0;
    frame *frame1 = new frame;
    memcpy(frame1->dst_mac, arp_table[dst_ip_32]->neighbor_MAC, MAC_ADDR_SIZE_BYTES);
    frame1->payload = msg;
    memcpy(frame1->src_mac, get_port_MAC(port_id), MAC_ADDR_SIZE_BYTES);
    size = 2 * MAC_ADDR_SIZE_BYTES + frame1->payload.size();
    frame_to_byte(frame1, send_buf.msg_buffer);
    
    
    ready_to_send = true;
    send_buf.data_size = size;
    send_buf.payload_size = frame1->payload.size();
    delete frame1;
    // cout << "test send " << send_buffer.dst_mac << endl;
    return size;
}

void Router::populate_recv_buffer(uint8_t *data, int data_size, int payload_size){
    memcpy(recv_buf.msg_buffer, data, data_size);
    recv_buf.data_size = data_size;
    recv_buf.payload_size = payload_size;
    ready_to_recv = false;
}

void Router::parse_recv_data(){
    frame *frame1 = new frame;
    int offset = 0;
    memcpy(frame1->dst_mac, &recv_buf.msg_buffer[offset], MAC_ADDR_SIZE_BYTES);
    offset += MAC_ADDR_SIZE_BYTES;
    memcpy(frame1->src_mac, &recv_buf.msg_buffer[offset], MAC_ADDR_SIZE_BYTES);
    offset += MAC_ADDR_SIZE_BYTES;
    memcpy(&frame1->payload, &recv_buf.msg_buffer[offset], recv_buf.payload_size);

    uint8_t recv_msg[10000];
    frame_to_byte(frame1, recv_buf.msg_buffer);
    cout << "received data\n";
    cout << "dst MAC ";
    print_mac(frame1->dst_mac);
    cout << "src MAC ";
    print_mac(frame1->src_mac);
    cout << "payload ";
    // print_byte_array(frame1->payload, recv_buf.payload_size);
    cout << frame1->payload;
    ready_to_recv = true;
    memset(&recv_buf, 0, sizeof(recv_buffer));
    delete frame1;
}

void Router::add_arp_table_entry(uint8_t *remote_end_ip, uint8_t *remote_end_mac){
    uint32_t remote_end_ip_32 = bytes_to_word(remote_end_ip);
    ARP_table_entry *new_entry = new ARP_table_entry;
    memcpy(new_entry->neighbor_IP, &remote_end_ip_32, IP_ADDR_SIZE_BYTES);
    // new_entry->neighbor_IP = remote_end_ip_32;
    // new_entry->neighbor_MAC = remote_end_mac;
    memcpy(new_entry->neighbor_MAC, remote_end_mac, MAC_ADDR_SIZE_BYTES);
    arp_table[remote_end_ip_32] = new_entry;
    arp_table_entry_num++;
}

ARP_table_entry* Router::get_arp_table_entry(uint8_t *IP){
    uint32_t ip_32 = bytes_to_word(IP);
    return arp_table[ip_32];
}

int Router::remove_arp_table_entry(uint8_t *IP){
    uint32_t ip_32 = bytes_to_word(IP);
    return arp_table.erase(ip_32);
}

void Router::print_ARP_table(){
    cout << "===============================================================\n";
    cout << "Router " << get_router_id() << " ARP table\n";
    cout << "===============================================================\n";
    cout << "IP                " << "MAC       " << endl;
    for(const auto& entry : arp_table){
        // cout << entry.second->neighbor_IP << "       " << entry.second->neighbor_MAC << endl;
        print_ip(entry.second->neighbor_IP);
        cout << "       ";
        print_mac(entry.second->neighbor_MAC);
        cout << endl;
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

void Router::add_routing_table_entry(uint8_t *dst_ip, int interface_id){
    routing_table_entry *new_entry = new routing_table_entry;
    memcpy(new_entry->dst_IP, dst_ip, IP_ADDR_SIZE_BYTES);
    new_entry->interface_id = interface_id;
    uint32_t dst_ip_32 = bytes_to_word(dst_ip);
    routing_table[dst_ip_32] = new_entry;
}

routing_table_entry * Router::get_routing_table_entry(uint8_t *IP){
    uint32_t ip_32 = bytes_to_word(IP);
    return routing_table[ip_32];
}

int Router::remove_routing_table_entry(uint8_t *dst_ip){
    uint32_t ip_32 = bytes_to_word(dst_ip);
    return routing_table.erase(ip_32);
}



void Router::print_routing_table(){
    cout << "===============================================================\n";
    cout << "Router " << get_router_id() << " Routing table\n";
    cout << "===============================================================\n";
    cout << "IP                " << "Interface       " << endl;
    for(const auto& entry : routing_table){
        print_ip(entry.second->dst_IP);
        cout << "       " << entry.second->interface_id << endl;
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

void Router::set_port_MAC(int port_id, uint8_t *mac_addr){
    ports[port_id]->set_MAC_addr(mac_addr);
}

uint8_t* Router::get_port_MAC(int port_id){
    return ports[port_id]->get_MAC_addr();
}

// ################################################
// #
// #        getters and setters
// #
// ################################################
void Router::set_ip(uint8_t *ip){
    memcpy(ip_addr, ip, IP_ADDR_SIZE_BYTES);
}

uint8_t* Router::get_ip(){
    return ip_addr;
}

void Router::set_router_id(int id){
    router_id = id;
}

int Router::get_router_id(){
    return router_id;
}

send_buffer Router::get_send_buffer(){
    return send_buf;
}

recv_buffer Router::get_recv_buffer(){
    return recv_buf;
}

bool Router::is_ready_to_receive(){
    return ready_to_recv;
}

// ################################################
// #
// #        Other
// #
// ################################################

void Router::frame_to_byte(frame *f, uint8_t *byte_array){
    int offset = 0;

    memcpy(byte_array + offset, f->dst_mac, MAC_ADDR_SIZE_BYTES);
    offset += MAC_ADDR_SIZE_BYTES;

    memcpy(byte_array + offset, f->src_mac, MAC_ADDR_SIZE_BYTES);
    offset += MAC_ADDR_SIZE_BYTES;

    memcpy(byte_array + offset, f->payload.c_str(), f->payload.size());
}


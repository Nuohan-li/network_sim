#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "port.h"

using namespace std;

#define LINK_UP true
#define LINK_DOWN false
#define NUM_PORTS 20
#define MAC_ADDR_SIZE_BYTES 6
#define IP_ADDR_SIZE_BYTES 4

struct MAC_table_entry{
    uint8_t remote_end_ip[IP_ADDR_SIZE_BYTES];
    int ingress_port;
    int egress_port;
};

struct ARP_table_entry{
    uint8_t neighbor_IP[IP_ADDR_SIZE_BYTES];
    uint8_t neighbor_MAC[MAC_ADDR_SIZE_BYTES];
};

struct routing_table_entry{
    uint8_t dst_IP[IP_ADDR_SIZE_BYTES];
    int interface_id; // using egress port ID for now
};

// heavily simgplified version of a ethernet frame
struct frame{
    uint8_t dst_mac[MAC_ADDR_SIZE_BYTES];
    uint8_t src_mac[MAC_ADDR_SIZE_BYTES];
    string payload;
};

class Router{

private:
    int router_id;
    uint8_t ip_addr[IP_ADDR_SIZE_BYTES];
    unordered_map<int, Port*> ports;  // port ID used as key
    
    uint8_t recv_buffer[10000];
    uint8_t send_buffer[10000];
    unordered_map<uint32_t, ARP_table_entry *> arp_table; // IP used as key
    unordered_map<uint32_t, routing_table_entry*> routing_table; // IP used as key
    bool ready_to_send;
    int arp_table_entry_num;
public: 
    // router function
    Router(int router_id);
    ~Router();
    int populate_send_buffer(uint8_t *dst_ip, string msg);
    int broadcast(string msg);
    void receive(Router *remote_end);
    void add_arp_table_entry(uint8_t *remote_end_ip, uint8_t *remote_end_mac);
    ARP_table_entry* get_arp_table_entry(uint8_t *IP);
    int remove_arp_table_entry(uint8_t *remote_end_ip);
    void print_ARP_table();
    void free_ARP_table();
    void add_routing_table_entry(uint8_t *ip, int interface_id);
    routing_table_entry *get_routing_table_entry(uint8_t *IP);
    int remove_routing_table_entry(uint8_t *dst_ip);
    void print_routing_table();
    void free_routing_table();

    // port functions
    void init_ports();
    void free_ports();
    void print_port_status();
    unordered_map<int, Port*> get_ports();
    void set_port_status(int port_id, bool status);
    bool get_port_status(int port_id);
    void set_port_MAC(int port_id, uint8_t *mac_addr);
    uint8_t *get_port_MAC(int port_id);

    // Other functions
    void frame_to_byte(frame *frame, uint8_t *byte_array);

    // getter and setter
    int get_router_id();
    void set_router_id(int id);
    uint8_t *get_ip();
    void set_ip(uint8_t *ip);
    uint8_t *get_send_buffer();
    uint8_t *get_recv_buffer();
    
    
};




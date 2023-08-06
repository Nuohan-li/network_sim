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

struct MAC_table_entry{
    string remote_end_ip;
    int ingress_port;
    int egress_port;
};

struct ARP_table_entry{
    string neighbor_IP;
    string neighbor_MAC;
};

struct routing_table_entry{
    string dst_IP;
    int interface_id; // using egress port ID for now
};

// heavily simgplified version of a ethernet frame
struct frame{
    string dst_mac;
    string src_mac;
    string payload;
};

class Router{

private:
    int router_id;
    string ip_addr;
    unordered_map<int, Port*> ports;
    frame *send_buffer;
    frame *recv_buffer;
    unordered_map<string, ARP_table_entry *> arp_table; // mac used as key
    unordered_map<string, routing_table_entry*> routing_table; // ip used as key
    int arp_table_entry_num;
public: 
    // router function
    Router(int router_id);
    ~Router();
    int send(string dst_ip, string msg);
    int broadcast(string msg);
    void receive(Router *remote_end);
    void add_arp_table_entry(string remote_end_ip, string remote_end_mac);
    int remove_arp_table_entry(string remote_end_ip);
    void print_ARP_table();
    void free_ARP_table();
    void add_routing_table_entry(string mac, int interface_id);
    int remove_routing_table_entry(string dst_ip);
    void print_routing_table();
    void free_routing_table();
    // control functions

    // port functions
    void init_ports();
    void free_ports();
    void print_port_status();
    unordered_map<int, Port*> get_ports();
    void set_port_status(int port_id, bool status);
    bool get_port_status(int port_id);
    void set_port_MAC(int port_id, string mac_addr);
    string get_port_MAC(int port_id);

    // getter and setter
    int get_router_id();
    void set_router_id(int id);
    string get_ip();
    void set_ip(string ip);
    
};




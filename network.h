#pragma once
#include "router.h"
#include <unordered_map>
#include <vector>

#define MAX_ROUTER_NUM_PER_NETWORK 20

// return code
enum return_code{
    SUCCESS = 0, 
    MAX_ROUTER_NUM_REACHED = -1,
    ROUTER_NOT_FOUND = -2,
    ROUTER_ALREADY_IN_NETWORK = -3,
    FAILED_TO_CONNECT_LINK = -4,
    LINK_DOES_NOT_EXIST = -5,
};

typedef struct Link{
    int router_id1;
    int port_id1;
    int router_id2;
    int port_id2;
} Link;

class Network{
    private:
        // this array maps to router_instances array to indicate whether a router at a given index exist
        bool router_exist[MAX_ROUTER_NUM_PER_NETWORK];
        Router *router_instances[MAX_ROUTER_NUM_PER_NETWORK];   // support 20 routers in a network
        int current_router_num;
        int network_id; // this could double as AS number in the future?
        vector<Link *> links; // adjacency list
        
    public:
        Network(int nid);
        ~Network();
        // network management 
        void set_network_id(int nid);
        int get_network_id();

        // routers related functions
        int add_router(int id);
        int remove_router(int router_id);
        Router *get_router_by_id(int id);
        bool check_router_exists(int id);
        void print_all_routers();
        int first_empty_slot();

        // link related functions
        int connect_link(int router_id1, int router_id2, int port_id1, int port_id2);
        Link *find_link(int router_id1, int port_id1);
        int remove_link(int router_id1, int port_id1);
        void remove_all_links();
        void print_all_links();
        


};
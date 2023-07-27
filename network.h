#pragma once
#include "router.h"

#define MAX_ROUTER_NUM_PER_NETWORK 20

// return code
enum return_code{
    SUCCESS = 0, 
    MAX_ROUTER_NUM_REACHED = -1,
    ROUTER_NOT_FOUND = -2
};

class Network{
    private:
        // this array maps to router_instances array to indicate whether a router at a given index exist
        bool router_exist[MAX_ROUTER_NUM_PER_NETWORK];
        Router *router_instances[MAX_ROUTER_NUM_PER_NETWORK];   // support 20 routers in a network
        int current_router_num;
    public:
        Network();
        ~Network();
        int add_router(int id);
        int remove_router(int router_id);
        int first_empty_slot();
        void connect_link(Router router1, Router router2, int port_id1, int port_id2);
        Router *get_router_by_id(int id);

};
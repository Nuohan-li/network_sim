#include "network.h"
#include <cstring>

using namespace std;

Network::Network(){
    current_router_num = 0;
    memset(router_exist, 0, sizeof(router_exist));
    memset(router_instances, 0, sizeof(router_instances));
}

Network::~Network(){
    // Release the dynamically allocated memory for router instances
    for (int i = 0; i < MAX_ROUTER_NUM_PER_NETWORK; i++) {
        if (router_exist[i]) {
            delete router_instances[i];
            router_instances[i] = nullptr;
        }
    }
}

// this function checks router_exists array to find the first empty slot and return the index corresponding to that slow
int Network::first_empty_slot(){
    for(int i = 0; i < MAX_ROUTER_NUM_PER_NETWORK; i++){
        if(!router_exist[i]){
            return i;
        }
    }
    return MAX_ROUTER_NUM_REACHED;
}

int Network::add_router(int id){
    if(current_router_num == MAX_ROUTER_NUM_PER_NETWORK){
        cout << "Maximum number of router reached, cannot add anymore routers to this network\n";
        return MAX_ROUTER_NUM_REACHED;
    }
    int spot = first_empty_slot();
    if(spot >= 0){
        Router *router = new Router(id);
        router_instances[spot] = router;
        router_exist[spot] = true;
        return SUCCESS;
    } 
    return MAX_ROUTER_NUM_REACHED;
}

Router* Network::get_router_by_id(int id){
    for(int i = 0; i < MAX_ROUTER_NUM_PER_NETWORK; i++){
        if(router_instances[i] != NULL){
            if(router_instances[i]->get_router_id() == id){
                return router_instances[i];
            }
        }  
    }
    cout << "Router not found\n";
    return nullptr;
}

int Network::remove_router(int id){
    Router *router = get_router_by_id(id);
    if(router == nullptr){
        return ROUTER_NOT_FOUND;
    }

    int router_index = 0;
    for(int router_index = 0; router_index < MAX_ROUTER_NUM_PER_NETWORK; router_index++){
        break;
    }
    delete router_instances[router_index];
    router_exist[router_index] = false;
    return SUCCESS;
}

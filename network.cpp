#include "network.h"
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

// ##############################################
// #
// #   misc
// #
// ##############################################

string generate_key(int a, int b, int c, int d){
    return to_string(a) + to_string(b) + to_string(c) + to_string(d);
}

// ##############################################
// #
// #   network functions
// #
// ##############################################

Network::Network(int nid){
    set_network_id(nid);
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
    remove_all_links();
}

void Network::set_network_id(int nid){
    network_id = nid;
}

int Network::get_network_id(){
    return network_id;
}

// ##############################################
// #
// #   Router management
// #
// ##############################################

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
    if(check_router_exists(id)){
        cout << "Router with this ID already exists\n";
        return ROUTER_ALREADY_IN_NETWORK;
    }
    int spot = first_empty_slot();
    if(spot >= 0){
        Router *router = new Router(id);
        router_instances[spot] = router;
        router_exist[spot] = true;
        current_router_num++;
        return SUCCESS;
    } 
    return MAX_ROUTER_NUM_REACHED;
}

bool Network::check_router_exists(int id){
    for(int i = 0; i < MAX_ROUTER_NUM_PER_NETWORK; i++){
        if(router_instances[i] != NULL){
            if(router_instances[i]->get_router_id() == id){
                return true;
            }
        }  
    }
    return false;
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
    if(!check_router_exists(id)){
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

// link needs to be stored somewhere -> these will act as edges in the graph that represents the network
int Network::connect_link(int router_id1, int router_id2, int port_id1, int port_id2){
    if(!(check_router_exists(router_id1) && check_router_exists(router_id2))){
        cout << "One or more routers do not exist in the network\n";
        return ROUTER_NOT_FOUND;
    }
    Router *router1 = get_router_by_id(router_id1);
    Router *router2 = get_router_by_id(router_id2);

    if(router1->get_port_status(port_id1) == LINK_UP){
        cout << "failed to connect link, router " << router_id1 << " port" << port_id1 << " already has a link\n";
        return FAILED_TO_CONNECT_LINK;
    }
    if(router2->get_port_status(port_id2) == LINK_UP){
        cout << "failed to connect link, router " << router_id2 << " port" << port_id2 << " already has a link\n";
        return FAILED_TO_CONNECT_LINK;
    }

    router1->set_port_status(port_id1, LINK_UP);
    router2->set_port_status(port_id2, LINK_UP);

    router1->add_arp_table_entry(router2->get_ip(), router2->get_port_MAC(port_id2));
    router2->add_arp_table_entry(router1->get_ip(), router2->get_port_MAC(port_id1));

    Link *link = new Link;
    link->port_id1 = port_id1;
    link->port_id2 = port_id2;
    link->router_id1 = router_id1;
    link->router_id2 = router_id2;

    // string key = generate_key(router_id1, router_id2, port_id1, port_id2);

    links.push_back(link);

    return SUCCESS;
}

Link* Network::find_link(int router_id, int port_id){
    for(auto link : links){
        if((router_id == link->router_id1 && port_id == link->port_id1) || 
            (router_id == link->router_id2 && port_id == link->port_id2)){
            return link;
        }
    }
    return nullptr;
}

int Network::remove_link(int router_id, int port_id){
    Link *link = find_link(router_id, port_id);
    if(link == nullptr){
        cout << "This link does not exist\n";
        return LINK_DOES_NOT_EXIST;
    }

    links.erase(remove(links.begin(), links.end(), link), links.end());
    delete link;
    return SUCCESS;
}

void Network::remove_all_links() {
    for (auto link : links) {
        delete link;
    }
    links.clear();
}

void Network::print_all_routers(){
    cout << "===============================================================\n";
    cout << "Network " << get_network_id() << " router list\n";
    cout << "===============================================================\n";
    for(int i = 0; i < MAX_ROUTER_NUM_PER_NETWORK; i++){
        if(router_exist[i]){
            cout << "Router " << router_instances[i]->get_router_id() << endl;
        }
    }
    cout << endl;
}

void Network::print_all_links(){
    cout << "===============================================================\n";
    cout << "Network " << get_network_id() << " link list\n";
    cout << "===============================================================\n";
    cout << "Router1 ID:Port number <---> Router2 ID:Port number\n\n";
    for(auto link : links){
        cout << link->router_id1 << ":" << link->port_id1 << "<--->" << link->router_id2 << ":" << link->port_id2 << endl;
    }
    cout << endl;
}




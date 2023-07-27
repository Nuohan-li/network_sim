#include <iostream>
#include "network.h"

using namespace std;

int main(){
    cout << "running\n";
    Network network;
    network.add_router(1);
    network.get_router_by_id(1)->print_port_status();

    Router *router = network.get_router_by_id(2);

    network.remove_router(2);
    if(network.remove_router(1) == SUCCESS){
        cout << "router removed successfully\n";
    }


    // Router *router = new Router(1);
    // router->print_port_stats();

    return 0;
}
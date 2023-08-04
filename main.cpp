#include <iostream>
#include "network.h"
#include "terminal.h"

using namespace std;

void network_test(){
    cout << "==================== Network Class test ====================\n";
    Network network = Network(1);
    network.add_router(1);
    network.get_router_by_id(1)->print_port_status();

    Router *router = network.get_router_by_id(2);

    network.remove_router(2);
    if(network.remove_router(1) == SUCCESS){
        cout << "router removed successfully\n";
    }

    network.add_router(100);
    network.add_router(201);
    network.add_router(102);
    network.print_all_routers();
    network.remove_router(100);
    network.print_all_routers();

    network.add_router(101);
    network.add_router(103);

    network.print_all_routers();
    network.connect_link(201, 102, 1, 2); // should work
    network.connect_link(201, 102, 2, 3); // should work
    network.connect_link(201, 102, 3, 4); // should work
    network.connect_link(201, 102, 4, 1); // should work
    network.connect_link(201, 102, 1, 1); // fail
    network.connect_link(101, 102, 1, 10); // should work
    
    network.print_all_links();

    network.remove_link(201, 1);
    network.remove_link(201, 2);
    network.print_all_links();

    network.remove_all_links();
    network.print_all_links();
}

int main(){
    network_test();
    // run_program();
    return 0;
}
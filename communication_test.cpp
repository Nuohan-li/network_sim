/*
    Test of sending information between two instances of Routers
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
// #include <sys/socket.h>
// #include <sys/un.h>
#include <string.h>
#include "router.h"

int main(){

    Router *router1 = new Router(1);
    Router *router2 = new Router(2);

    router1->add_routing_table_entry("192.168.1.1", 1);
    router1->add_routing_table_entry("192.168.1.4", 2);
    router1->add_routing_table_entry("192.168.1.3", 3);
    router1->add_routing_table_entry("192.168.1.2", 4);
    router1->print_routing_table();

    router1->add_arp_table_entry("192.168.1.1", "11:22:33:44:55:66");
    router1->add_arp_table_entry("192.168.1.2", "11:22:33:44:55:62");
    router1->add_arp_table_entry("192.168.1.3", "11:22:33:44:55:61");
    router1->print_ARP_table();
    router1->remove_arp_table_entry("11:22:33:44:55:66");
    int ret = router1->remove_arp_table_entry("11:22:33:44:55:60");
    if(ret == 0){
        cout << "this MAC does not exist\n";
    }
    router1->print_ARP_table();

    // router1->add_mtable_entry("192.168.1.1", 1);
    // router1->add_mtable_entry("192.168.1.2", 2);
    // router1->add_mtable_entry("192.168.1.3", 3);
    // router1->add_mtable_entry("192.168.1.4", 6);
    // router1->add_mtable_entry("192.168.1.5", 8);

    // router1->print_MAC_table();
    router1->print_port_status();

    return 0;
}
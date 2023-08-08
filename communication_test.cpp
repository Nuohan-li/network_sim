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

#ifdef __linux__ 
    #include <sys/socket.h>
    #include <sys/un.h>
#endif

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
    router1->remove_arp_table_entry("192.168.1.2");
    int ret = router1->remove_arp_table_entry("11:22:33:44:55:60");
    if(ret == 0){
        cout << "this MAC does not exist\n";
    }
    router1->print_ARP_table();

    router1->print_port_status();

    router1->set_port_status(1, 1);
    int size = router1->send("192.168.1.1", "test message");
    router1->print_byte_array(router1->get_send_buffer(), size);
    // cout << router1->send_buffer << endl;

    return 0;
}
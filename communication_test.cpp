/*
    Test of sending information between two instances of Routers
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include "router.h"

int main(){

    Router *router1 = new Router(1);
    Router *router2 = new Router(2);

    router1->add_mtable_entry("192.168.1.1", 1, 1);
    router1->add_mtable_entry("192.168.1.2", 2, 2);
    router1->add_mtable_entry("192.168.1.3", 3, 6);
    router1->add_mtable_entry("192.168.1.4", 6, 2);
    router1->add_mtable_entry("192.168.1.5", 8, 1);

    router1->print_MAC_table();
    router1->print_port_status();

    return 0;
}
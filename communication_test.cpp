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
#include "misc.h"

#ifdef __linux__ 
    #include <sys/socket.h>
    #include <sys/un.h>
#endif
// g++ router.cpp communication_test.cpp port.cpp network.cpp misc.cpp -> test using this file
// stored outgoing frame to send_buffer -> needs network to pull it and 'send' it to destination

/*
    to send packet, looks like that I can use socket library with sendto function, but then I will have to use sockaddr_in struct
    which I don't want to.
    Another way to simulate the transmission of packet at layer 2 is required
*/
int main(){

    Router *router1 = new Router(1);
    Router *router2 = new Router(2);
    uint8_t ip1[4] = {192, 168, 1, 1};
    uint8_t ip2[4] = {192, 168, 1, 2};
    uint8_t ip3[4] = {192, 168, 1, 3};
    uint8_t ip4[4] = {192, 168, 1, 4};
    uint8_t ip5[4] = {192, 168, 1, 5};

    router1->add_routing_table_entry(ip1, 1);
    router1->add_routing_table_entry(ip4, 2);
    router1->add_routing_table_entry(ip3, 3);
    router1->add_routing_table_entry(ip2, 4);
    router1->print_routing_table();

    uint8_t mac1[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    uint8_t mac2[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x62};
    uint8_t mac3[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x61};
    router1->add_arp_table_entry(ip1, mac1);
    router1->add_arp_table_entry(ip2, mac2);
    router1->add_arp_table_entry(ip3, mac3);
    router1->print_ARP_table();
    router1->remove_arp_table_entry(ip2);
    int ret = router1->remove_arp_table_entry(ip5);
    if(ret == 0){
        cout << "this MAC does not exist\n";
    }
    router1->print_ARP_table();
    router1->print_port_status();

    router1->set_port_status(1, 1);
    router1->set_port_MAC(1, mac3);
    int size = router1->populate_send_buffer(ip1, "test message");
    print_byte_array(router1->get_send_buffer().msg_buffer, size);
    // cout << router1->send_buffer << endl;

    // uint8_t values[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    // for(int i = 0; i < 1; i++){
    //     uint64_t val = (i + 2) & ((1ULL << 48) - 1);
    //     std::cout << static_cast<int>(val) << std::endl;
    //     memcpy(values, &val, sizeof(values));
    // }

    // for(int i = 0; i < 6; i++){
    //     std::cout << static_cast<int>(values[i]) << std::endl;
    // }

    return 0;
}
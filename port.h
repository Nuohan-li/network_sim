#include <iostream>
#include <string>

using namespace std;

class Port{
    private:
        int port_id;
        uint8_t MAC_addr[6];
        bool port_status;
    
    public:
        Port();
        ~Port();
        int get_port_id();
        void set_port_id(int id);
        uint8_t* get_MAC_addr();
        void set_MAC_addr(uint8_t *mac);
        bool get_port_status();
        void set_port_status(bool status);
        void print_port_state();

};
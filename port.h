#include <iostream>
#include <string>

using namespace std;

class Port{
    private:
        int port_id;
        string MAC_addr;
        bool port_status;
    
    public:
        Port();
        ~Port();
        int get_port_id();
        void set_port_id(int id);
        string get_MAC_addr();
        void set_MAC_addr(string mac);
        bool get_port_status();
        void set_port_status(bool status);

};
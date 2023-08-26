#include "misc.h"
#include <string.h>

using namespace std;
void print_byte_array(uint8_t *byte_array, int size_byte){
    uint16_t bytes_counter = 0;
    int num_of_lines = 0;
    int num_bytes_to_print = 0;
    int remainder = size_byte % 32;
    if(remainder == 0){
        num_of_lines = size_byte / 32;
    } else{
        num_of_lines = size_byte / 32 + 1;
    }
    for(int i = 0; i < num_of_lines; i++){
        printf("%04u     ", bytes_counter);
        if(i == num_of_lines - 1 && remainder != 0){ 
            num_bytes_to_print = remainder;
        } else{
            num_bytes_to_print = 32;
        }
        // printing the hex value 
        for(int j = 0; j < num_bytes_to_print; j++){
            printf("%02X ", byte_array[(i * num_bytes_to_print) + j]);
            if(j == 15){
                printf(" ");
            }
        }
        printf(" ");
        // upon reaching last line, add padding to hex values so that characters align
        if(i == num_of_lines - 1){
            int padding = 32 - num_bytes_to_print;
            for (int j = 0; j < padding; j++) {
                printf("   ");
            }
        }
        // printing characters
        for (int j = 0; j < num_bytes_to_print; j++) {
            uint8_t value = byte_array[i * 32 + j];
            if (isprint(value)) {
                printf("%c", value);
            } else {
                printf(".");
            }
        }
        printf("\n");
        bytes_counter += num_bytes_to_print;
    }

}

uint32_t bytes_to_word(uint8_t *bytes){
    return *(uint32_t *)bytes;
}
uint8_t * word_to_bytes(uint32_t word){ 
    uint8_t bytes[4];
    memcpy(bytes, &word, 4);
    return bytes;
}

void print_ip(uint8_t *ip){
    for(int i = 0; i < 4; i++){
        if(i != 3){
            printf("%u.", ip[i]);
        } else {
            printf("%u", ip[i]);
        }
    }
}

void print_mac(uint8_t *mac){
    for(int i = 0; i < 6; i++){
        if(i != 5){
            printf("%02X:", mac[i]);
        } else {
            printf("%02X", mac[i]);
        }
        
    }
}



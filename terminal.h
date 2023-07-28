#pragma once

#include <string>

using namespace std;

typedef enum commands{
    unknown,
    create_network,
    create_router, 
    remove_router,
    access_router,
} commands;

commands get_command(string command);

void run_program();
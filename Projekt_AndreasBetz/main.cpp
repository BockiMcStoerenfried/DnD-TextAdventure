#include "Headers/Handler.h"

int main(){

    EventHandler* controller = new EventHandler();

    controller->handleCommands();

    return 0;
}   
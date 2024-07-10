#include "Display.h"

int main() {
    Management manager;

    // Example: Adding shippers, senders, and receivers
    addShippers(manager.shippers);
    addSenders(manager.senders);
    addReceivers(manager.receivers);

    displayMenuManagement(&manager);

    return 0;
}

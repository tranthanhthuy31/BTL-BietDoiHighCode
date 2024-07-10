#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdio.h>
#include <string.h>
#include "Management.h"

void displayMenuManagement(Management* manager) ;

void displaySenderMenu(Management* manager);


void displayReceiverMenu(Management* manager);

void displayShipmentMenu(Management* manager) ;

void displayShipperMenu(Management* manager);
#endif // DISPLAY_H

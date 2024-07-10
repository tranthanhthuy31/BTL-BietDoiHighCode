#ifndef SHIPPER_H
#define SHIPPER_H
#include <stdio.h>
#include <string.h>

typedef enum {
    ReadyToDeliver,
    Delivering
} ShipperStatus;

typedef struct {
    char name[50];
    char shipperId[20];
    char tel[20];
    ShipperStatus shipperStatus;
} Shipper;

void exportDataShipper(const Shipper* s, FILE* out);

void displayShipper(const Shipper* s);

#endif // SHIPPER_H

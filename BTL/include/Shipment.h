#ifndef SHIPMENT_H
#define SHIPMENT_H
#include <stdio.h>
#include <string.h>
#include "Person.h"

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef enum {
    Pending,
    InTransit,
    Delivered,
    Returned
} ShipmentStatus;

typedef enum {
    Unpaid,
    Paid
} PaymentStatus;

typedef struct {
    char ShipmentId[20];
    Date sendDate;
    Date receiveDate;
    PaymentStatus paymentStatus;
    ShipmentStatus status;
    Person sender;
    Person receiver;
    char goodsInfo[100];
} Shipment;

void dateToString(const Date* date, char* buffer);

void displayShipment(const Shipment* s);

void exportDataShipment(const Shipment* s, FILE* out);

#endif // SHIPMENT_H

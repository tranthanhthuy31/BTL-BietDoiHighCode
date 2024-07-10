#ifndef MANAGEMENT_H
#define MANAGEMENT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Person.h"
#include "Shipper.h"
#include "Shipment.h"

typedef struct {
    Person* senders;
    int numSenders;
    Person* receivers;
    int numReceivers;
    Shipment* Shipments;
    int numShipments;
    Shipper* shippers;
    int numShippers;
} Management;

void addPerson(Person** list, int* numPersons, const char* role) ;

void printAllPersons(const Person* list, int numPersons, const char* role);

void deletePerson(Person** list, int* numPersons, const char* role) ;

void updatePerson(Person* list, int numPersons, const char* role);

void findPerson(const Person* list, int numPersons, const char* role);

int comparePersonsById(const void* a, const void* b) ;

void sortPersonById(Person* list, int numPersons, int ascending);

void exportToFile(const Person* list, int numPersons, const char* filename, const char* role) ;

void addShipment(Shipment* list, int* numShipments, Person* senders, int numSenders, Person* receivers, int numReceivers) ;

void printAllShipments(const Shipment* list, int numShipments) ;

Person* findPersonById(Person* persons, int numPersons, const char* id) ;

void deleteShipment(Shipment* list, int numShipments, Person* senders, int numSenders, Person* receivers, int numReceivers) ;

Shipment* findShipmentById(Shipment* list, int numShipments, const char* id);

void updateShipment(Shipment* list, int numShipments);

void findShipment(Shipment* list, int numShipments);

void exportToFileShipment(const Shipment* list, int numShipments, const char* filename);

void swap(Shipment* a, Shipment* b);

void sortShipmentsById(Shipment* list, int numShipments, int ascending);
void displayShipments(const Shipment* list, int numShipments) ;
int compareDates(const Date* d1, const Date* d2) ;

void sortShipmentsByDate(Shipment* shipments, int numShipments, int ascending) ;

void printAllShippers(const Shipper* list, int numShippers);

void setShipperStatus(Shipper* shippers, int numShippers) ;

void exportToFileShipper(const Shipper* shippers, int numShippers, const char* filename);

void addSenders(Person* senders, int numSenders);

// Function to add receivers
void addReceivers(Person* receivers, int numReceivers) ;

// Function to add shippers
void addShippers(Shipper* shippers, int numShippers);



#endif // MANAGEMENT_H

#ifndef PERSON_H
#define PERSON_H
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    char address[50];
    char id[20];
    char tel[20];
    int totalShipments;
} Person;

void displayPerson(const Person* p);

void displayPersonForShipment(const Person* p);

void exportData(const Person* p, FILE* out);

void updateDetails(Person* p, const char* name, const char* address, const char* tel);

#endif // PERSON_H

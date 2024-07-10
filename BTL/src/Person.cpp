#include "Person.h"

void displayPerson(const Person* p) {
    printf("%-10s%-20s%-20s%-16s%-10d\n", p->id, p->name, p->address, p->tel, p->totalShipments);
}

void displayPersonForShipment(const Person* p) {
    printf("ID: %s | Name: %s | Address: %s | Tel: %s\n", p->id, p->name, p->address, p->tel);
}

void exportData(const Person* p, FILE* out) {
    fprintf(out, "ID: %s | Name: %s | Address: %s | Tel: %s\n", p->id, p->name, p->address, p->tel);
    fprintf(out, "-----------------------\n");
}

void updateDetails(Person* p, const char* name, const char* address, const char* tel) {
    strcpy(p->name, name);
    strcpy(p->address, address);
    strcpy(p->tel, tel);
}

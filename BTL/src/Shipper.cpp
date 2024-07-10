#include "Shipper.h"

void exportDataShipper(const Shipper* s, FILE* out) {
    fprintf(out, "ID Shipper: %s | ", s->shipperId);
    fprintf(out, "Name Shipper: %s | ", s->name);
    fprintf(out, "Tel: %s | ", s->tel);
    fprintf(out, "Shipper Status: %d\n", s->shipperStatus);
    fprintf(out, "-----------------------\n");
}

void displayShipper(const Shipper* s) {
    printf("%-10s%-20s%-16s%-10s\n", s->shipperId, s->name, s->tel, s->shipperStatus == ReadyToDeliver ? "Ready to deliver" : "Delivering");
}

#include "Shipment.h"

void dateToString(const Date* date, char* buffer) {
    sprintf(buffer, "%d/%d/%d", date->day, date->month, date->year);
}

void displayShipment(const Shipment* s) {
    char sendDateStr[11], receiveDateStr[11];
    dateToString(&s->sendDate, sendDateStr);
    dateToString(&s->receiveDate, receiveDateStr);

    printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "ID", "Send Date", "Receive Date", "Goods Info", "Status", "Payment Status");
    printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", s->ShipmentId, sendDateStr, receiveDateStr, s->goodsInfo,
           s->status == Pending ? "Pending" : s->status == InTransit ? "In Transit" : s->status == Delivered ? "Delivered" : "Returned",
           s->paymentStatus == Unpaid ? "Unpaid" : "Paid");
    printf("-----Sender information:\n");
    displayPersonForShipment(&s->sender);
    printf("-----Receiver information:\n");
    displayPersonForShipment(&s->receiver);
    printf("%s\n", "----------------------------------------------------------------------------------------------------");
}

void exportDataShipment(const Shipment* s, FILE* out) {
    char sendDateStr[11], receiveDateStr[11];
    dateToString(&s->sendDate, sendDateStr);
    dateToString(&s->receiveDate, receiveDateStr);

    fprintf(out, "ID: %s | Send Date: %s | Receive Date: %s | Infor: %s\n", s->ShipmentId, sendDateStr, receiveDateStr, s->goodsInfo);
    fprintf(out, "ID Sender: %s | Name Sender: %s | Address Sender: %s | Tel Sender: %s\n", s->sender.id, s->sender.name, s->sender.address, s->sender.tel);
    fprintf(out, "ID Receiver: %s | Name Receiver: %s | Address Receiver: %s | Tel Receiver: %s\n", s->receiver.id, s->receiver.name, s->receiver.address, s->receiver.tel);
    fprintf(out, "-----------------------\n");
}

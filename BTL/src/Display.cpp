#include "Display.h"

void displayMenuManagement(Management* manager) {
    int choice;
    do {
        system("CLS");
        printf("\t\t   BIET DOI HIGH CODE\t\n");
        printf("====================MENU-MANAGEMENT===================\n");
        printf("==               1.Sender Management                ==\n");
        printf("==               2.Receiver Management              ==\n");
        printf("==               3.Shipment Management              ==\n");
        printf("==               4.Shipper Management               ==\n");
        printf("==               5.Exit                             ==\n");
        printf("======================================================\n");
        printf(" Enter your choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySenderMenu(manager);
                break;
            case 2:
                displayReceiverMenu(manager);
                break;
            case 3:
                displayShipmentMenu(manager);
                break;
            case 4:
                displayShipperMenu(manager);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                system("pause");
                break;
        }
    } while (choice != 5);
}

void displaySenderMenu(Management* manager) {
    int choice;
    do {
        system("CLS");
        printf("\t\t   BIET DOI HIGH CODE\t\n");
        printf("====================SENDER-MANAGEMENT===================\n");
        printf("==               1.Add Sender                         ==\n");
        printf("==               2.Print Sender List                  ==\n");
        printf("==               3.Delete Sender By ID                ==\n");
        printf("==               4.Update Sender By ID                ==\n");
        printf("==               5.Find Sender By ID                  ==\n");
        printf("==               6.Sort Sender List By ID             ==\n");
        printf("==               7.Export Sender List To File         ==\n");
        printf("==               8.Return To Main Menu                ==\n");
        printf("========================================================\n");
        printf(" Enter your choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPerson(manager->senders, "Sender");
                break;
            case 2:
                printAllPersons(manager->senders, "Sender");
                break;
            case 3:
                deletePerson(manager->senders, "Sender");
                break;
            case 4:
                updatePerson(manager->senders, "Sender");
                break;
            case 5:
                findPerson(manager->senders, "Sender");
                break;
            case 6: {
                system("CLS");
                int personChoice;
                printf("1. Ascending\n2. Descending\n");
                printf("Enter your choice: ");
                scanf("%d", &personChoice);
                sortPersonById(manager->senders, personChoice == 1);
                printf("Senders sorted by ID %s!\n", personChoice == 1 ? "(Ascending)" : "(Descending)");
                system("pause");
                break;
            }
            case 7: {
                system("CLS");
                char fname[50];
                printf("Enter the filename: ");
                scanf("%s", fname);
                exportToFile(manager->senders, fname, "Sender");
                printf("\nExport File Successfully !\n");
                system("pause");
                break;
            }
            case 8:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
                system("pause");
                break;
        }
    } while (choice != 8);
}


void displayReceiverMenu(Management* manager) {
    int choice;
    do {
        system("CLS");
        printf("\t\t   BIET DOI HIGH CODE\t\n");
        printf("====================RECEIVER-MANAGEMENT===================\n");
        printf("==               1.Add Receiver                         ==\n");
        printf("==               2.Print Receiver List                  ==\n");
        printf("==               3.Delete Receiver By ID                ==\n");
        printf("==               4.Update Receiver By ID                ==\n");
        printf("==               5.Find Receiver By ID                  ==\n");
        printf("==               6.Sort Receiver List By ID             ==\n");
        printf("==               7.Export Receiver List To File         ==\n");
        printf("==               8.Return To Main Menu                  ==\n");
        printf("==========================================================\n");
        printf(" Enter your choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPerson(manager->receivers, "Receiver");
                break;
            case 2:
                printAllPersons(manager->receivers, "Receiver");
                break;
            case 3:
                deletePerson(manager->receivers, "Receiver");
                break;
            case 4:
                updatePerson(manager->receivers, "Receiver");
                break;
            case 5:
                findPerson(manager->receivers, "Receiver");
                break;
            case 6: {
                system("CLS");
                int personChoice;
                printf("1. Ascending\n2. Descending\n");
                printf("Enter your choice: ");
                scanf("%d", &personChoice);
                sortPersonById(manager->receivers, personChoice == 1);
                printf("Receivers sorted by ID %s!\n", personChoice == 1 ? "(Ascending)" : "(Descending)");
                system("pause");
                break;
            }
            case 7: {
                system("CLS");
                char fname[50];
                printf("Enter the filename: ");
                scanf("%s", fname);
                exportToFile(manager->receivers, fname, "Receiver");
                printf("\nExport File Successfully !\n");
                system("pause");
                break;
            }
            case 8:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
                system("pause");
                break;
        }
    } while (choice != 8);
}

void displayShipmentMenu(Management* manager) {
    int choice;
    do {
        system("CLS");
        printf("\t\t   BIET DOI HIGH CODE\t\n");
        printf("====================SHIPMENT-MANAGEMENT===================\n");
        printf("==               1.Add Shipment                         ==\n");
        printf("==               2.Print Shipment List                  ==\n");
        printf("==               3.Delete Shipment By ID                ==\n");
        printf("==               4.Update Shipment By ID                ==\n");
        printf("==               5.Find Shipment By ID                  ==\n");
        printf("==               6.Sort Shipment List By ID             ==\n");
        printf("==               7.Sort Shipment List By Date           ==\n");
        printf("==               8.Export Shipment List To File         ==\n");
        printf("==               9.Return To Main Menu                  ==\n");
        printf("==========================================================\n");
        printf(" Enter your choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addShipment(manager->shipments, manager->senders, manager->receivers);
                break;
            case 2:
                printAllShipments(manager->shipments);
                break;
            case 3:
                deleteShipment(manager->shipments, manager->senders, manager->receivers);
                break;
            case 4:
                updateShipment(manager->shipments);
                break;
            case 5:
                findShipment(manager->shipments);
                break;
            case 6: {
                system("CLS");
                int shipmentChoice;
                printf("1. Ascending\n2. Descending\n");
                printf("Enter your choice: ");
                scanf("%d", &shipmentChoice);
                sortShipmentsById(manager->shipments, shipmentChoice == 1);
                printf("Shipments sorted by ID %s!\n", shipmentChoice == 1 ? "(Ascending)" : "(Descending)");
                system("pause");
                break;
            }
            case 7: {
                system("CLS");
                int dateChoice;
                printf("1. Ascending\n2. Descending\n");
                printf("Enter your choice: ");
                scanf("%d", &dateChoice);
                sortShipmentsByDate(manager->shipments, dateChoice == 1);
                printf("Shipments sorted by Date %s!\n", dateChoice == 1 ? "(Ascending)" : "(Descending)");
                system("pause");
                break;
            }
            case 8: {
                system("CLS");
                char fname[50];
                printf("Enter the filename: ");
                scanf("%s", fname);
                exportToFileShipment(manager->shipments, fname, manager->senders, manager->receivers);
                printf("\nExport File Successfully !\n");
                system("pause");
                break;
            }
            case 9:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
                system("pause");
                break;
        }
    } while (choice != 9);
}

void displayShipperMenu(Management* manager) {
    int choice;
    do {
        system("CLS");
        printf("\t\t   BIET DOI HIGH CODE\t\n");
        printf("====================SHIPPER-MANAGEMENT===================\n");
        printf("==               1.Print Shipper List                  ==\n");
        printf("==               2.Set Shipper Status                  ==\n");
        printf("==               3.Export Shipper List To File         ==\n");
        printf("==               4.Return To Main Menu                 ==\n");
        printf("=========================================================\n");
        printf(" Enter your choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printAllShippers(manager->shippers);
                break;
            case 2:
                setShipperStatus(manager->shippers);
                break;
            case 3: {
                system("CLS");
                char fname[50];
                printf("Enter the filename: ");
                scanf("%s", fname);
                exportToFileShipper(manager->shippers, fname);
                printf("\nExport File Successfully !\n");
                system("pause");
                break;
            }
            case 4:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
                system("pause");
                break;
        }
    } while (choice != 4);
}

#include "Management.h"


void addPerson(Person** list, int* numPersons, const char* role) {
    system("CLS");
    char name[50], address[50], id[20], tel[20];

    printf("Enter %s ID: ", role);
    scanf("%s", id);
    getchar(); // Consume newline character

    // Check if person with ID already exists
    for (int i = 0; i < *numPersons; i++) {
        if (strcmp((*list)[i].id, id) == 0) {
            printf("%s with ID %s already exists. Please enter a new ID.\n", role, id);
            system("pause");
            return;
        }
    }

    printf("Enter %s Name: ", role);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character

    printf("Enter %s Address: ", role);
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = '\0'; // Remove newline character

    printf("Enter %s Tel: ", role);
    scanf("%s", tel);
    getchar(); // Consume newline character

    // Allocate memory for new person
    *list = realloc(*list, (*numPersons + 1) * sizeof(Person));
    if (*list == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Assign values to new person
    strcpy((*list)[*numPersons].name, name);
    strcpy((*list)[*numPersons].address, address);
    strcpy((*list)[*numPersons].id, id);
    strcpy((*list)[*numPersons].tel, tel);

    (*numPersons)++;
    printf("%s added successfully!\n", role);
    system("pause");
}

void printAllPersons(const Person* list, int numPersons, const char* role) {
    system("CLS");
    printf("%-10s%-20s%-20s%-16s%-10s\n", "ID", "Name", "Address", "Tel", "Shipments");
    printf("%s\n", "---------------------------------------------------------------------------------");

    for (int i = 0; i < numPersons; i++) {
        displayPerson(&list[i]);
    }

    system("pause");
}

void deletePerson(Person** list, int* numPersons, const char* role) {
    system("CLS");
    char id[20];
    printf("Enter %s ID to delete: ", role);
    scanf("%s", id);

    // Tìm và xóa người có ID tương ứng
    for (int i = 0; i < *numPersons; i++) {
        if (strcmp((*list)[i].id, id) == 0) {
            // Di chuyển các phần tử phía sau lên trước để xóa
            for (int j = i; j < *numPersons - 1; j++) {
                (*list)[j] = (*list)[j + 1];
            }
            (*numPersons)--;
            *list = realloc(*list, (*numPersons) * sizeof(Person));
            if (*list == NULL && *numPersons > 0) {
                perror("Failed to reallocate memory");
                exit(EXIT_FAILURE);
            }
            printf("%s with ID %s deleted successfully!\n", role, id);
            system("pause");
            return;
        }
    }

    printf("%s with ID %s does not exist.\n", role, id);
    system("pause");
}

void updatePerson(Person* list, int numPersons, const char* role) {
    system("CLS");
    char id[20];
    printf("Enter %s ID to update: ", role);
    scanf("%s", id);

    // Tìm và cập nhật thông tin người dùng
    for (int i = 0; i < numPersons; i++) {
        if (strcmp(list[i].id, id) == 0) {
            int choice;
            printf("%s found! What do you want to update?\n", role);
            printf("1. Name\n2. Address\n3. Telephone\nEnter your choice: ");
            scanf("%d", &choice);
            getchar(); // Đọc ký tự '\n' từ bộ đệm

            switch (choice) {
            case 1: {
                char newName[50];
                printf("Enter new name: ");
                fgets(newName, sizeof(newName), stdin);
                newName[strcspn(newName, "\n")] = 0; // Xóa ký tự '\n' cuối chuỗi
                updateDetails(&list[i], newName, list[i].address, list[i].tel);
                printf("Name updated successfully!\n");
                system("pause");
                break;
            }
            case 2: {
                char newAddress[50];
                printf("Enter new address: ");
                fgets(newAddress, sizeof(newAddress), stdin);
                newAddress[strcspn(newAddress, "\n")] = 0; // Xóa ký tự '\n' cuối chuỗi
                updateDetails(&list[i], list[i].name, newAddress, list[i].tel);
                printf("Address updated successfully!\n");
                system("pause");
                break;
            }
            case 3: {
                char newTel[20];
                printf("Enter new telephone: ");
                scanf("%s", newTel);
                updateDetails(&list[i], list[i].name, list[i].address, newTel);
                printf("Telephone updated successfully!\n");
                system("pause");
                break;
            }
            default:
                printf("Invalid choice!\n");
                system("pause");
                break;
            }

            return;
        }
    }

    printf("%s with ID %s does not exist.\n", role, id);
    system("pause");
}

void findPerson(const Person* list, int numPersons, const char* role) {
    system("CLS");
    char id[20];
    printf("Enter %s ID to find: ", role);
    scanf("%s", id);

    // Tìm và hiển thị thông tin người dùng
    for (int i = 0; i < numPersons; i++) {
        if (strcmp(list[i].id, id) == 0) {
            displayPerson(&list[i]);
            system("pause");
            return;
        }
    }

    printf("%s with ID %s does not exist. Returning to main menu.\n", role, id);
    system("pause");
}

int comparePersonsById(const void* a, const void* b) {
    const Person* personA = (const Person*)a;
    const Person* personB = (const Person*)b;

    return strcmp(personA->id, personB->id);
}

void sortPersonById(Person* list, int numPersons, int ascending) {
    qsort(list, numPersons, sizeof(Person), comparePersonsById);
    if (!ascending) {
        // Nếu không sắp xếp tăng dần, đảo ngược mảng
        for (int i = 0; i < numPersons / 2; i++) {
            Person temp = list[i];
            list[i] = list[numPersons - i - 1];
            list[numPersons - i - 1] = temp;
        }
    }
}

void exportToFile(const Person* list, int numPersons, const char* filename, const char* role) {
    FILE* outFile = fopen(filename, "w");
    if (outFile == NULL) {
        fprintf(stderr, "Could not open the file!\n");
        return;
    }
    fprintf(outFile, "%s:\n", role);
    fprintf(outFile, "==============================\n");
    for (int i = 0; i < numPersons; i++) {
        fprintf(outFile, "ID: %s | Name: %s | Address: %s | Tel: %s\n",
            list[i].id, list[i].name, list[i].address, list[i].tel);
        fprintf(outFile, "-----------------------\n");
    }
    fclose(outFile);
}

void addShipment(Shipment* list, int* numShipments, Person* senders, int numSenders, Person* receivers, int numReceivers) {
    system("clear");
    int status, pstatus;
    char goods[100], shipmentId[20], senderId[20], receiverId[20];
    Date sDate, rDate;

    printf("Enter the information for new Shipment\n");

    Person* findPersonById(Person* persons, int numPersons, const char* id) {
        for (int i = 0; i < numPersons; ++i) {
            if (strcmp(persons[i].id, id) == 0) {
                return &persons[i];
            }
        }
        printf("Person with ID %s not found.\n", id);
        exit(1);
    }

    int findShipmentById(Shipment* list, int numShipments, const char* id) {
        for (int i = 0; i < numShipments; ++i) {
            if (strcmp(list[i].shipmentId, id) == 0) {
                return 1;
            }
        }
        return 0;
    }

    printf("Enter the Sender ID: ");
    scanf("%s", senderId);

    Person* sender = NULL;
    sender = findPersonById(senders, numSenders, senderId);

    printf("Enter the Receiver ID: ");
    scanf("%s", receiverId);

    Person* receiver = NULL;
    receiver = findPersonById(receivers, numReceivers, receiverId);

    printf("Enter the Shipment ID: ");
    scanf("%s", shipmentId);

    if (findShipmentById(list, *numShipments, shipmentId)) {
        printf("Shipment with ID %s already exists.\n", shipmentId);
        exit(1);
    }

    printf("Send Date (day month year): ");
    scanf("%d %d %d", &sDate.day, &sDate.month, &sDate.year);
    printf("Receive Date (day month year): ");
    scanf("%d %d %d", &rDate.day, &rDate.month, &rDate.year);
    getchar();
    printf("Goods information: ");
    fgets(goods, sizeof(goods), stdin);
    goods[strlen(goods) - 1] = '\0'; // Remove newline character from fgets input

    printf("Shipment Status: Pending (0) / InTransit (1) / Delivered (2) / Returned (3): ");
    scanf("%d", &status);
    printf("Payment Status: Unpaid (0) / Paid (1): ");
    scanf("%d", &pstatus);

    strcpy(list[*numShipments].shipmentId, shipmentId);
    list[*numShipments].sendDate = sDate;
    list[*numShipments].receiveDate = rDate;
    list[*numShipments].paymentStatus = pstatus;
    list[*numShipments].shipmentStatus = status;
    strcpy(list[*numShipments].senderId, senderId);
    strcpy(list[*numShipments].receiverId, receiverId);
    strcpy(list[*numShipments].goodsInfo, goods);

    (*numShipments)++;

    sender->totalShipments++;
    receiver->totalShipments++;

    printf("Shipment added successfully!\n");
    system("pause");
}

void printAllShipments(const Shipment* list, int numShipments) {
    system("clear");
    printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n",
           "ID", "Send Date", "Receive Date", "Goods Info", "Status", "Payment Status", "Sender/Receiver");

    printf("--------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < numShipments; ++i) {
        displayShipment(&list[i]);
    }
    system("pause");
}

Person* findPersonById(Person* persons, int numPersons, const char* id) {
    for (int i = 0; i < numPersons; ++i) {
        if (strcmp(persons[i].id, id) == 0) {
            return &persons[i];
        }
    }
    return NULL;
}

void deleteShipment(Shipment* list, int numShipments, Person* senders, int numSenders, Person* receivers, int numReceivers) {
    system("clear");
    char id[20];
    printf("Enter Shipment ID to delete: ");
    scanf("%s", id);

    for (int i = 0; i < numShipments; ++i) {
        if (strcmp(list[i].shipmentId, id) == 0) {
            Person* sender = findPersonById(senders, numSenders, list[i].senderId);
            if (sender == NULL) {
                fprintf(stderr, "Sender with ID %s not found.\n", list[i].senderId);
                system("pause");
                return;
            }

            Person* receiver = findPersonById(receivers, numReceivers, list[i].receiverId);
            if (receiver == NULL) {
                fprintf(stderr, "Receiver with ID %s not found.\n", list[i].receiverId);
                system("pause");
                return;
            }

            sender->totalShipments--;
            receiver->totalShipments--;

            // Shift elements to fill the gap left by the deleted shipment
            for (int j = i; j < numShipments - 1; ++j) {
                list[j] = list[j + 1];
            }

            printf("Shipment with ID %s deleted successfully!\n", id);
            system("pause");
            return;
        }
    }

    printf("Shipment with ID %s does not exist.\n", id);
    system("pause");
}

Shipment* findShipmentById(Shipment* list, int numShipments, const char* id) {
    for (int i = 0; i < numShipments; ++i) {
        if (strcmp(list[i].shipmentId, id) == 0) {
            return &list[i];
        }
    }
    return NULL;
}

void updateShipment(Shipment* list, int numShipments) {
    system("clear");
    char id[20];
    printf("Enter Shipment ID to update: ");
    scanf("%s", id);

    Shipment* shipmentToUpdate = findShipmentById(list, numShipments, id);

    if (shipmentToUpdate != NULL) {
        int choice;
        int updateAgain = 1;

        while (updateAgain) {
            system("clear");
            printf("\nSelect field to update for Shipment ID %s:\n", id);
            printf("1. Send Date\n");
            printf("2. Receive Date\n");
            printf("3. Status\n");
            printf("4. Payment Status\n");
            printf("5. Goods Info\n");
            printf("6. Exit update\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1: {
                // Update Send Date
                printf("Enter new Send Date (day month year): ");
                scanf("%d %d %d", &shipmentToUpdate->sendDate.day, &shipmentToUpdate->sendDate.month, &shipmentToUpdate->sendDate.year);
                printf("Shipment with ID %s's Send Date updated successfully!\n", id);
                break;
            }
            case 2: {
                // Update Receive Date
                printf("Enter new Receive Date (day month year): ");
                scanf("%d %d %d", &shipmentToUpdate->receiveDate.day, &shipmentToUpdate->receiveDate.month, &shipmentToUpdate->receiveDate.year);
                printf("Shipment with ID %s's Receive Date updated successfully!\n", id);
                break;
            }
            case 3: {
                printf("Enter new Shipment Status: Pending (0) / InTransit (1) / Delivered (2) / Returned (3): ");
                scanf("%d", (int*)&shipmentToUpdate->shipmentStatus);
                printf("Shipment with ID %s's Status updated successfully!\n", id);
                break;
            }
            case 4: {
                printf("Enter new Payment Status: Unpaid (0) / Paid (1): ");
                scanf("%d", (int*)&shipmentToUpdate->paymentStatus);
                printf("Shipment with ID %s's Payment Status updated successfully!\n", id);
                break;
            }
            case 5: {
                printf("Enter new Goods Info: ");
                scanf(" %[^\n]s", shipmentToUpdate->goodsInfo);
                printf("Shipment with ID %s's Goods Info updated successfully!\n", id);
                break;
            }
            case 6:
                updateAgain = 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }

            system("pause");
        }

        printf("Shipment with ID %s updated successfully!\n", id);
    } else {
        printf("Shipment with ID %s not found!\n", id);
        system("pause");
    }
}

void findShipment(Shipment* list, int numShipments) {
    system("clear");
    char id[20];
    printf("Enter Shipment ID to find: ");
    scanf("%s", id);

    Shipment* shipment = findShipmentById(list, numShipments, id);

    if (shipment != NULL) {
        displayShipment(shipment);
        system("pause");
    } else {
        printf("Shipment with ID %s does not exist.\n", id);
        system("pause");
    }
}

void exportToFileShipment(const Shipment* list, int numShipments, const char* filename) {
    FILE* outFile = fopen(filename, "w");
    if (outFile == NULL) {
        fprintf(stderr, "Could not open the file!\n");
        return;
    }

    fprintf(outFile, "Shipments\n");
    fprintf(outFile, "==============================\n");
    for (int i = 0; i < numShipments; ++i) {
        exportDataShipment(outFile, &list[i]);
    }

    fclose(outFile);
}

void swap(Shipment* a, Shipment* b) {
    Shipment temp = *a;
    *a = *b;
    *b = temp;
}

void sortShipmentsById(Shipment* list, int numShipments, int ascending) {
    for (int i = 0; i < numShipments - 1; ++i) {
        for (int j = i + 1; j < numShipments; ++j) {
            if ((ascending && strcmp(list[i].shipmentId, list[j].shipmentId) > 0) ||
                (!ascending && strcmp(list[i].shipmentId, list[j].shipmentId) < 0)) {
                swap(&list[i], &list[j]);
            }
        }
    }
}

void displayShipments(const Shipment* list, int numShipments) {
    printf("All Shipments:\n");
    for (int i = 0; i < numShipments; ++i) {
        printf("Shipment ID: %s\n", list[i].shipmentId);
        printf("Sender ID: %s\n", list[i].senderId);
        printf("Receiver ID: %s\n", list[i].receiverId);
        printf("Send Date: %d/%d/%d\n", list[i].sendDate.day, list[i].sendDate.month, list[i].sendDate.year);
        printf("Receive Date: %d/%d/%d\n", list[i].receiveDate.day, list[i].receiveDate.month, list[i].receiveDate.year);
        printf("Goods Info: %s\n", list[i].goodsInfo);
        printf("Shipment Status: %s\n", list[i].shipmentStatus == Pending ? "Pending" :
                                        list[i].shipmentStatus == InTransit ? "In Transit" :
                                        list[i].shipmentStatus == Delivered ? "Delivered" : "Returned");
        printf("Payment Status: %s\n\n", list[i].paymentStatus == Unpaid ? "Unpaid" : "Paid");
    }
}

int compareDates(const Date* d1, const Date* d2) {
    if (d1->year != d2->year) return d1->year < d2->year;
    if (d1->month != d2->month) return d1->month < d2->month;
    return d1->day < d2->day;
}

void sortShipmentsByDate(Shipment* shipments, int numShipments, int ascending) {
    for (int i = 0; i < numShipments - 1; ++i) {
        for (int j = i + 1; j < numShipments; ++j) {
            if ((ascending && compareDates(&shipments[i].sendDate, &shipments[j].sendDate) > 0) ||
                (!ascending && compareDates(&shipments[i].sendDate, &shipments[j].sendDate) < 0)) {
                swap(&shipments[i], &shipments[j]);
            }
        }
    }
}

void printAllShippers(const Shipper* list, int numShippers) {
    system("CLS");
    printf("%-10s%-20s%-16s%-10s\n", "ID", "Name", "Tel", "Shipper Status");
    printf("%s\n", "---------------------------------------------------------------------------------");

    for (int i = 0; i < numShippers; ++i) {
        displayShipper(&list[i]);
    }

    system("pause");
}

void setShipperStatus(Shipper* shippers, int numShippers) {
    system("CLS");
    char id[20];
    printf("Enter Shipper ID to update status: ");
    scanf("%s", id);

    for (int i = 0; i < numShippers; ++i) {
        if (strcmp(shippers[i].shipperId, id) == 0) {
            int newStatus;
            printf("Enter new Shipper Status: ReadyToDeliver (0) / Delivering (1): ");
            scanf("%d", &newStatus);
            shippers[i].shipperStatus = newStatus == 0 ? ReadyToDeliver : Delivering;
            printf("Shipper with ID %s's status updated successfully!\n", id);
            system("pause");
            return;
        }
    }

    printf("Shipper with ID %s not found!\n", id);
    system("pause");
}

void exportToFileShipper(const Shipper* shippers, int numShippers, const char* filename) {
    FILE* outFile = fopen(filename, "w");
    if (!outFile) {
        fprintf(stderr, "Could not open the file!\n");
        return;
    }
    fprintf(outFile, "SHIPPER\n");
    fprintf(outFile, "=================================\n");
    for (int i = 0; i < numShippers; ++i) {
        fprintf(outFile, "Name: %s\n", shippers[i].name);
        fprintf(outFile, "ID: %s\n", shippers[i].shipperId);
        fprintf(outFile, "Tel: %s\n", shippers[i].tel);
        fprintf(outFile, "Shipper Status: %s\n", shippers[i].shipperStatus == ReadyToDeliver ? "ReadyToDeliver" : "Delivering");
        fprintf(outFile, "---------------------------------\n");
    }
    fclose(outFile);
}

void addSenders(Person* senders, int numSenders) {
    Person tempSenders[] = {
        {"John Smith", "Hometown", "002", "0123456789", 0},
        {"Emily Johnson", "Springfield", "003", "0987654321", 0},
        {"Michael Brown", "Lakeview", "004", "0765432109", 0},
        {"Sarah Davis", "Meadow Hills", "005", "0456789123", 0},
        {"Daniel Wilson", "Pine Grove", "006", "0543219876", 0},
        {"Jessica Martinez", "Sunset Valley", "007", "0678912345", 0},
        {"Christopher Garcia", "Riverbend", "008", "0890123456", 0},
        {"Amanda Rodriguez", "Clearwater", "009", "0987654321", 0},
        {"James Miller", "Cedar Ridge", "010", "0102030405", 0},
        {"Ashley Jackson", "Oakwood", "011", "0112233445", 0}
    };

    if (numSenders >= sizeof(tempSenders) / sizeof(tempSenders[0])) {
        fprintf(stderr, "Number of senders exceeds predefined list.\n");
        return;
    }

    memcpy(senders, tempSenders, numSenders * sizeof(Person));
}

// Function to add receivers
void addReceivers(Person* receivers, int numReceivers) {
    Person tempReceivers[] = {
        {"Matthew White", "Green Acres", "012", "0123245678", 0},
        {"Elizabeth Lopez", "Golden Heights", "013", "0133456789", 0},
        {"Joshua Hill", "Willow Creek", "014", "0144567890", 0},
        {"Lauren Scott", "Silver Springs", "015", "0155678901", 0},
        {"Andrew King", "Maple Grove", "016", "0166789012", 0},
        {"Olivia Young", "Peachtree", "017", "0177890123", 0},
        {"Ryan Clark", "Hillcrest", "018", "0188901234", 0},
        {"Sophia Lewis", "Birchwood", "019", "0199012345", 0},
        {"David Walker", "Lakeside", "020", "0200123456", 0},
        {"Grace Hall", "Valley View", "021", "0211234567", 0}
    };

    if (numReceivers >= sizeof(tempReceivers) / sizeof(tempReceivers[0])) {
        fprintf(stderr, "Number of receivers exceeds predefined list.\n");
        return;
    }

    memcpy(receivers, tempReceivers, numReceivers * sizeof(Person));
}

// Function to add shippers
void addShippers(Shipper* shippers, int numShippers) {
    Shipper tempShippers[] = {
        {"Nguyen Viet Anh", "01", "0866986596", 0},
        {"Phung Thanh Thuy", "02", "0123888888", 0},
        {"Tran Cong Tai", "03", "0234999999", 0},
        {"Nguyen Thi Tu", "04", "0345777777", 0},
        {"Phung Anh Tai", "05", "0456111111", 0},
        {"Tran Viet Tu", "06", "0567222222", 0},
        {"Nguyen Cong Thanh", "07", "0678333333", 0},
        {"Phung Viet Thuy", "08", "0789444444", 0},
        {"Tran Thi Anh", "09", "0866555555", 0},
        {"Nguyen Thanh Tu", "10", "9999999999", 0}
    };

    if (numShippers >= sizeof(tempShippers) / sizeof(tempShippers[0])) {
        fprintf(stderr, "Number of shippers exceeds predefined list.\n");
        return;
    }

    memcpy(shippers, tempShippers, numShippers * sizeof(Shipper));
}




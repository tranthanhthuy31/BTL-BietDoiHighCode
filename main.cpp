#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include<fstream>

struct Date { int day, month, year; };

enum ShipmentStatus { Pending, InTransit, Delivered, Returned };
enum PaymentStatus { Unpaid, Paid };
enum ShipperStatus { ReadyToDelivery, Delivering };

std::string dateToString(const Date& date) {
    return std::to_string(date.day) + "/" + std::to_string(date.month) + "/" + std::to_string(date.year);
}

class Person {
private:
    std::string name, address, id, tel;
    int totalOrders;
 public:
    Person(const std::string& name, const std::string& address, const std::string& id, const std::string& tel, int totalOrders = 0)
        : name(name), address(address), id(id), tel(tel), totalOrders(totalOrders){}
    std::string getId() {return id;}
    std::string getName() const {return name;}
    std::string getAddress() const {return address;}
    std::string getTel()  const {return tel;}
    void displayPerson() const {
        std::cout << std::left;
        std::cout << std::setw(15) << id << " | "
            << std::setw(20) << name << " | "
            << std::setw(20) << address << " | "
            << std::setw(20) << tel << " | "
            << totalOrders << "\n";
    }

    void displayPersonForShipment() const {
        std::cout << "ID: " << id << " | "
            << "Name: " << name << " | "
            << "Address: " << address << " | "
            << "Tel: " << tel << "\n";
    }
    // Hàm xuất dữ liệu của đối tượng ra file
    void exportData(std::ofstream &out) const {
        out << "ID: " << id << " | ";
        out << "Name: " << name << " | ";
        out << "Address: "<<address<< " | ";
        out << "Tel: "<< tel <<"\n";
        out << "-----------------------\n";
    }
    

    void updateDetails(const std::string& name, const std::string& address, const std::string& tel) {
        this->name = name;
        this->address = address;
        this->tel = tel;
    }

    std::string getId() const {
        return id;
    }

    friend class SRSManagement;
};

class Shipper {
private:
    std::string name, shipperId, tel;
    ShipperStatus shipperStatus;
public:
    Shipper(const std::string& name, const std::string& shipperId, const std::string& tel, ShipperStatus shipperStatus)
        :name(name), shipperId(shipperId), tel(tel), shipperStatus(shipperStatus) {}

    std::string getShipperId() {
        return shipperId;
    }
    // Hàm xuất dữ liệu của đối tượng ra file
    void exportDataShipper(std::ofstream &out) const {
        out << "ID Shipper: " << shipperId << " | ";
        out << "Name Shipper: " << name << " | ";
        out << "Tel: "<<tel<< " | ";
        out << "Shipper Status: "<< shipperStatus <<"\n";
        out << "-----------------------\n";
    }
    void displayShipper() const {

    }

    friend class SRSManagement;

};

class Shipment {
private:
    Date sendDate, receiveDate;
    PaymentStatus paymentStatus;
    ShipmentStatus status;
    Person sender, receiver;
    std::string goodsInfo, shipmentId;
public:
    Shipment(const std::string& shipmentId, const Date& sendDate, const Date& receiveDate, const Person& sender, const Person& receiver, const std::string& goodsInfo, ShipmentStatus status, PaymentStatus paymentStatus)
        : shipmentId(shipmentId), sendDate(sendDate), receiveDate(receiveDate), sender(sender), receiver(receiver), goodsInfo(goodsInfo), status(status), paymentStatus(paymentStatus) {}

    std::string getShipmentId() const { 
        return shipmentId;
    }

    Person& getSender() {
        return sender;
    }

    Person& getReceiver() {
        return receiver;
    }
    
    void displayShipment() const {
        std::cout << std::left;
        std::cout << std::setw(15) << shipmentId << " | "
            << std::setw(20) << dateToString(sendDate) << " | "
            << std::setw(20) << dateToString(receiveDate) << " | "
            << std::setw(20) << goodsInfo << " | "
            << std::setw(20) << (status == Pending ? "Pending" : status == InTransit ? "In Transit" : status == Delivered ? "Delivered" : "Returned") << " | "
            << std::setw(20) << (paymentStatus == Unpaid ? "Unpaid" : "Paid") << " | ";
        std::cout << "-----Sender information:\n";
        sender.displayPersonForShipment();
        std::cout << "-----Receiver information:\n";
        receiver.displayPersonForShipment();
    }
    // Hàm xuất dữ liệu của đơn hàng ra file
    void exportDataShipment(std::ofstream &out) const {
        out << "ID: " << shipmentId << " | ";
        out << "Send Date: " << dateToString(sendDate) << " | ";
        out << "Receive Date: "<<dateToString(receiveDate)<< " | ";
        out << "Infor: "<< goodsInfo <<"\n";
        out << "ID Sender: " << sender.getId() << " | ";
        out << "Name Sender: " << sender.getName() << " | ";
        out << "Address Sender: "<<sender.getAddress()<< " | ";
        out << "Tel Sender: "<< sender.getTel() <<"\n";
        out << "ID Receiver: " << receiver.getId() << " | ";
        out << "Name Receiver: " << receiver.getName() << " | ";
        out << "Address Receiver: "<<receiver.getAddress()<< " | ";
        out << "Tel Receiver: "<< receiver.getTel() <<"\n";
        out << "-----------------------\n";
    }
    friend class SRSManagement;
};

class SRSManagement {
private:
    std::vector<Person> senders;
    std::vector<Person> receivers;
    std::vector<Shipment> shipments;
    std::vector<Shipper> shippers;
public:
    void addPerson(std::vector<Person>& list, const std::string& role) {
        system("CLS");
        std::string name, address, id, tel;

        std::cout << "Enter " << role << " ID: ";
        std::cin >> id;
        std::cin.ignore();

        auto it = std::find_if(list.begin(), list.end(), [id](const Person& p) {
            return p.id == id;
            });

        if (it != list.end()) {
            std::cout << role << " with ID " << id << " already exists. Please enter a new ID.\n";
            system("pause");
            return;
        }

        std::cout << "Enter " << role << " Name: ";
        std::getline(std::cin, name);

        std::cout << "Enter " << role << " Address: ";
        std::getline(std::cin, address);

        std::cout << "Enter " << role << " Tel: ";
        std::cin >> tel;
        std::cin.ignore();

        list.emplace_back(name, address, id, tel);
        std::cout << role << " added successfully!\n";
        system("pause");
    }

    void printAllPersons(const std::vector<Person>& list, const std::string& role) const {
        system("CLS");
        std::cout << "All " << role << "s:\n";
        std::cout<< "ID" << std::setw(16) << " | "
            << "Name" << std::setw(19) << " | " 
            << "Address" << std::setw(16) << " | "
            << "Tel" << std::setw(20) << " | "  
            << "Total orders" << "\n";
        for (const auto& person : list) {
            person.displayPerson();
        }
        system("pause");
    }

    void deletePerson(std::vector<Person>& list, const std::string& role) {
        system("CLS");
        std::string id;
        std::cout << "Enter " << role << " ID to delete: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Person& p) {
            return p.id == id;
            });

        if (it != list.end()) {
            list.erase(it);
            std::cout << role << " with ID " << id << " deleted successfully!\n";
            system("pause");
        }
        else {
            std::cout << role << " with ID " << id << " does not exist.\n";
            system("pause");
        }
    }

    void updatePerson(std::vector<Person>& list, const std::string& role) {
        system("CLS");
        std::string id;
        std::cout << "Enter " << role << " ID to update: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Person& p) {
            return p.id == id;
            });

        if (it != list.end()) {
            Person& personToUpdate = *it;
            int choice;
            std::cout << role << " found! What do you want to update?\n";
            std::cout << "1. Name\n2. Address\n3. Telephone\nEnter your choice: ";
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
            case 1: {
                std::string newName;
                std::cout << "Enter new name: ";
                std::getline(std::cin, newName);
                personToUpdate.updateDetails(newName, personToUpdate.address, personToUpdate.tel);
                std::cout << "Name updated successfully!\n";
                system("pause");
                break;
            }
            case 2: {
                std::string newAddress;
                std::cout << "Enter new address: ";
                std::getline(std::cin, newAddress);
                personToUpdate.updateDetails(personToUpdate.name, newAddress, personToUpdate.tel);
                std::cout << "Address updated successfully!\n";
                system("pause"); 
                break;
            }
            case 3: {
                std::string newTel;
                std::cout << "Enter new telephone: ";
                std::cin >> newTel;
                personToUpdate.updateDetails(personToUpdate.name, personToUpdate.address, newTel);
                std::cout << "Telephone updated successfully!\n";
                system("pause"); 
                break;
            }
            default:
                std::cout << "Invalid choice!\n";
                system("pause"); 
                break;
            }
        }
        else {
            std::cout << role << " with ID " << id << " does not exist.\n";
            system("pause");
        }
    }

    void findPerson(const std::vector<Person>& list, const std::string& role) const {
        system("CLS");
        std::string id;
        std::cout << "Enter " << role << " ID to find: ";
        std::cin >> id;
        std::cin.ignore();

        auto it = std::find_if(list.begin(), list.end(), [id](const Person& p) {
            return p.id == id;
            });

        if (it != list.end()) {
            it->displayPerson();
            system("pause");
        }
        else {
            std::cout << role << " with ID " << id << " does not exist. Returning to main menu.\n";
            system("pause");
        }
    }
    
    void exportToFile(const std::vector<Person>& list,const std::string &filename,const std::string&role){
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Could not open the file!" << std::endl;
            return;
        }
        outFile<<role<<":\n";
        outFile<<"==============================\n";
        for(const auto& person : list){
            person.exportData(outFile);
        }
    }
    
    void addShipment(std::vector<Shipment>& list, std::vector<Person>& senders, std::vector<Person>& receivers) {
        system("CLS");
        int status, pstatus;
        std::string goods, shipmentId, senderId, receiverId;
        Date sDate, rDate;

        std::cout << "Enter the information for new Shipment" << std::endl;

        auto findPersonById = [](std::vector<Person>& persons, std::string id) -> Person& {
            for (auto& person : persons) {
                if (person.getId() == id) {
                    return person;
                }
            }
            throw std::runtime_error("Person with ID not found.");
        };

        auto findShipmentById = [&list](std::string id) -> bool {
            for (auto& shipment : list) {
                if (shipment.getShipmentId() == id) {
                    return true;
                }
            }
            return false;
        };

        std::cout << "Enter the Sender ID: ";
        std::cin >> senderId;

        Person* sender = nullptr;
        try {
            sender = &findPersonById(senders, senderId);
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            system("pause");
            return;
        }

        std::cout << "Enter the Receiver ID: ";
        std::cin >> receiverId;

        Person* receiver = nullptr;
        try {
            receiver = &findPersonById(receivers, receiverId);
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            system("pause");
            return;
        }

        std::cout << "Enter the Shipment ID: ";
        std::cin >> shipmentId;

        if (findShipmentById(shipmentId)) {
            std::cerr << "Shipment with ID " << shipmentId << " already exists." << std::endl;
            system("pause");
            return;
        }

        std::cout << "Send Date (day month year): "; std::cin >> sDate.day >> sDate.month >> sDate.year;
        std::cout << "Receive Date (day month year): "; std::cin >> rDate.day >> rDate.month >> rDate.year;
        std::cin.ignore();
        std::cout << "Goods information: "; std::getline(std::cin, goods);
        std::cout << "Shipment Status: Pending (0) / InTransit (1) / Delivered (2) / Returned (3): "; std::cin >> status;
        std::cout << "Payment Status: Unpaid (0) / Paid (1): "; std::cin >> pstatus;

        Shipment newShipment(shipmentId, sDate, rDate, *sender, *receiver, goods, static_cast<ShipmentStatus>(status), static_cast<PaymentStatus>(pstatus));
        list.push_back(newShipment);

        sender->totalOrders++;
        receiver->totalOrders++;


        std::cout << "Shipment added successfully!" << std::endl;
        system("pause");
    }

    void printAllShipments(const std::vector<Shipment> list) const {
        system("CLS");
        std::cout << "All shipments:\n";
        std::cout << "ID" << std::setw(16) << " | "
            << "Send" << std::setw(19) << " | "
            << "Receive" << std::setw(16) << " | "
            << "Goods Info" << std::setw(20) << " | "
            << "Status" << std::setw(20) << " | "
            << "Payment Status" << "\n";
        for (const auto& shipment : list) {
            shipment.displayShipment();
        }
        system("pause");
    }

    void deleteShipment(std::vector<Shipment>& list, std::vector<Person>& senders, std::vector<Person>& receivers) {
        system("CLS");
        std::string id;
        std::cout << "Enter Shipment ID to delete: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Shipment& s) { return s.getShipmentId() == id; });

        if (it != list.end()) {
            
            auto findPersonById = [](std::vector<Person>& persons, std::string id) -> Person& {
                for (auto& person : persons) {
                    if (person.getId() == id) {
                        return person;
                    }
                }
                throw std::runtime_error("Person with ID not found.");
            };

            Person* sender = nullptr;
            try {
                sender = &findPersonById(senders, it->sender.id);
            }
            catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                system("pause");
                return;
            }

            Person* receiver = nullptr;
            try {
                receiver = &findPersonById(receivers, it->receiver.id);
            }
            catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                system("pause");
                return;
            }

            sender->totalOrders--;
            receiver->totalOrders--;

            list.erase(it);
            std::cout << "Shipment with ID " << id << " deleted successfully!\n";
            system("pause");
        }
        else {
            std::cout << "Shipment with ID " << id << " does not exist.\n";
            system("pause");
        }
    }

    void updateShipment(std::vector<Shipment>& list) {
        system("CLS");
        std::string id;
        std::cout << "Enter Shipment ID to update: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Shipment& s) { return s.shipmentId == id; });

        if (it != list.end()) {
            int choice;
            bool updateAgain = true;

            while (updateAgain) {
                system("CLS");
                std::cout << "\nSelect field to update for Shipment ID " << id << ":" << std::endl;
                std::cout << "1. Send Date\n";
                std::cout << "2. Receive Date\n";
                std::cout << "3. Status\n";
                std::cout << "4. Payment Status\n";
                std::cout << "5. Goods Info\n";
                std::cout << "6. Exit update\n";
                std::cout << "Enter your choice: ";
                std::cin >> choice;

                switch (choice) {
                case 1: {
                    // Update Send Date
                    Date newSendDate;
                    std::cout << "Enter new Send Date (day month year): ";
                    std::cin >> newSendDate.day >> newSendDate.month >> newSendDate.year;
                    it->sendDate = newSendDate;
                    std::cout << "Shipment with ID " << id << "'s Send Date updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 2: {
                    // Update Receive Date
                    Date newReceiveDate;
                    std::cout << "Enter new Receive Date (day month year): ";
                    std::cin >> newReceiveDate.day >> newReceiveDate.month >> newReceiveDate.year;
                    it->receiveDate = newReceiveDate;
                    std::cout << "Shipment with ID " << id << "'s Receive Date updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 3: {
                    std::cout << "Enter new Shipment Status: Pending (0) / InTransit (1) / Delivered (2) / Returned (3): ";
                    int statusChoice; std::cin >> statusChoice; it->status = static_cast<ShipmentStatus>(statusChoice);
                    std::cout << "Shipment with ID " << id << "'s Status updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 4: {
                    std::cout << "Enter new Payment Status: Unpaid (0) / Paid (1): ";
                    int pstatusChoice; std::cin >> pstatusChoice; it->paymentStatus = static_cast<PaymentStatus>(pstatusChoice);
                    std::cout << "Shipment with ID " << id << "'s Payment Status updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 5: {
                    std::string newGoodsInfo;
                    std::cout << "Enter new Goods Info: ";
                    std::cin.ignore();
                    std::getline(std::cin, newGoodsInfo);
                    it->goodsInfo = newGoodsInfo;
                    std::cout << "Shipment with ID " << id << "'s Goods Info updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 6:
                    updateAgain = false;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
            std::cout << "Shipment with ID " << id << " updated successfully!" << std::endl;
        }
        else {
            std::cout << "Shipment with ID " << id << " not found!" << std::endl;
            system("pause");
        }
    }

    void findShipment(std::vector<Shipment>& list) const {
        system("CLS");
        std::string id;
        std::cout << "Enter Shipment ID to find: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Shipment& s) {
            return s.getShipmentId() == id;
            });

        if (it != list.end()) {
            it->displayShipment();
            system("pause");
        }
        else {
            std::cout << "Shipment with ID " << id << " does not exist. Returning to main menu.\n";
            system("pause");
        }
    }
 
    void exportToFileShipment(const std::vector<Shipment>&list,std::string filename,std::vector<Person>& senders, std::vector<Person>& receivers){
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Could not open the file!" << std::endl;
            return;
        }
        outFile<<"SHIPMENTS"<<"\n";
        outFile<<"==============================\n";
        for(const auto& shipment :list){
            shipment.exportDataShipment(outFile);
        }

    }
    void sortShipmentsById(std::vector<Shipment>& list, bool ascending = true) {
        std::sort(list.begin(), list.end(),
            [ascending](const Shipment& a, const Shipment& b) {
                return ascending ? (a.shipmentId < b.shipmentId) : (a.shipmentId > b.shipmentId);
            });
        return;
    }

    void addShipper() {
        shippers.push_back(Shipper("Nguyễn Việt Anh", "01", "0866986596", ShipperStatus::ReadyToDelivery));
        shippers.push_back(Shipper("Phùng Thanh Thuỷ", "02", "0123888888", ShipperStatus::ReadyToDelivery));
        shippers.push_back(Shipper("Trần Công Tài", "03", "0234999999", ShipperStatus::ReadyToDelivery));
        shippers.push_back(Shipper("Nguyễn Thị Tú", "04", "0345777777", ShipperStatus::ReadyToDelivery));
        shippers.push_back(Shipper("Phùng Anh Tài", "05", "0456111111", ShipperStatus::ReadyToDelivery));
        shippers.push_back(Shipper("Trần Việt Tú", "06", "0567222222", ShipperStatus::ReadyToDelivery));
        shippers.push_back(Shipper("Nguyễn Công Thanh", "07", "0678333333", ShipperStatus::ReadyToDelivery));
        shippers.push_back(Shipper("Phùng Việt Thuỷ", "08", "0789444444", ShipperStatus::ReadyToDelivery));
        shippers.push_back(Shipper("Trần Thị Anh", "09", "0866555555", ShipperStatus::ReadyToDelivery));
        shippers.push_back(Shipper("Nguyễn Thanh Tú", "10", "9999999999", ShipperStatus::ReadyToDelivery));
    }

    void setShipperStatus(std::vector<Shipper>& shippers) {
        system("CLS");
        std::string id;
        std::cout << "Enter Shipper ID to update status: ";
        std::cin >> id;

        auto it = std::find_if(shippers.begin(), shippers.end(), [id](const Shipper& s) { return s.shipperId == id; });
        if (it != shippers.end()) {
            std::cout << "Enter new Shipper Status: ReadyToDelivery (0) / Delivering (1): ";
            int newStatus; std::cin >> newStatus; it->shipperStatus = static_cast<ShipperStatus>(newStatus);
            std::cout << "Shipper with ID " << id << "'s status updated successfully!" << std::endl;
            system("pause");
        }
        else {
            std::cout << "Shipment with ID " << id << " not found!" << std::endl;
            system("pause");
        }
    }
    
    void exportToFileShipper(const std::vector<Shipper>& shippers,std::string filename){
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Could not open the file!" << std::endl;
            return;
        }
        outFile<<"SHIPPER"<<"\n";
        outFile<<"=================================\n";
        for(const auto& shipper:shippers){
            shipper.exportDataShipper(outFile);
        }
    }

    friend void displayMenuSRManagement(SRSManagement& manager);
    friend void displaySenderMenu(SRSManagement& manager);
    friend void displayReceiverMenu(SRSManagement& manager);
    friend void displayShipmentMenu(SRSManagement& manager);
    friend void displayShipperMenu(SRSManagement& manager);
};

void displayMenuSRManagement(SRSManagement& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "Main Menu:\n";
        std::cout << "1. Sender Management\n2. Receiver Management\n3. Shipment Management\n4. Shipper Management\n5. Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            displaySenderMenu(manager);
            break;
        case 2:
            displayReceiverMenu(manager);
            break;
        case 3:
            displayShipmentMenu(manager);
        case 4:
            displayShipperMenu(manager);
        case 5:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            system("pause");
            break;
        }
    } while (choice != 5);
}

void displaySenderMenu(SRSManagement& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "Sender Management Menu:\n";
        std::cout << "1. Add a Sender\n2. Print All Senders\n3. Delete a Sender\n4. Update Sender Details\n";
        std::cout << "5. Find a Sender\n6. Export to File\n7. Return to Main Menu\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            manager.addPerson(manager.senders, "Sender");
            break;
        case 2:
            manager.printAllPersons(manager.senders, "Sender");
            break;
        case 3:
            manager.deletePerson(manager.senders, "Sender");
            break;
        case 4:
            manager.updatePerson(manager.senders, "Sender");
            break;
        case 5:
            manager.findPerson(manager.senders, "Sender");
            break;
        case 6:{
            std::string fname;                
            std::cout << "Enter the filename: ";
            std::cin >> fname;
            manager.exportToFile(manager.senders,fname, "Sender");}
            break;
        case 7:
            return;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            system("pause");
            break;
        }
    } while (choice != 7);
}

void displayReceiverMenu(SRSManagement& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "Receiver Management Menu:\n";
        std::cout << "1. Add a Receiver\n2. Print All Receivers\n3. Delete a Receiver\n4. Update Receiver Details\n";
        std::cout << "5. Find a Receiver\n6. Export to File\n7. Return to Main Menu\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            manager.addPerson(manager.receivers, "Receiver");
            break;
        case 2:
            manager.printAllPersons(manager.receivers, "Receiver");
            break;
        case 3:
            manager.deletePerson(manager.receivers, "Receiver");
            break;
        case 4:
            manager.updatePerson(manager.receivers, "Receiver");
            break;
        case 5:
            manager.findPerson(manager.receivers, "Receiver");
            break;
        case 6:{
            std::string fname;                
            std::cout << "Enter the filename: ";
            std::cin >> fname;
            manager.exportToFile(manager.receivers,fname,"Receiver");}
            break;    
        case 7:
            return;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            system("pause");
            break;
        }
    } while (choice != 7);
}

void displayShipmentMenu(SRSManagement& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "Shipment Management Menu:\n";
        std::cout << "1. Add a Shipment\n2. Print All Shipments\n3. Delete a Shipment\n4. Update Shipment Details\n";
        std::cout << "5. Find a Shipments\n6. Sort Shipments by ID\n7. Export to File\n8. Return to Main Menu\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            manager.addShipment(manager.shipments, manager.senders, manager.receivers);
            break;
        case 2:
            manager.printAllShipments(manager.shipments);
            break;
        case 3:
            manager.deleteShipment(manager.shipments, manager.senders, manager.receivers);
            break;
        case 4:
            manager.updateShipment(manager.shipments);
            break;
        case 5:
            manager.findShipment(manager.shipments);
            break;
        case 6:
            system("CLS");
            int orderChoice;
            std::cout << "1. Ascending\n2. Descending" << std::endl;
            std::cout << "Enter your choice: "; std::cin >> orderChoice;
            if (orderChoice == 1) {
                manager.sortShipmentsById(manager.shipments, orderChoice == 1);
                std::cout << "Shipments sorted by ID (Ascending)!" << std::endl;
                system("pause");
            }
            else if (orderChoice == 2) {
                manager.sortShipmentsById(manager.shipments, orderChoice == 0);
                std::cout << "Shipments sorted by ID (Descending)!" << std::endl;
                system("pause");
            }
            else {
                std::cout << "Invalid order choice!" << std::endl;
            }
            break;
        case 7:{
            std::string fname;                
            std::cout << "Enter the filename: ";
            std::cin >> fname;
            manager.exportToFileShipment(manager.shipments,fname,manager.senders,manager.receivers);}
            break;
        case 8:
            return;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            system("pause");
            break;
        }
    } while (choice != 8);
}

void displayShipperMenu(SRSManagement& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "Shipper Management Menu:\n";
        std::cout << "1. Print All Shippers\n2. Set status for a Shipper\n3. Export to file list Shipper\n4. Return to Main Menu\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            //Hàm printAllShipers
            break;
        case 2:
            manager.setShipperStatus(manager.shippers);
            break;
        case 3:{
            std::string fname;                
            std::cout << "Enter the filename: ";
            std::cin >> fname;
            manager.exportToFileShipper(manager.shippers,fname);}
            break;   
        case 4:
            
            return;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            system("pause");
            break;
        }
    } while (choice != 4);
}

int main() {
    SRSManagement srsm;
    srsm.addShipper();
    displayMenuSRManagement(srsm);
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>

struct Date { int day, month, year; };

enum OrderStatus { Pending, InTransit, Delivered, Returned };
enum PaymentStatus { Unpaid, Paid };
enum ShipperStatus { ReadyToDeliver, Delivering };

std::string dateToString(const Date& date) {
    return std::to_string(date.day) + "/" + std::to_string(date.month) + "/" + std::to_string(date.year);
}

class Person {
private:
    std::string name, address, id, tel;
    int totalOrders;
public:
    Person(const std::string& name, const std::string& address, const std::string& id, const std::string& tel, int totalOrders = 0)
        : name(name), address(address), id(id), tel(tel), totalOrders(totalOrders) {}

    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getTel()  const { return tel; }

    void displayPerson() const {
        std::cout << std::left
            << std::setw(10) << id
            << std::setw(20) << name
            << std::setw(20) << address
            << std::setw(16) << tel
            << std::setw(10) << totalOrders << std::endl;
    }

    void displayPersonForOrder() const {
        std::cout << "ID: " << id << " |" << "Name: " << name << " |" << "Address: " << address << " |" << "Tel: " << tel << "\n";
    }
    // Hàm xuất dữ liệu của đối tượng ra file
    void exportData(std::ofstream& out) const {
        out << "ID: " << id << " | ";
        out << "Name: " << name << " | ";
        out << "Address: " << address << " | ";
        out << "Tel: " << tel << "\n";
        out << "-----------------------\n";
    }

    void updateDetails(const std::string& name, const std::string& address, const std::string& tel) {
        this->name = name;
        this->address = address;
        this->tel = tel;
    }

    friend class Management;
};

class Shipper {
private:
    std::string name, shipperId, tel;
    ShipperStatus shipperStatus;
public:
    Shipper(const std::string& name, const std::string& shipperId, const std::string& tel, ShipperStatus shipperStatus)
        :name(name), shipperId(shipperId), tel(tel), shipperStatus(shipperStatus) {}

    std::string getShipperId() { return shipperId; }
    // Hàm xuất dữ liệu của đối tượng ra file
    void exportDataShipper(std::ofstream& out) const {
        out << "ID Shipper: " << shipperId << " | ";
        out << "Name Shipper: " << name << " | ";
        out << "Tel: " << tel << " | ";
        out << "Shipper Status: " << shipperStatus << "\n";
        out << "-----------------------\n";
    }

    void displayShipper() const {
        std::cout << std::left
            << std::setw(10) << shipperId
            << std::setw(20) << name
            << std::setw(16) << tel
            << std::setw(10) << (shipperStatus == ReadyToDeliver ? "Ready to deliver" : "Delivering") << std::endl;
    }

    friend class Management;
};

class Order {
private:
    Date sendDate, receiveDate;
    PaymentStatus paymentStatus;
    OrderStatus status;
    Person sender, receiver;
    std::string goodsInfo, orderId;
public:
    Order(const std::string& orderId, const Date& sendDate, const Date& receiveDate, const Person& sender, const Person& receiver, const std::string& goodsInfo, OrderStatus status, PaymentStatus paymentStatus)
        : orderId(orderId), sendDate(sendDate), receiveDate(receiveDate), sender(sender), receiver(receiver), goodsInfo(goodsInfo), status(status), paymentStatus(paymentStatus) {}

    std::string getOrderId() const { return orderId; }

    const Date& getSendDate() const { return sendDate; }
    const Date& getReceiveDate() const { return receiveDate; }

    Person& getSender() { return sender; }

    Person& getReceiver() { return receiver; }

    void displayOrder() const {
        std::cout << std::left
            << std::setw(15) << "ID"
            << std::setw(15) << "Send Date"
            << std::setw(15) << "Receive Date"
            << std::setw(15) << "Goods Info"
            << std::setw(15) << "Status"
            << std::setw(15) << "Payment Status" << std::endl;
        std::cout << std::setw(15) << orderId
            << std::setw(15) << dateToString(sendDate)
            << std::setw(15) << dateToString(receiveDate)
            << std::setw(15) << goodsInfo
            << std::setw(15) << (status == Pending ? "Pending" : status == InTransit ? "In Transit" : status == Delivered ? "Delivered" : "Returned")
            << std::setw(15) << (paymentStatus == Unpaid ? "Unpaid" : "Paid") << std::endl;
        std::cout << "-----Sender information:\n";
        sender.displayPersonForOrder();
        std::cout << "-----Receiver information:\n";
        receiver.displayPersonForOrder();
        std::cout << std::string(100, '-');
        std::cout << "\n";
    }
    // Hàm xuất dữ liệu của đơn hàng ra file
    void exportDataOrder(std::ofstream& out) const {
        out << "ID: " << orderId << " | ";
        out << "Send Date: " << dateToString(sendDate) << " | ";
        out << "Receive Date: " << dateToString(receiveDate) << " | ";
        out << "Infor: " << goodsInfo << "\n";
        out << "ID Sender: " << sender.getId() << " | ";
        out << "Name Sender: " << sender.getName() << " | ";
        out << "Address Sender: " << sender.getAddress() << " | ";
        out << "Tel Sender: " << sender.getTel() << "\n";
        out << "ID Receiver: " << receiver.getId() << " | ";
        out << "Name Receiver: " << receiver.getName() << " | ";
        out << "Address Receiver: " << receiver.getAddress() << " | ";
        out << "Tel Receiver: " << receiver.getTel() << "\n";
        out << "-----------------------\n";
    }

    friend class Management;
};

class Management {
private:
    std::vector<Person> senders;
    std::vector<Person> receivers;
    std::vector<Order> orders;
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
        std::cout << std::left
            << std::setw(10) << "ID"
            << std::setw(20) << "Name"
            << std::setw(20) << "Address"
            << std::setw(16) << "Tel"
            << std::setw(10) << "Orders" << std::endl;

        std::cout << std::string(81, '-');
        std::cout << "\n";
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

    void sortPersonById(std::vector<Person>& list, bool ascending = true) {
        std::sort(list.begin(), list.end(),
            [ascending](const Person& a, const Person& b) {
                return ascending ? (a.getId() < b.getId()) : (a.getId() > b.getId());
            });
        return;
    }

    void exportToFile(const std::vector<Person>& list, const std::string& filename, const std::string& role) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Could not open the file!" << std::endl;
            return;
        }
        outFile << role << ":\n";
        outFile << "==============================\n";
        for (const auto& person : list) {
            person.exportData(outFile);
        }
    }
    //---------//
    void addOrder(std::vector<Order>& list, std::vector<Person>& senders, std::vector<Person>& receivers) {
        system("CLS");
        int status, pstatus;
        std::string goods, orderId, senderId, receiverId;
        Date sDate, rDate;

        std::cout << "Enter the information for new Order" << std::endl;

        auto findPersonById = [](std::vector<Person>& persons, std::string id) -> Person& {
            for (auto& person : persons) {
                if (person.getId() == id) {
                    return person;
                }
            }
            throw std::runtime_error("Person with ID not found.");
        };

        auto findOrderById = [&list](std::string id) -> bool {
            for (auto& order : list) {
                if (order.getOrderId() == id) {
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

        std::cout << "Enter the Order ID: ";
        std::cin >> orderId;

        if (findOrderById(orderId)) {
            std::cerr << "Order with ID " << orderId << " already exists." << std::endl;
            system("pause");
            return;
        }

        std::cout << "Send Date (day month year): "; std::cin >> sDate.day >> sDate.month >> sDate.year;
        std::cout << "Receive Date (day month year): "; std::cin >> rDate.day >> rDate.month >> rDate.year;
        std::cin.ignore();
        std::cout << "Goods information: "; std::getline(std::cin, goods);
        std::cout << "Order Status: Pending (0) / InTransit (1) / Delivered (2) / Returned (3): "; std::cin >> status;
        std::cout << "Payment Status: Unpaid (0) / Paid (1): "; std::cin >> pstatus;

        Order newShipment(orderId, sDate, rDate, *sender, *receiver, goods, static_cast<OrderStatus>(status), static_cast<PaymentStatus>(pstatus));
        list.push_back(newShipment);

        sender->totalOrders++;
        receiver->totalOrders++;

        std::cout << "Order added successfully!" << std::endl;
        system("pause");
    }

    void printAllOrders(const std::vector<Order> list) const {
        system("CLS");
        std::cout << "All orders:\n";
        for (const auto& order : list) {
            order.displayOrder();
        }
        system("pause");
    }

    void deleteOrder(std::vector<Order>& list, std::vector<Person>& senders, std::vector<Person>& receivers) {
        system("CLS");
        std::string id;
        std::cout << "Enter Order ID to delete: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Order& o) { return o.getOrderId() == id; });

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
            std::cout << "Order with ID " << id << " deleted successfully!\n";
            system("pause");
        }
        else {
            std::cout << "Order with ID " << id << " does not exist.\n";
            system("pause");
        }
    }

    void updateOrder(std::vector<Order>& list) {
        system("CLS");
        std::string id;
        std::cout << "Enter Order ID to update: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Order& o) { return o.orderId == id; });

        if (it != list.end()) {
            int choice;
            bool updateAgain = true;

            while (updateAgain) {
                system("CLS");
                std::cout << "\nSelect field to update for Order ID " << id << ":" << std::endl;
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
                    std::cout << "Order with ID " << id << "'s Send Date updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 2: {
                    // Update Receive Date
                    Date newReceiveDate;
                    std::cout << "Enter new Receive Date (day month year): ";
                    std::cin >> newReceiveDate.day >> newReceiveDate.month >> newReceiveDate.year;
                    it->receiveDate = newReceiveDate;
                    std::cout << "Order with ID " << id << "'s Receive Date updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 3: {
                    std::cout << "Enter new Order Status: Pending (0) / InTransit (1) / Delivered (2) / Returned (3): ";
                    int statusChoice; std::cin >> statusChoice; it->status = static_cast<OrderStatus>(statusChoice);
                    std::cout << "Order with ID " << id << "'s Status updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 4: {
                    std::cout << "Enter new Payment Status: Unpaid (0) / Paid (1): ";
                    int pstatusChoice; std::cin >> pstatusChoice; it->paymentStatus = static_cast<PaymentStatus>(pstatusChoice);
                    std::cout << "Order with ID " << id << "'s Payment Status updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 5: {
                    std::string newGoodsInfo;
                    std::cout << "Enter new Goods Info: ";
                    std::cin.ignore();
                    std::getline(std::cin, newGoodsInfo);
                    it->goodsInfo = newGoodsInfo;
                    std::cout << "Order with ID " << id << "'s Goods Info updated successfully!" << std::endl;
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
            std::cout << "Order with ID " << id << " updated successfully!" << std::endl;
        }
        else {
            std::cout << "Order with ID " << id << " not found!" << std::endl;
            system("pause");
        }
    }

    void findOrder(std::vector<Order>& list) const {
        system("CLS");
        std::string id;
        std::cout << "Enter Order ID to find: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Order& o) {
            return o.getOrderId() == id;
            });

        if (it != list.end()) {
            it->displayOrder();
            system("pause");
        }
        else {
            std::cout << "Order with ID " << id << " does not exist. Returning to main menu.\n";
            system("pause");
        }
    }

    void exportToFileOrder(const std::vector<Order>& list, std::string filename, std::vector<Person>& senders, std::vector<Person>& receivers) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Could not open the file!" << std::endl;
            return;
        }
        outFile << "ORDERS" << "\n";
        outFile << "==============================\n";
        for (const auto& order : list) {
            order.exportDataOrder(outFile);
        }
    }

    void sortOrdersById(std::vector<Order>& list, bool ascending = true) {
        std::sort(list.begin(), list.end(),
            [ascending](const Order& a, const Order& b) {
                return ascending ? (a.orderId < b.orderId) : (a.orderId > b.orderId);
            });
        return;
    }

    int compareDates(const Date& d1, const Date& d2) {
    if (d1.year != d2.year) return d1.year < d2.year;
    if (d1.month != d2.month) return d1.month < d2.month;
    return d1.day < d2.day;
}

    void sortOrdersByDate(std::vector<Order>& orders, bool ascending = true) {
    std::sort(orders.begin(), orders.end(), [this, ascending](const Order& a, const Order& b) {
        return ascending ? compareDates(a.getSendDate(), b.getSendDate()) : compareDates(b.getSendDate(), a.getSendDate());
    });
}
    //---------//
    void printAllShippers(const std::vector<Shipper>& list) const {
        system("CLS");
        std::cout << std::left
            << std::setw(10) << "ID"
            << std::setw(20) << "Name"
            << std::setw(16) << "Tel"
            << std::setw(10) << "Shipper Status" << std::endl;
        std::cout << std::string(81, '-');
        std::cout << "\n";
        for (const auto& person : list) {
            person.displayShipper();
        }
        system("pause");
    }

    void setShipperStatus(std::vector<Shipper>& shippers) {
        system("CLS");
        std::string id;
        std::cout << "Enter Shipper ID to update status: ";
        std::cin >> id;

        auto it = std::find_if(shippers.begin(), shippers.end(), [id](const Shipper& o) { return o.shipperId == id; });
        if (it != shippers.end()) {
            std::cout << "Enter new Shipper Status: ReadyToDeliver (0) / Delivering (1): ";
            int newStatus; std::cin >> newStatus; it->shipperStatus = static_cast<ShipperStatus>(newStatus);
            std::cout << "Shipper with ID " << id << "'s status updated successfully!" << std::endl;
            system("pause");
        }
        else {
            std::cout << "Order with ID " << id << " not found!" << std::endl;
            system("pause");
        }
    }

    void exportToFileShipper(const std::vector<Shipper>& shippers, std::string filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Could not open the file!" << std::endl;
            return;
        }
        outFile << "SHIPPER" << "\n";
        outFile << "=================================\n";
        for (const auto& shipper : shippers) {
            shipper.exportDataShipper(outFile);
        }
    }

    void addSenders() {
        senders.push_back(Person("John Smith", "Hometown", "002", "0123456789", 0));
        senders.push_back(Person("Emily Johnson", "Springfield", "003", "0987654321", 0));
        senders.push_back(Person("Michael Brown", "Lakeview", "004", "0765432109", 0));
        senders.push_back(Person("Sarah Davis", "Meadow Hills", "005", "0456789123", 0));
        senders.push_back(Person("Daniel Wilson", "Pine Grove", "006", "0543219876", 0));
        senders.push_back(Person("Jessica Martinez", "Sunset Valley", "007", "0678912345", 0));
        senders.push_back(Person("Christopher Garcia", "Riverbend", "008", "0890123456", 0));
        senders.push_back(Person("Amanda Rodriguez", "Clearwater", "009", "0987654321", 0));
        senders.push_back(Person("James Miller", "Cedar Ridge", "010", "0102030405", 0));
        senders.push_back(Person("Ashley Jackson", "Oakwood", "011", "0112233445", 0));
    }
    void addReceivers() {
        receivers.push_back(Person("Matthew White", "Green Acres", "012", "0123245678", 0));
        receivers.push_back(Person("Elizabeth Lopez", "Golden Heights", "013", "0133456789", 0));
        receivers.push_back(Person("Joshua Hill", "Willow Creek", "014", "0144567890", 0));
        receivers.push_back(Person("Lauren Scott", "Silver Springs", "015", "0155678901", 0));
        receivers.push_back(Person("Andrew King", "Maple Grove", "016", "0166789012", 0));
        receivers.push_back(Person("Olivia Young", "Peachtree", "017", "0177890123", 0));
        receivers.push_back(Person("Ryan Clark", "Hillcrest", "018", "0188901234", 0));
        receivers.push_back(Person("Sophia Lewis", "Birchwood", "019", "0199012345", 0));
        receivers.push_back(Person("David Walker", "Lakeside", "020", "0200123456", 0));
        receivers.push_back(Person("Grace Hall", "Valley View", "021", "0211234567", 0));
    }
    void addShipper() {
        shippers.push_back(Shipper("Nguyen Viet Anh", "01", "0866986596", ShipperStatus::ReadyToDeliver));
        shippers.push_back(Shipper("Phung Thanh Thuy", "02", "0123888888", ShipperStatus::ReadyToDeliver));
        shippers.push_back(Shipper("Tran Cong Tai", "03", "0234999999", ShipperStatus::ReadyToDeliver));
        shippers.push_back(Shipper("Nguyen Thi Tu", "04", "0345777777", ShipperStatus::ReadyToDeliver));
        shippers.push_back(Shipper("Phung Anh Tai", "05", "0456111111", ShipperStatus::ReadyToDeliver));
        shippers.push_back(Shipper("Tran Viet Tu", "06", "0567222222", ShipperStatus::ReadyToDeliver));
        shippers.push_back(Shipper("Nguyen Cong Thanh", "07", "0678333333", ShipperStatus::ReadyToDeliver));
        shippers.push_back(Shipper("Phung Viet Thuy", "08", "0789444444", ShipperStatus::ReadyToDeliver));
        shippers.push_back(Shipper("Tran Thi Anh", "09", "0866555555", ShipperStatus::ReadyToDeliver));
        shippers.push_back(Shipper("Nguyen Thanh Tu", "10", "9999999999", ShipperStatus::ReadyToDeliver));
    }

    friend void displayMenuManagement(Management& manager);
    friend void displaySenderMenu(Management& manager);
    friend void displayReceiverMenu(Management& manager);
    friend void displayOrderMenu(Management& manager);
    friend void displayShipperMenu(Management& manager);
};

void displayMenuManagement(Management& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "\t\t  BIET DOI HIGH CODE\t" << std::endl;
        std::cout << "====================MENU-MANAGEMENT===================\n";
        std::cout << "==               1.Sender Management                ==\n";
        std::cout << "==               2.Receiver Management              ==\n";
        std::cout << "==               3.Order Management                 ==\n";
        std::cout << "==               4.Shipper Management               ==\n";
        std::cout << "==               5.Exit                             ==\n";
        std::cout << "======================================================\n";
        std::cout <<" Enter your choice:"; 
        std::cin >> choice;

        switch (choice) {
        case 1:
            displaySenderMenu(manager);
            break;
        case 2:
            displayReceiverMenu(manager);
            break;
        case 3:
            displayOrderMenu(manager);
            break;
        case 4:
            displayShipperMenu(manager);
            break;
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

void displaySenderMenu(Management& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "\t\t  BIET DOI HIGH CODE\t" << std::endl;
        std::cout << "====================SENDER-MANAGEMENT===================\n";
        std::cout << "==               1.Add Sender                         ==\n";
        std::cout << "==               2.Print Sender List                  ==\n";
        std::cout << "==               3.Delete Sender By ID                ==\n";
        std::cout << "==               4.Update Sender By ID                ==\n";
        std::cout << "==               5.Find Sender By ID                  ==\n";
        std::cout << "==               6.Sort Sender List By ID             ==\n";
        std::cout << "==               7.Export Sender List To File         ==\n";
        std::cout << "==               8.Return To Main Menu                ==\n";
        std::cout << "========================================================\n";
        std::cout <<" Enter your choice:"; 
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
        case 6:
            system("CLS");
            int personChoice;
            std::cout << "1. Ascending\n2. Descending" << std::endl;
            std::cout << "Enter your choice: "; std::cin >> personChoice;
            if (personChoice == 1) {
                manager.sortPersonById(manager.senders, personChoice == 1);
                std::cout << "Senders sorted by ID (Ascending)!" << std::endl;
                system("pause");
            }
            else if (personChoice == 2) {
                manager.sortPersonById(manager.senders, personChoice == 0);
                std::cout << "Senders sorted by ID (Descending)!" << std::endl;
                system("pause");
            }
            else {
                std::cout << "Invalid order choice!" << std::endl;
            }
            break;
        case 7: {
            system("CLS");
            std::string fname;
            std::cout << "Enter the filename: ";
            std::cin >> fname;
            manager.exportToFile(manager.senders, fname, "Sender");
            std::cout<<"\nExport File Successfully !\n"; }
              system("pause");
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

void displayReceiverMenu(Management& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "\t\t  BIET DOI HIGH CODE\t" << std::endl;
        std::cout << "====================RECEIVER-MANAGEMENT===================\n";
        std::cout << "==               1.Add Receiver                         ==\n";
        std::cout << "==               2.Print Receiver List                  ==\n";
        std::cout << "==               3.Delete Receiver By ID                ==\n";
        std::cout << "==               4.Update Receiver By ID                ==\n";
        std::cout << "==               5.Find Receiver By ID                  ==\n";
        std::cout << "==               6.Sort Receiver List By ID             ==\n";
        std::cout << "==               7.Export Receiver List To File         ==\n";
        std::cout << "==               8.Return To Main Menu                  ==\n";
        std::cout << "==========================================================\n";
        std::cout <<" Enter your choice:"; 
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
        case 6:
            system("CLS");
            int personChoice;
            std::cout << "1. Ascending\n2. Descending" << std::endl;
            std::cout << "Enter your choice: "; std::cin >> personChoice;
            if (personChoice == 1) {
                manager.sortPersonById(manager.receivers, personChoice == 1);
                std::cout << "Receivers sorted by ID (Ascending)!" << std::endl;
                system("pause");
            }
            else if (personChoice == 2) {
                manager.sortPersonById(manager.receivers, personChoice == 0);
                std::cout << "Receivers sorted by ID (Descending)!" << std::endl;
                system("pause");
            }
            else {
                std::cout << "Invalid order choice!" << std::endl;
            }
            break;
        case 7: {
            system("CLS");
            std::string fname;
            std::cout << "Enter the filename: ";
            std::cin >> fname;
            manager.exportToFile(manager.receivers, fname, "Receiver"); 
            std::cout<<"\nExport File Successfully !\n";}
              system("pause");
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

void displayOrderMenu(Management& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "\t\t  BIET DOI HIGH CODE\t" << std::endl;
        std::cout << "====================ORDER-MANAGEMENT===================\n";
        std::cout << "==               1.Add Order                         ==\n";
        std::cout << "==               2.Print Order List                  ==\n";
        std::cout << "==               3.Delete Order By ID                ==\n";
        std::cout << "==               4.Update Order By ID                ==\n";
        std::cout << "==               5.Find Order By ID                  ==\n";
        std::cout << "==               6.Sort Order List By ID             ==\n";
        std::cout << "==               7.Sort Order List By Date           ==\n";
        std::cout << "==               8.Export Order List To File         ==\n";
        std::cout << "==               9.Return To Main Menu               ==\n";
        std::cout << "=======================================================\n";
        std::cout <<" Enter your choice:"; 
        std::cin >> choice;

        switch (choice) {
        case 1:
            manager.addOrder(manager.orders, manager.senders, manager.receivers);
            break;
        case 2:
            manager.printAllOrders(manager.orders);
            break;
        case 3:
            manager.deleteOrder(manager.orders, manager.senders, manager.receivers);
            break;
        case 4:
            manager.updateOrder(manager.orders);
            break;
        case 5:
            manager.findOrder(manager.orders);
            break;
        case 6:
            system("CLS");
            int orderChoice;
            std::cout << "1. Ascending\n2. Descending" << std::endl;
            std::cout << "Enter your choice: "; std::cin >> orderChoice;
            if (orderChoice == 1) {
                manager.sortOrdersById(manager.orders, true);
                std::cout << "Orders sorted by ID (Ascending)!" << std::endl;
                system("pause");
            }
            else if (orderChoice == 2) {
                manager.sortOrdersById(manager.orders, false);
                std::cout << "Orders sorted by ID (Descending)!" << std::endl;
                system("pause");
            }
            else {
                std::cout << "Invalid order choice!" << std::endl;
            }
            break;
        case 7:
            system("CLS");
            int dateChoice;
            std::cout << "1. Ascending\n2. Descending" << std::endl;
            std::cout << "Enter your choice: "; std::cin >> dateChoice;
            if (dateChoice == 1) {
                manager.sortOrdersByDate(manager.orders, true);
                std::cout << "Orders sorted by Date (Ascending)!" << std::endl;
                system("pause");
            }
            else if (dateChoice == 2) {
                manager.sortOrdersByDate(manager.orders, false);
                std::cout << "Orders sorted by Date (Descending)!" << std::endl;
                system("pause");
            }
            else {
                std::cout << "Invalid date choice!" << std::endl;
            }
            break;
        case 8: {
            system("CLS");
            std::string fname;
            std::cout << "Enter the filename: ";
            std::cin >> fname;
            manager.exportToFileOrder(manager.orders, fname, manager.senders, manager.receivers);
            std::cout<<"\nExport File Successfully !\n";
        }
              system("pause");
              break;
        case 9:
            return;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            system("pause");
            break;
        }
    } while (choice != 9);
}

void displayShipperMenu(Management& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "\t\t  BIET DOI HIGH CODE\t" << std::endl;
        std::cout << "====================SHIPPER-MANAGEMENT===================\n";
        std::cout << "==               1.Print Shipper List                  ==\n";
        std::cout << "==               2.Set Shipper Status                  ==\n";
        std::cout << "==               3.Export Shipper List To File         ==\n";
        std::cout << "==               4.Return To Main Menu                 ==\n";
        std::cout << "=========================================================\n";
        std::cout <<" Enter your choice:"; 
        std::cin >> choice;

        switch (choice) {
        case 1:
            manager.printAllShippers(manager.shippers);
            break;
        case 2:
            manager.setShipperStatus(manager.shippers);
            break;
        case 3: {
            system("CLS");
            std::string fname;
            std::cout << "Enter the filename: ";
            std::cin >> fname;
            manager.exportToFileShipper(manager.shippers, fname);
            std::cout<<"\nExport File Successfully !\n"; }
            system("pause");
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
    Management manager;
    manager.addShipper(); //example
    manager.addSenders(); //example
    manager.addReceivers(); //example
    displayMenuManagement(manager);
    return 0;
}
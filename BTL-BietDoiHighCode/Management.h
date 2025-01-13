#pragma once
#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include"Person.h"
#include"Shipment.h"
#include"Shipper.h"

class Management {

private:

    std::vector<Person> senders;
    std::vector<Person> receivers;
    std::vector<Shipment> Shipments;
    std::vector<Shipper> shippers;

public:
    void addPerson(std::vector<Person>& list, const std::string& role) ;

    void printAllPersons(const std::vector<Person>& list, const std::string& role) const;

    void deletePerson(std::vector<Person>& list, const std::string& role) ;

    void updatePerson(std::vector<Person>& list, const std::string& role);

    void findPerson(const std::vector<Person>& list, const std::string& role) const ;

    void sortPersonById(std::vector<Person>& list, bool ascending = true) ;

    void exportToFile(const std::vector<Person>& list, const std::string& filename, const std::string& role) ;

    //---------//

    void addShipment(std::vector<Shipment>& list, std::vector<Person>& senders, std::vector<Person>& receivers) ;

    void printAllShipments(const std::vector<Shipment> list) const ;

    void deleteShipment(std::vector<Shipment>& list, std::vector<Person>& senders, std::vector<Person>& receivers) ;

    void updateShipment(std::vector<Shipment>& list) ;

    void findShipment(std::vector<Shipment>& list) const ;

    void exportToFileShipment(const std::vector<Shipment>& list, std::string filename, std::vector<Person>& senders, std::vector<Person>& receivers);

    void sortShipmentsById(std::vector<Shipment>& list, bool ascending = true) ;

    void sortShipmentsByDate(std::vector<Shipment>& Shipments, bool ascending = true) ;

    //---------//

    void printAllShippers(const std::vector<Shipper>& list) const ;

    void setShipperStatus(std::vector<Shipper>& shippers);

    void exportToFileShipper(const std::vector<Shipper>& shippers, std::string filename) ;

    //---thêm dữ liệu lấy ví dụ---//

    void addSenders() ;

    void addReceivers() ;

    void addShipper() ;

    friend void displayMenuManagement(Management& manager);
    friend void displaySenderMenu(Management& manager);
    friend void displayReceiverMenu(Management& manager);
    friend void displayShipmentMenu(Management& manager);
    friend void displayShipperMenu(Management& manager);
};

#endif
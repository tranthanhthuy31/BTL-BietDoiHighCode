#include "LinkedList.h"
#include <iostream>
#include <string>

// Cấu trúc Person
struct Person {
    std::string id;
    std::string name;
    std::string address;
    std::string tel;

    // Để so sánh dữ liệu của Person
    bool operator==(const Person& other) const {
        return id == other.id;
    }
};

// Hàm in thông tin một Person
void printPerson(const Person& person) {
    std::cout << "ID: " << person.id
              << ", Name: " << person.name
              << ", Address: " << person.address
              << ", Tel: " << person.tel << "\n";
}

int main() {
    LinkedList<Person> personList;

    // Tạo các đối tượng Person
    Person p1{"001", "Alice", "123 Main St", "123456789"};
    Person p2{"002", "Bob", "456 Elm St", "987654321"};
    Person p3{"001", "Charlie", "789 Oak St", "111222333"}; // Trùng ID với p1

    // Thêm các Person vào danh sách
    std::cout << "Adding Person 1:\n";
    personList.push_back(p1);

    std::cout << "Adding Person 2:\n";
    personList.push_back(p2);

    std::cout << "Adding Person 3 (duplicate ID):\n";
    personList.push_back(p3); 

    std::cout << "\nList of Persons:\n";
    personList.for_each(printPerson);

    return 0;
}


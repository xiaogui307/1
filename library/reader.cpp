#include "reader.h"
#include "book.h"
#include <iostream>

// ==================== 基类 Reader 实现 ====================

Reader::Reader(std::string n, std::string id, std::string d)
    : name(n), userId(id), department(d) {
}

std::string Reader::getName() const { return name; }
std::string Reader::getUserId() const { return userId; }
std::string Reader::getDepartment() const { return department; }
std::vector<Book*> Reader::getBorrowedBooks() const { return borrowedBooks; }
int Reader::getBorrowedCount() const {
    return static_cast<int>(borrowedBooks.size());
}

void Reader::setName(std::string n) { name = n; }
void Reader::setDepartment(std::string d) { department = d; }

// 借书：基类实现，内部通过虚函数多态获取上限和借期
bool Reader::borrowBook(Book* b) {
    if (!canBorrowMore()) {
        std::cout << "错误：已达到最大借阅数量（"
            << getMaxBorrowLimit() << "本）！" << std::endl;
        return false;
    }
    if (b->getIsBorrowed()) {
        std::cout << "错误：该书已被借出！" << std::endl;
        return false;
    }
    b->borrowBook(this, getBorrowDays());   // 借几天？问虚函数
    borrowedBooks.push_back(b);
    return true;
}

bool Reader::returnBook(Book* b) {
    for (size_t i = 0; i < borrowedBooks.size(); i++) {
        if (borrowedBooks[i] == b) {
            borrowedBooks.erase(borrowedBooks.begin() + i);
            b->returnBook();
            return true;
        }
    }
    return false;
}

bool Reader::hasBook(Book* b) const {
    for (size_t i = 0; i < borrowedBooks.size(); i++) {
        if (borrowedBooks[i] == b) {
            return true;
        }
    }
    return false;
}

bool Reader::canBorrowMore() const {
    return borrowedBooks.size() < static_cast<size_t>(getMaxBorrowLimit());
}

// ==================== 派生类 Student 实现 ====================

Student::Student(std::string n, std::string id, std::string d)
    : Reader(n, id, d) {          // 初始化基类部分
}

int Student::getMaxBorrowLimit() const { return 5; }
int Student::getBorrowDays() const { return 30; }

void Student::displayInfo() const {
    std::cout << "学生: " << name << "  学号: " << userId
        << "  院系: " << department << std::endl;
    std::cout << "最大借阅数: " << getMaxBorrowLimit()
        << " 本  已借: " << borrowedBooks.size() << " 本" << std::endl;
    if (!borrowedBooks.empty()) {
        std::cout << "  已借图书: ";
        for (size_t i = 0; i < borrowedBooks.size(); i++) {
            std::cout << borrowedBooks[i]->getTitle();
            if (i < borrowedBooks.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

// ==================== 派生类 Teacher 实现 ====================

Teacher::Teacher(std::string n, std::string id, std::string d)
    : Reader(n, id, d) {
}

int Teacher::getMaxBorrowLimit() const { return 10; }
int Teacher::getBorrowDays() const { return 60; }

void Teacher::displayInfo() const {
    std::cout << "教师: " << name << "  工号: " << userId
        << "  院系: " << department << std::endl;
    std::cout << "最大借阅数: " << getMaxBorrowLimit()
        << " 本  已借: " << borrowedBooks.size() << " 本" << std::endl;
    if (!borrowedBooks.empty()) {
        std::cout << "  已借图书: ";
        for (size_t i = 0; i < borrowedBooks.size(); i++) {
            std::cout << borrowedBooks[i]->getTitle();
            if (i < borrowedBooks.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

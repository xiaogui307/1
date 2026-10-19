#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <ctime>

class Reader;   // 前置声明：只告诉编译器"Reader 是一个类"，不包含 reader.h

class Book {
private:
    std::string barcode;
    std::string isbn;
    std::string title;
    std::string author;
    std::string publisher;
    std::string category;
    bool isBorrowed;
    Reader* borrower;        // 借阅者指针（指回借走它的人）
    time_t borrowDate;
    time_t dueDate;

public:
    Book(std::string bc, std::string i, std::string t,
        std::string a, std::string p, std::string c);

    // Getter
    std::string getBarcode() const;
    std::string getIsbn() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    std::string getCategory() const;
    bool getIsBorrowed() const;
    Reader* getBorrower() const;      // 返回借阅者指针（替代原来的 getBorrowerId）
    time_t getBorrowDate() const;
    time_t getDueDate() const;

    // Setter
    void setTitle(std::string t);
    void setAuthor(std::string a);
    void setPublisher(std::string p);
    void setCategory(std::string c);

    // 业务方法
    void borrowBook(Reader* r, int borrowDays);  // 参数从 string 变成 Reader*
    void returnBook();
    int calculateOverdueDays();
    void displayInfo() const;
};

#endif

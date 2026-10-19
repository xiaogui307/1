#ifndef READER_H
#define READER_H

#include <string>
#include <vector>

class Book;   // 前置声明

// ==================== 基类：读者 ====================
class Reader {
protected:                       // protected：派生类可访问，外部不可
    std::string name;            // 姓名
    std::string userId;          // 学号/工号
    std::string department;      // 院系
    std::vector<Book*> borrowedBooks;   // 已借书籍

public:
    Reader(std::string n, std::string id, std::string d);

    // Getter
    std::string getName() const;
    std::string getUserId() const;
    std::string getDepartment() const;
    std::vector<Book*> getBorrowedBooks() const;
    int getBorrowedCount() const;

    // Setter
    void setName(std::string n);
    void setDepartment(std::string d);

    // ===== 纯虚函数：规则由派生类各自定义 =====
    virtual int getMaxBorrowLimit() const = 0;   // 最大借阅数
    virtual int getBorrowDays() const = 0;       // 借阅天数
    virtual void displayInfo() const = 0;        // 显示信息

    virtual ~Reader() {}   // 虚析构：通过基类指针 delete 派生类对象时正确释放

    // ===== 公共业务方法（所有读者一样）=====
    bool borrowBook(Book* b);
    bool returnBook(Book* b);
    bool hasBook(Book* b) const;
    bool canBorrowMore() const;
};

// ==================== 派生类：学生 ====================
class Student : public Reader {
public:
    Student(std::string n, std::string id, std::string d);

    int getMaxBorrowLimit() const override;   // 5 本
    int getBorrowDays() const override;       // 30 天
    void displayInfo() const override;
};

// ==================== 派生类：教师 ====================
class Teacher : public Reader {
public:
    Teacher(std::string n, std::string id, std::string d);

    int getMaxBorrowLimit() const override;   // 10 本
    int getBorrowDays() const override;       // 60 天
    void displayInfo() const override;
};

#endif

#include "book.h"
#include "reader.h"      // 只有实现文件里才需要 Reader 的完整定义
#include <iostream>

Book::Book(std::string bc, std::string i, std::string t,
    std::string a, std::string p, std::string c)
    : barcode(bc), isbn(i), title(t), author(a),
    publisher(p), category(c), isBorrowed(false),
    borrower(nullptr), borrowDate(0), dueDate(0) {
}

// Getter
std::string Book::getBarcode() const { return barcode; }
std::string Book::getIsbn() const { return isbn; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getPublisher() const { return publisher; }
std::string Book::getCategory() const { return category; }
bool Book::getIsBorrowed() const { return isBorrowed; }
Reader* Book::getBorrower() const { return borrower; }
time_t Book::getBorrowDate() const { return borrowDate; }
time_t Book::getDueDate() const { return dueDate; }

// Setter
void Book::setTitle(std::string t) { title = t; }
void Book::setAuthor(std::string a) { author = a; }
void Book::setPublisher(std::string p) { publisher = p; }
void Book::setCategory(std::string c) { category = c; }

// 被读者借走：记住"谁"借的，不再只记一个字符串ID
void Book::borrowBook(Reader* r, int borrowDays) {
    isBorrowed = true;
    borrower = r;
    borrowDate = time(nullptr);
    dueDate = borrowDate + borrowDays * 24 * 60 * 60;
}

// 还书
void Book::returnBook() {
    isBorrowed = false;
    borrower = nullptr;
    borrowDate = 0;
    dueDate = 0;
}

// 计算逾期天数
int Book::calculateOverdueDays() {
    if (!isBorrowed) return 0;
    time_t now = time(nullptr);
    if (now <= dueDate) return 0;
    return static_cast<int>(difftime(now, dueDate) / (24 * 60 * 60));
}

// 时间转字符串
std::string formatDate(time_t t) {
    if (t == 0) return "无";
    struct tm timeinfo;
    localtime_s(&timeinfo, &t);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d", &timeinfo);
    return std::string(buf);
}

// 显示图书信息
void Book::displayInfo() const {
    std::cout << "条码号: " << barcode << "  状态: "
        << (isBorrowed ? "已借出" : "可借阅") << std::endl;
    std::cout << "书名: " << title << "  作者: " << author << std::endl;
    std::cout << "ISBN: " << isbn << "  出版社: " << publisher
        << "  分类: " << category << std::endl;
    if (isBorrowed) {
        // 通过指针直接访问借阅者的姓名和学号
        std::cout << "  借阅人: " << borrower->getName()
            << " (" << borrower->getUserId() << ")"
            << "  借出日期: " << formatDate(borrowDate)
            << "  应还日期: " << formatDate(dueDate) << std::endl;
    }
}

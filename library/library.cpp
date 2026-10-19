#include "library.h"
#include <iostream>

// 罚款标准：每天每本 0.5 元
const double FINE_PER_DAY = 0.5;

// 析构函数：释放所有 new 出来的读者对象，防止内存泄漏
Library::~Library() {
    for (size_t i = 0; i < readers.size(); i++) {
        delete readers[i];
    }
}

// ==================== 图书管理 ====================

// 添加图书
void Library::addBook(const Book& book) {
    books.push_back(book);
    std::cout << "图书添加成功！" << std::endl;
}

// 按条码号查找
Book* Library::findBookByBarcode(std::string barcode) {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getBarcode() == barcode) {
            return &books[i];
        }
    }
    return nullptr;
}

// 按ISBN查找
Book* Library::findBookByIsbn(std::string isbn) {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getIsbn() == isbn) {
            return &books[i];
        }
    }
    return nullptr;
}

// 按书名关键字搜索
std::vector<Book*> Library::searchBooksByTitle(std::string keyword) {
    std::vector<Book*> result;
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getTitle().find(keyword) != std::string::npos) {
            result.push_back(&books[i]);
        }
    }
    return result;
}

// 修改图书信息（直接回车表示该项保持不变）
void Library::modifyBook(std::string barcode) {
    Book* book = findBookByBarcode(barcode);
    if (book == nullptr) {
        std::cout << "错误：未找到该图书！" << std::endl;
        return;
    }
    std::string input;
    std::cout << "当前书名: " << book->getTitle() << std::endl;
    std::cout << "请输入新书名（直接回车保持不变）: ";
    std::getline(std::cin, input);
    if (!input.empty()) book->setTitle(input);

    std::cout << "当前作者: " << book->getAuthor() << std::endl;
    std::cout << "请输入新作者（直接回车保持不变）: ";
    std::getline(std::cin, input);
    if (!input.empty()) book->setAuthor(input);

    std::cout << "当前出版社: " << book->getPublisher() << std::endl;
    std::cout << "请输入新出版社（直接回车保持不变）: ";
    std::getline(std::cin, input);
    if (!input.empty()) book->setPublisher(input);

    std::cout << "当前分类: " << book->getCategory() << std::endl;
    std::cout << "请输入新分类（直接回车保持不变）: ";
    std::getline(std::cin, input);
    if (!input.empty()) book->setCategory(input);

    std::cout << "图书信息修改完成！" << std::endl;
}

// 显示所有图书
void Library::showAllBooks() const {
    std::cout << "===== 所有图书 =====" << std::endl;
    if (books.empty()) {
        std::cout << "图书馆暂无图书。" << std::endl;
        return;
    }
    for (size_t i = 0; i < books.size(); i++) {
        std::cout << "--- 第 " << (i + 1) << " 本 ---" << std::endl;
        books[i].displayInfo();
    }
}

// ==================== 读者管理 ====================

// 注册读者（参数为指针，多态需要）
void Library::addReader(Reader* reader) {
    readers.push_back(reader);
    std::cout << "读者注册成功！" << std::endl;
}

// 按学号/工号查找读者
Reader* Library::findReaderById(std::string userId) {
    for (size_t i = 0; i < readers.size(); i++) {
        if (readers[i]->getUserId() == userId) {
            return readers[i];
        }
    }
    return nullptr;
}

// 修改读者信息（直接回车表示该项保持不变）
void Library::modifyReader(std::string userId) {
    Reader* reader = findReaderById(userId);
    if (reader == nullptr) {
        std::cout << "错误：未找到该读者！" << std::endl;
        return;
    }
    std::string input;
    std::cout << "当前姓名: " << reader->getName() << std::endl;
    std::cout << "请输入新姓名（直接回车保持不变）: ";
    std::getline(std::cin, input);
    if (!input.empty()) reader->setName(input);

    std::cout << "当前院系: " << reader->getDepartment() << std::endl;
    std::cout << "请输入新院系（直接回车保持不变）: ";
    std::getline(std::cin, input);
    if (!input.empty()) reader->setDepartment(input);

    std::cout << "读者信息修改完成！" << std::endl;
}

// 显示所有读者（-> 访问 + 多态 displayInfo）
void Library::showAllReaders() const {
    std::cout << "===== 所有读者 =====" << std::endl;
    if (readers.empty()) {
        std::cout << "暂无注册读者。" << std::endl;
        return;
    }
    for (size_t i = 0; i < readers.size(); i++) {
        std::cout << "--- 第 " << (i + 1) << " 位 ---" << std::endl;
        readers[i]->displayInfo();
    }
}

// ==================== 借书还书 ====================

// 借书：借期天数由派生类多态决定（学生30天，教师60天）
bool Library::borrowBook(std::string barcode, std::string userId) {
    Reader* reader = findReaderById(userId);
    if (reader == nullptr) {
        std::cout << "错误：未找到该读者！" << std::endl;
        return false;
    }
    Book* book = findBookByBarcode(barcode);
    if (book == nullptr) {
        std::cout << "错误：未找到该图书！" << std::endl;
        return false;
    }
    if (reader->borrowBook(book)) {
        std::cout << "借书成功！借阅期限 " << reader->getBorrowDays()
            << " 天。" << std::endl;
        return true;
    }
    return false;
}

// 还书
bool Library::returnBook(std::string barcode, std::string userId) {
    Reader* reader = findReaderById(userId);
    if (reader == nullptr) {
        std::cout << "错误：未找到该读者！" << std::endl;
        return false;
    }
    Book* book = findBookByBarcode(barcode);
    if (book == nullptr) {
        std::cout << "错误：未找到该图书！" << std::endl;
        return false;
    }
    if (!reader->hasBook(book)) {
        std::cout << "错误：该读者未借阅此书！" << std::endl;
        return false;
    }

    // 判断逾期并提示罚款
    int overdueDays = book->calculateOverdueDays();
    if (overdueDays > 0) {
        std::cout << "警告：该书已逾期 " << overdueDays << " 天！"
            << "应缴罚款: " << overdueDays * FINE_PER_DAY << " 元" << std::endl;
    }

    reader->returnBook(book);
    std::cout << "还书成功！" << std::endl;
    return true;
}

// ==================== 逾期罚款 ====================

// 显示所有逾期未还的书
void Library::showOverdueBooks() {
    std::cout << "===== 逾期未还图书 =====" << std::endl;
    bool found = false;
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getIsBorrowed()) {
            int days = books[i].calculateOverdueDays();
            if (days > 0) {
                found = true;
                std::cout << "书名: " << books[i].getTitle()
                    << "  借阅人: " << books[i].getBorrower()->getName()
                    << " (" << books[i].getBorrower()->getUserId() << ")"
                    << "  逾期: " << days << " 天"
                    << "  罚款: " << days * FINE_PER_DAY << " 元" << std::endl;
            }
        }
    }
    if (!found) {
        std::cout << "当前没有逾期未还的图书。" << std::endl;
    }
}

// 计算某本书的罚款金额
double Library::calculateFine(std::string barcode, std::string userId) {
    Book* book = findBookByBarcode(barcode);
    if (book == nullptr || !book->getIsBorrowed()) {
        return 0;
    }
    return book->calculateOverdueDays() * FINE_PER_DAY;
}

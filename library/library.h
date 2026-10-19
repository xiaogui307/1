#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include "book.h"
#include "reader.h"

class Library {
private:
    std::vector<Book> books;      // 所有图书
    std::vector<Reader*> readers;  // 所有读者

public:
    // ===== 图书管理 =====
    void addBook(const Book& book);
    Book* findBookByBarcode(std::string barcode);    // 按条码号查
    Book* findBookByIsbn(std::string isbn);
    std::vector<Book*> searchBooksByTitle(std::string keyword);  // 按书名搜
    void modifyBook(std::string barcode);            // 修改图书信息
    void showAllBooks() const;

    // ===== 读者管理 =====
    void addReader(Reader* reader);
    Reader* findReaderById(std::string userId);
    void modifyReader(std::string userId);           // 修改读者信息
    void showAllReaders() const;

    // ===== 借书还书 =====
    bool borrowBook(std::string barcode, std::string userId);
    bool returnBook(std::string barcode, std::string userId);

    // ===== 逾期罚款 =====
    void showOverdueBooks();
    double calculateFine(std::string barcode, std::string userId);

   //释放new出来的读者对象
    ~Library();
};

#endif

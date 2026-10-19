#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "library.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001);   // 设置控制台为 UTF-8 编码，正常显示中文
    Library lib;
    int choice;

    // 预置测试数据
    lib.addBook(Book("B001", "9787111211266", "C++ Primer",
        "Stanley", "机械工业出版社", "编程"));
    lib.addBook(Book("B002", "9780439708180", "哈利波特",
        "J.K.罗琳", "人民文学出版社", "小说"));
    lib.addBook(Book("B003", "9787111397656", "数据结构",
        "Clifford", "清华大学出版社", "计算机"));

    // 继承+多态：学生和教师都是 Reader，但行为不同
    lib.addReader(new Student("张三", "2024001", "计算机学院"));
    lib.addReader(new Teacher("李教授", "T001", "软件学院"));

    cout << endl;

    do {
        cout << "========== 图书管理系统 ==========" << endl;
        cout << "1.  添加新图书" << endl;
        cout << "2.  显示所有图书" << endl;
        cout << "3.  按书名搜索图书" << endl;
        cout << "4.  修改图书信息" << endl;
        cout << "5.  注册新读者" << endl;
        cout << "6.  显示所有读者" << endl;
        cout << "7.  修改读者信息" << endl;
        cout << "8.  借书" << endl;
        cout << "9.  还书" << endl;
        cout << "10. 查看逾期图书" << endl;
        cout << "0.  退出系统" << endl;
        cout << "===================================" << endl;
        cout << "请输入您的选择: ";
        cin >> choice;
        cin.ignore();   // 吃掉换行符，避免影响后面的 getline
        cout << endl;

        if (choice == 1) {
            string bc, isbn, title, author, pub, cat;
            cout << "请输入图书条码号: ";
            getline(cin, bc);
            cout << "请输入ISBN: ";
            getline(cin, isbn);
            cout << "请输入书名: ";
            getline(cin, title);
            cout << "请输入作者: ";
            getline(cin, author);
            cout << "请输入出版社: ";
            getline(cin, pub);
            cout << "请输入分类: ";
            getline(cin, cat);
            lib.addBook(Book(bc, isbn, title, author, pub, cat));
            cout << endl;

        }
        else if (choice == 2) {
            lib.showAllBooks();
            cout << endl;

        }
        else if (choice == 3) {
            string keyword;
            cout << "请输入书名关键字: ";
            getline(cin, keyword);
            vector<Book*> results = lib.searchBooksByTitle(keyword);
            if (results.empty()) {
                cout << "未找到相关图书。" << endl;
            }
            else {
                cout << "找到 " << results.size() << " 本相关图书：" << endl;
                for (size_t i = 0; i < results.size(); i++) {
                    cout << "--- 第 " << (i + 1) << " 本 ---" << endl;
                    results[i]->displayInfo();
                }
            }
            cout << endl;

        }
        else if (choice == 4) {
            string bc;
            cout << "请输入要修改的图书条码号: ";
            getline(cin, bc);
            lib.modifyBook(bc);
            cout << endl;

        }
        else if (choice == 5) {
            string name, id, type, dept;
            cout << "请输入姓名: ";
            getline(cin, name);
            cout << "请输入学号/工号: ";
            getline(cin, id);
            cout << "请输入类型(学生/教师): ";
            getline(cin, type);
            cout << "请输入院系: ";
            getline(cin, dept);

            if (type == "学生") {
                lib.addReader(new Student(name, id, dept));
                cout << "注册成功！学生限借 5 本，借期 30 天。" << endl;
            }
            else {
                lib.addReader(new Teacher(name, id, dept));
                cout << "注册成功！教师限借 10 本，借期 60 天。" << endl;
            }
            cout << endl;

        }
        else if (choice == 6) {
            lib.showAllReaders();
            cout << endl;

        }
        else if (choice == 7) {
            string id;
            cout << "请输入要修改的读者学号/工号: ";
            getline(cin, id);
            lib.modifyReader(id);
            cout << endl;

        }
        else if (choice == 8) {
            string bc, userId;
            cout << "请输入图书条码号: ";
            getline(cin, bc);
            cout << "请输入读者学号/工号: ";
            getline(cin, userId);
            lib.borrowBook(bc, userId);
            cout << endl;

        }
        else if (choice == 9) {
            string bc, userId;
            cout << "请输入图书条码号: ";
            getline(cin, bc);
            cout << "请输入读者学号/工号: ";
            getline(cin, userId);
            lib.returnBook(bc, userId);
            cout << endl;

        }
        else if (choice == 10) {
            lib.showOverdueBooks();
            cout << endl;

        }
        else if (choice == 0) {
            cout << "感谢使用，再见！" << endl;

        }
        else {
            cout << "输入无效，请重新选择！" << endl << endl;
        }

    } while (choice != 0);

    return 0;   // main 结束时 Library 析构函数自动释放所有读者内存
}

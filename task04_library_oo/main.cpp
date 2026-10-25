#include "Libary.h"
#include "LibaryItem.h"
#include "TextStorage.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <memory>
#include <iomanip>
#include <string>
using std::string;
using std::cout;
using std::cin;

TextStorage sto;
Libary lib(sto);

void madd() {
    cout << "cin id, name, kind" << '\n';
    string id, name, kind;
    bool status = false;
    cin >> id >> name >> kind;
    std::unique_ptr<LibaryItem> item;
    if(kind == "Book"){
        Book bk(id, name, status, kind);
        item = std::make_unique<Book>(bk);
    }
    else if(kind == "Magazine"){
        Magazine ma(id, name, status, kind);
        item = std::make_unique<Magazine>(ma);
    }
    else{
        cout << "unknown kind \n";
        return;
    }
    lib.add(item);
}

void mdelete() {
    cout << "cin id, name, kind" << '\n';
    string id, name, kind;
    bool status = false;
    cin >> id >> name >> kind;
    std::unique_ptr<LibaryItem> item;
    if(kind == "Book"){
        Book bk(id, name, status, kind);
        item = std::make_unique<Book>(bk);
    }
    else if(kind == "Magazine"){
        Magazine ma(id, name, status, kind);
        item = std::make_unique<Magazine>(ma);
    }
    else{
        cout << "unknown kind \n";
        return;
    }
    lib.detele(item);
}

void mset() {
    cout << "old message: " << '\n';
    mdelete();
    cout << "new message: " << '\n';
    madd();
}

void mfind() {
    cout << "cin the id" << '\n';
    string id;
    cin >> id;
    lib.find(id);
}

void mborrow() {
    cout << "cin id, name, kind" << '\n';
    string id, name, kind;
    bool status = false;
    cin >> id >> name >> kind;
    std::unique_ptr<LibaryItem> item;
    if(kind == "Book"){
        Book bk(id, name, status, kind);
        item = std::make_unique<Book>(bk);
    }
    else if(kind == "Magazine"){
        Magazine ma(id, name, status, kind);
        item = std::make_unique<Magazine>(ma);
    }
    else{
        cout << "unknown kind \n";
        return;
    }
    lib.borrow(item);
}

void mreturn() {
    cout << "cin id, name, kind" << '\n';
    string id, name, kind;
    bool status = false;
    cin >> id >> name >> kind;
    std::unique_ptr<LibaryItem> item;
    if(kind == "Book"){
        Book bk(id, name, status, kind);
        item = std::make_unique<Book>(bk);
    }
    else if(kind == "Magazine"){
        Magazine ma(id, name, status, kind);
        item = std::make_unique<Magazine>(ma);
    }
    else{
        cout << "unknown kind \n";
        return;
    }
    lib.returnitem(item);
}

void mlist() {
    lib.list();
}

void msave() {
    sto.save(lib.libstream());
}

void mload() {
    lib.loadfile();
}

void showmain(){
    while(1){
        cout << "=======================" << '\n';
        cout << "[1] add a item" << '\n';
        cout << "[2] delete a item " << '\n';
        cout << "[3] set a item" << '\n';
        cout << "[4] find a item " << '\n';
        cout << "[5] borrow a item " << '\n';
        cout << "[6] return a item " << '\n';
        cout << "[7] list all items " << '\n';
        cout << "[8] save the items " << '\n';
        cout << "[9] load the tiems " << '\n';
        cout << "[10] sort by name" << '\n';
        cout << "[11] show total" << '\n';
        cout << "[0] exit " << '\n';
        cout << '\n';
        cout << "please cin a number" << '\n';
        cout << "=======================" << '\n';
        int choice;
        cin >> choice;
        switch(choice){
            case 1: madd(); break;
            case 2: mdelete(); break;
            case 3: mset(); break;
            case 4: mfind(); break;
            case 5: mborrow(); break;
            case 6: mreturn(); break;
            case 7: mlist(); break;
            case 8: msave(); break;
            case 9: mload(); break;
            case 10: lib.sortwithname(); break;
            case 11: lib.showtotal(); break;
            case 0:
                cout << "byebye" << '\n';
                return;
            default:
                cout << "use the right number" << '\n';
                break;
        }
    }
    return;
}

int main(){
    using namespace std;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    try{
        showmain();
    }catch(const exception& e){
        cout << "error: " << e.what() << '\n';
    }
    

    return;
}
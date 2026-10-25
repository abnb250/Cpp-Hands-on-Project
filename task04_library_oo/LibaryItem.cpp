#include "LibaryItem.h"

void Book::Show() const {
    using namespace std;
    cout << "=======================" << '\n';
    cout << "kind  : " << kind_ << '\n';
    cout << "name  : " << name << '\n';
    cout << "id    : " << id << '\n';
    cout << "status: " << static_cast<int>(status) << '\n';
    cout << "=======================" << '\n';
    return;
}

bool Book::Check() const {
    return status;
}

string Book::kind() const {
    return kind_;
}

string Book::getid() const{
    return id;
}

string Book::getname() const{
    return name;
}

void Book::setstatus(){
    status = status ^ 1;
}

void Magazine::Show() const {
    using namespace std;
    cout << "=======================" << '\n';
    cout << "kind  : " << kind_ << '\n';
    cout << "name  : " << name << '\n';
    cout << "id    : " << id << '\n';
    cout << "status: " << status << '\n';
    cout << "=======================" << '\n';
    return;
}

bool Magazine::Check() const {
    return status;
}

string Magazine::kind() const {
    return kind_;
}

string Magazine::getid() const{
    return id;
}

string Magazine::getname() const{
    return name;
}

void Magazine::setstatus(){
    status = status ^ 1;
}
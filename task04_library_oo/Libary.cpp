#include "Libary.h"
#include "LibaryItem.h"
using std::cout;
using std::cin;

void Libary::add(std::unique_ptr<LibaryItem>& item) {
    for (const auto& x : items) {
        if (x->getid() == item->getid()) {
            throw std::invalid_argument("duplicate id: " + item->getid());
        }
    }
    items.push_back(std::move(item));
}

void Libary::detele(std::unique_ptr<LibaryItem>& item) {
    int index = 0;
    for(auto &x : items){
        if(x->getname() == item->getname() 
        && x->getid() == item->getid()
        && x->kind() == item->kind()){
            items.erase(items.begin() + index);
            return;
        }
        index++;
    }
    throw std::out_of_range("no find item to delete");
    return ;
}

void Libary::find(std::string ids) {
    int index = 0;
    for(auto &x : items){
        if(ids == x->getid()){
            x->Show();
            return;
        }
        index++;
    }
    throw std::out_of_range("no result");
    return ;
}

void Libary::list() {
    for(auto &x : items){
        x->Show();
    }
    return;
}

void Libary::borrow(std::unique_ptr<LibaryItem>& item) {
    for(auto &x : items){
        if(x->getname() == item->getname() 
        && x->getid() == item->getid()
        && x->kind() == item->kind()){
            if(x->Check() == true ){
                cout << "borrowed" << '\n';
                return;
            }
            x->setstatus();
            return;
        }
    }
    throw std::out_of_range("no find item to borrow");
    return ;
}

void Libary::returnitem(std::unique_ptr<LibaryItem>& item) {
    for(auto &x : items){
        if(x->getname() == item->getname() 
        && x->getid() == item->getid()
        && x->kind() == item->kind()){
            if(x->Check() == false ){
                cout << "not borrowed" << '\n';
                return;
            }
            x->setstatus();
            return;
        }
    }
    throw std::out_of_range("no find item to return");
    return ;
}

void Libary::sortwithname() {
    std::sort(items.begin(), items.end(),[](std::unique_ptr<LibaryItem>& a, std::unique_ptr<LibaryItem>& b){
        return a->getname() < b->getname();
    });
    return;
}

void Libary::showtotal() {
    int cnt = 0, b = 0, nob = 0;
    for(auto &x : items){
        cnt++;
        if(x->Check()) b++;
        else nob++;
    }
    cout << "===================" << '\n';
    cout << "total    : " << cnt << '\n';
    cout << "borrowed : " << b << '\n';
    cout << "haved    : " << nob << '\n';
    cout << "===================" << '\n';

    return;
}

std::vector<std::unique_ptr<LibaryItem>>& Libary::libstream() {
    return items;
}

void Libary::loadfile() {
    items = sto.load();
}
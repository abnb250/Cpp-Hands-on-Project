#ifndef LIBARY_H
#define LIBARY_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include "LibaryItem.h"

class Storage{
public:
    virtual ~Storage() = default;
    virtual void save(std::vector<std::unique_ptr<LibaryItem>>& items) = 0;
    virtual std::vector<std::unique_ptr<LibaryItem>> load() = 0;
};

class Libary{
private:
    std::vector<std::unique_ptr<LibaryItem>> items;
    Storage& sto;
public:
    explicit Libary(Storage& stor) : sto(stor) {}
    void add(std::unique_ptr<LibaryItem>& item);
    void detele(std::unique_ptr<LibaryItem>& item);
    void find(std::string ids);
    void list();
    void borrow(std::unique_ptr<LibaryItem>& item);
    void returnitem(std::unique_ptr<LibaryItem>& item);
    void sortwithname();
    void showtotal();
    std::vector<std::unique_ptr<LibaryItem>>& libstream();
    void loadfile();

};

#endif
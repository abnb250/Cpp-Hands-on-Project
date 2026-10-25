#ifndef LIBARYITEM_H
#define LIBARYITEM_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include <fstream>
using std::string;

class LibaryItem{
protected:
    string id;
    string name;
    bool status;
public:
    explicit LibaryItem() : id("unknown"), name("unknown"), status(false) {}
    explicit LibaryItem(string i, string n, bool s) : id(i), name(n), status(s) {}
    virtual ~LibaryItem() {}
    virtual void Show() const = 0;
    virtual bool Check() const = 0;
    virtual string kind() const = 0;
    virtual string getname() const = 0;
    virtual string getid() const = 0;
    virtual void setstatus() = 0;
};

class Book : public LibaryItem{
protected:
    string kind_;
public:
    explicit Book() : LibaryItem(), kind_("unknown") {}
    explicit Book(string i, string n, bool s, string k) : LibaryItem(i, n, s), kind_(k) {}
    void Show() const override;
    bool Check() const override;
    string kind() const override;
    string getname() const override;
    string getid() const override;
    void setstatus() override;
};

class Magazine : public LibaryItem{
protected:
    string kind_;
public:
    explicit Magazine() : LibaryItem(), kind_("unknown") {}
    explicit Magazine(string i, string n, bool s, string k) : LibaryItem(i, n, s), kind_(k) {}
    void Show() const override;
    bool Check() const override;
    string kind() const override;
    string getname() const override;
    string getid() const override;
    void setstatus() override;
};

#endif
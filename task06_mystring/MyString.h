#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <stdexcept>

class MyString{
private:
    char* data_;
    std::size_t size_;
public:
    MyString() : data_(new char[1]{'\0'}), size_(0) {}
    MyString(const char* s);
    MyString(const char* s, int len);
    ~MyString();

    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    MyString(MyString&& other) noexcept;
    MyString& operator=(MyString&& other) noexcept;

    void Swap(MyString& other) noexcept;
    std::size_t size() const;
    bool empty() const;
    const char* c_str() const noexcept;
    const char* data() const noexcept;

    const char& operator[](std::size_t index) const;
    char& operator[](std::size_t index);
    char at(std::size_t index) const;
    char& at(std::size_t index);

    MyString& operator+=(const char* other) ;
    MyString& operator+=(const MyString& other);
    MyString operator+(const char* other) const;
    MyString operator+(const MyString& other) const;

    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    
    void clear();
};

#endif
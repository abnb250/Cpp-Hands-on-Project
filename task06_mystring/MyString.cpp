#include "MyString.h"
#include <utility>
#include <cstring>

MyString::MyString(const char *s) {
    if(s == nullptr){
        data_ = new char[1]{'\0'};
        size_ = 0;
        return;
    }
    std::size_t len = std::strlen(s);
    char* tmp = new char[len+1];
    for(std::size_t i = 0; i < len; i++){
        tmp[i] = s[i];
    }
    tmp[len] = '\0';
    data_ = tmp;
    size_ = len;
}

MyString::MyString(const char *s, int len) {
    if(len < 0 ) throw std::invalid_argument("negative length");
    if(!s && len > 0) throw std::invalid_argument("nullptr pointer");
    std::size_t l = static_cast<std::size_t>(len);
    char * tmp = new char[l+1];
    for(std::size_t i = 0; i < l; i++){
        tmp[i] = s[i];
    }
    tmp[l] = '\0';
    data_ = tmp;
    size_ = l;
}

MyString::~MyString() {
    delete[] data_;
}

MyString::MyString(const MyString &other) : 
    data_(nullptr), 
    size_(other.size_) {
    char* tmp = new char[size_ +1];
    for(std::size_t i = 0; i < size_; i++){
        tmp[i] = other.data_[i];
    }
    tmp[size_] = '\0';
    data_ = tmp;
}

MyString& MyString::operator=(const MyString &other) {
    if(this == &other){
        return *this;
    }
    MyString tmp(other);
    Swap(tmp);
    return *this;
}

MyString::MyString(MyString &&other) noexcept
    : data_(other.data_), 
    size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
    }

MyString& MyString::operator=(MyString &&other) noexcept {
    if(this == &other){
        return *this;
    }
    delete[] data_;
    size_ = other.size_;
    data_ = other.data_;
    other.data_ = nullptr;
    other.size_ = 0;
    return *this;
}

void MyString::Swap(MyString& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
}

std::size_t MyString::size() const {
    return size_;
}

bool MyString::empty() const {
    return size_ == 0;
}

const char * MyString::c_str() const noexcept{
    static const char emp[1]{'\0'};
    return data_ ? data_ : emp;
}

const char * MyString::data() const noexcept {
    return c_str();
}

const char& MyString::operator[](std::size_t index) const {
    if(index >= size_ ){
        throw std::out_of_range("out of range");
    }
    return data_[index];
}

char& MyString::operator[](std::size_t index) {
    if(index >= size_ ){
        throw std::out_of_range("out of range");
    }
    return data_[index];
}

char MyString::at(std::size_t index) const {
    if(index >= size_){
        throw std::out_of_range("out of range");
    }
    return data_[index];
}

char& MyString::at(std::size_t index){
    if(index >= size_ ){
        throw std::out_of_range("out of range");
    }
    return data_[index];
}

MyString& MyString::operator+=(const char *other) {
    if(other == nullptr) return *this;
    std::size_t len = std::strlen(other);
    char* tmp = new char[size_+len + 1];
    std::strcpy(tmp, data_ ? data_ : "");
    std::strcpy(tmp + size_, other);
    delete[] data_;
    data_ = tmp;
    size_ += len;
    return *this;
}

MyString& MyString::operator+=(const MyString &other) {
    char* tmp = new char[size_ + other.size_ + 1];
    std::strcpy(tmp, data_ ? data_ : "");
    std::strcpy(tmp + size_, other.data_ ? other.data_ : "");
    delete[] data_;
    data_ = tmp;
    size_ += other.size_;
    return *this;
}

MyString MyString::operator+(const char *other) const {
    MyString nt(*this);
    nt += other;
    return nt;
}

MyString MyString::operator+(const MyString &other) const {
    MyString nt(*this);
    nt += other;
    return nt;
}

bool MyString::operator==(const MyString &other) const {
    const char* a = data_ ? data_ : "";
    const char* b = other.data_ ? other.data_ : "";
    return std::strcmp(a, b) == 0;
}

bool MyString::operator!=(const MyString &other) const {
    return !(*this == other);
}

bool MyString::operator<(const MyString &other) const {
    const char* a = data_ ? data_ : "";
    const char* b = other.data_ ? other.data_ : "";
    return std::strcmp(a, b) < 0;
}

void MyString::clear() {
    size_ = 0;
    if(data_){
        data_[0] = '\0';
    }
}
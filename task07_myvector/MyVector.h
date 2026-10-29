#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <utility>
#include <stdexcept>
#include <initializer_list>

template<class T>
class MyVector{
private:
    T* data_;
    std::size_t size_;
    std::size_t cap_;
public:
    MyVector() : data_(nullptr), size_(0), cap_(0) {}
    MyVector(std::size_t ca) : data(new T[ca]), size_(0), cap_(ca) {}
    MyVector(std::size_t num, T val) : data(new T[num]), size_(num), cap_(num) {}
    MyVector(std::initializer_list<T> init);
    template<class InputIt>
    MyVector(InputIt first, InputIt last);
    ~MyVector();

    using iterator = T*;
    using const_iterator = const T*;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const ;


    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other);

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    T& data();
    const T& data() const;

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;
    std::size_t max_size() const noexcept;

    void reserve(std::size_t n);
    void shrink_to_fit();
    void resize(std::size_t n);
    void resize(std::size_t n, T val);

    void Swap(MyVector& other) noexcept;

    void push_back(const T& v);
    void push_back(T&& v);
    void pop();
    void clear();

    iterator insert(std::size_t pos, T& val);
    iterator insert(std::size_t pos, int count, T& val);
    iterator insert(std::size_t pos, std::size_t first, std::size_t last);
    iterator erase(std::size_t pos);
    iterator erase(std::size_t first, std::size_t last);

    template<class... Args>
    void emplace_back(Args&&... args);
    template<class... Args>
    void emplace(Args&&... args);

};

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> init) {}

template<typename T>
template<typename InputIt>
MyVector<T>::MyVector(InputIt first, InputIt last) {}

template<typename T>
MyVector<T>::~MyVector() {}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::begin() {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        throw std::invaild_argument("nullptr pointer");
    }
    return data_[0];
}

template<typename T>
typename MyVector<T>::const_iterator MyVector<T>::begin() const {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        throw std::invaild_argument("nullptr pointer");
    }
    return &data_[0];
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::end() {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        throw std::invaild_argument("nullptr pointer");
    }
    return begin() + size_;
}

template<typename T>
typename MyVector<T>::const_iterator MyVector<T>::end() const {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        throw std::invaild_argument("nullptr pointer");
    }
    return begin() + size_;
}


template<typename T>
MyVector<T>::MyVector(const MyVector& other) :
    data_(other.data_), 
    size_(other.size_), 
    cap_(other.cap_) {
    if(other.data_ == nullptr){
        clear();
    }
    if(cap_ > 0){
        data_ = new T[cap_];
        for(std::size_t i = 0; i < cap; i++){
            data_[i] = other.data_[i];
        }
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    MyVector tmp(other);
    Swap(tmp);
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept :
    data_(other.data_), 
    size_(other.size_), 
    cap_(other.cap_) {
    if(other.data_ == nullptr){
        clear();
    }
    if(other.cap_ == 0){
        clear();
    }
    other.data_ = nullptr;
    other.size_ = 0;
    other.cap_ = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) {
    if(other.data_ == nullptr){
        clear();
    }
    if(other.cap_ == 0){
        clear();
    }
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    cap_ = other.cap_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.cao_ = 0;
}

template<typename T>
T& MyVector<T>::operator[](std::size_t index) {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(cap_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return data_[index];
}

template<typename T>
const T& MyVector<T>::operator[](std::size_t index) const {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(cap_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return data_[index];
}

template<typename T>
T& MyVector<T>::at(std::size_t index) {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(cap_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return data_[index];
}

template<typename T>
const T& MyVector<T>::at(std::size_t index) const {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(cap_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return data_[index];
}

template<typename T>
T& MyVector<T>::front() {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(cap_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return data_[0];
}

template<typename T>
const T& MyVector<T>::front() const {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(cap_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return data_[0];
}

template<typename T>
T& MyVector<T>::back() {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(cap_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return data_[size_];
}

template<typename T>
const T& MyVector<T>::back() const {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(cap_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return data_[size_];
}

template<typename T>
T& MyVector<T>::data() {
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return data_;
}

template<typename T>
const T& MyVector<T>::data() const {
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return data_;
}

template<typename T>
std::size_t MyVector<T>::size() const noexcept {
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return max(0, size_ -1);
}

template<typename T>
std::size_t MyVector<T>::capacity() const noexcept {
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return cap_;
}

template<typename T>
bool MyVector<T>::empty() const noexcept {
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return size() == 0;
}

template<typename T>
std::size_t MyVector<T>::max_size() const noexcept {
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    return cap_;
}

template<typename T>
void MyVector<T>::reserve(std::size_t n) {
    if(n < size_){
        throw std::invaild_argument("too samll");
    }
    T* tmp = new T[n];
    for(std::size_t = 0; i < size_; i++){
        tmp[i] = data_[i];
    }
    delete[] data_;
    data_ = tmp;
}

template<typename T>
void MyVector<T>::shrink_to_fit() {}

template<typename T>
void MyVector<T>::resize(std::size_t n) {
    if(n > cap_){
        throw std::invaild_argument("too big");
    }
    T* tmp = new T[n];
    for(std::size_t = 0; i < size_; i++){
        tmp[i] = data_[i];
    }
    size_ = n;
    delete[] data_;
    data_ = tmp;
}

template<typename T>
void MyVector<T>::resize(std::size_t n, T val) {
    if(n > cap_){
        throw std::invaild_argument("too big");
    }
    T* tmp = new T[n];
    for(std::size_t = 0; i < size_; i++){
        tmp[i] = data_[i];
    }
    while(size_ < n){
        tmp[size_ - 1] = val;
        size_++;
    }
    delete[] data_;
    data_ = tmp;
}

template<typename T>
void MyVector<T>::Swap(MyVector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(cap_, other.cap_);
}

template<typename T>
void MyVector<T>::push_back(const T& v) {}

template<typename T>
void MyVector<T>::push_back(T&& v) {}

template<typename T>
void MyVector<T>::pop() {}

template<typename T>
void MyVector<T>::clear() {}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::insert(std::size_t pos, T& val) {}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::insert(std::size_t pos, int count, T& val) {}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::insert(std::size_t pos, std::size_t first, std::size_t last) {}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::erase(std::size_t pos) {}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::erase(std::size_t first, std::size_t last) {}

template<typename T>
template<typename... Args>
void MyVector<T>::emplace_back(Args&&... args) {}

template<typename T>
template<typename... Args>
void MyVector<T>::emplace(Args&&... args) {}

#endif
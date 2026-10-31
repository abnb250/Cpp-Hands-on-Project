#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <utility>
#include <stdexcept>
#include <initializer_list>

template<class T>
class MyVector{
private:
    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t cap_ = 0;
    static T* alloc(std::size_t n){
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    static void dealloc(T* p) noexcept{
        ::operator delete(p);
    }
    void free_all() noexcept {
        for(std::size_t i = 0; i < size_; i++){
            data_[i].~T();
        }
        dealloc(data_);
        data_ = nullptr;
        size_ = 0;
        cap_ = 0;
    }
    void grow(std::size_t newcap);

public:
    MyVector() noexcept : data_(nullptr), size_(0), cap_(0) {}
    MyVector(std::size_t ca) : data_(ca ? alloc(ca) : nullptr), size_(0), cap_(ca) {}
    MyVector(std::size_t num, const T& val) : data_(num ? alloc(num) : nullptr), size_(0), cap_(num) {
        try{
            for(; size_ < cap_; size_++){
                new(data_ + size_) T(val);
            }
        }catch(...){
            free_all();
            throw;
        }
    }
    MyVector(std::initializer_list<T> init);
    template<class InputIt>
    MyVector(InputIt first, InputIt last);
    ~MyVector() noexcept;

    using iterator = T*;
    using const_iterator = const T*;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;


    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    T* data();
    const T* data() const;

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;
    std::size_t max_size() const noexcept;

    void reserve(std::size_t n);
    void shrink_to_fit();
    void resize(std::size_t n);
    void resize(std::size_t n, const T& val);

    void Swap(MyVector& other) noexcept;

    void push_back(const T& v);
    void push_back(T&& v);
    void pop_back();
    void clear() noexcept;

    iterator insert(std::size_t pos, const T& val);
    iterator insert(std::size_t pos, T&& val);
    iterator insert(std::size_t pos, std::size_t count, const T& val);
    template<class InputIt>
    iterator insert(std::size_t pos, InputIt first, InputIt last);
    iterator erase(std::size_t pos);
    iterator erase(std::size_t first, std::size_t last);

    template<class... Args>
    void emplace_back(Args&&... args);
    template<class... Args>
    iterator emplace(std::size_t pos, Args&&... args);

};

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> init) {
    try{
        reserve(init.size());
        for(auto v : init){
            emplace_back(v);
        }
    }catch(...){
        for(std::size_t i = 0; i < size_; i++){
            data_[i].~T();
        }
        ::operator delete(data_);
        data_ = nullptr;
        size_ = 0;
        cap_ = 0;
        throw;
    }
}

template<typename T>
template<typename InputIt>
MyVector<T>::MyVector(InputIt first, InputIt last) {
    try{
        for(; first != last; first++){
            emplace_back(*first);
        }
    }catch(...){
        for(std::size_t i = 0; i < size_; i++){
            data_[i].~T();
        }
        ::operator delete(data_);
        data_ = nullptr;
        size_ = 0;
        cap_ = 0;
        throw;
    }
}

template<typename T>
MyVector<T>::~MyVector() noexcept {
    free_all();
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::begin() noexcept{
    return data_;
}

template<typename T>
typename MyVector<T>::const_iterator MyVector<T>::begin() const noexcept{
    return data_;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::end() noexcept{
    return data_ + size_;
}

template<typename T>
typename MyVector<T>::const_iterator MyVector<T>::end() const noexcept{
    return data_ + size_;
}

template<typename T>
typename MyVector<T>::const_iterator MyVector<T>::cbegin() const noexcept{
    return data_;
}

template<typename T>
typename MyVector<T>::const_iterator MyVector<T>::cend() const noexcept{
    return data_ + size_;
}


template<typename T>
MyVector<T>::MyVector(const MyVector& other) :
    data_(nullptr), 
    size_(0), 
    cap_(0) {
    if(other.size_ == 0){
        return;
    }
    data_ = alloc(other.cap_);
    cap_ = other.cap_;
    try{
        for(; size_ < other.size_; size_++){
            new(data_ + size_) T(other.data_[size_]);
        }
    }catch(...){    
        free_all();
        throw;
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if(this == &other) return *this;
    MyVector tmp(other);
    Swap(tmp);
    return *this;
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept :
    data_(other.data_), 
    size_(other.size_), 
    cap_(other.cap_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.cap_ = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept{
    if(this == &other) return *this;
    free_all();
    data_ = other.data_;
    size_ = other.size_;
    cap_ = other.cap_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.cap_ = 0;
    return *this;
}

template<typename T>
void MyVector<T>::grow(std::size_t newcap){
    if(newcap <= cap_) return;

    T* newdata = alloc(newcap);
    std::size_t constructed = 0;
    try{
        for(; constructed < size_; constructed++){
            new(newdata + constructed) T(std::move_if_noexcept(data_[constructed]));
        }
    }catch(...){
        for(std::size_t i = 0; i < constructed; i++){
            newdata[i].~T();
        }
        dealloc(newdata);
        throw;
    }
    for(std::size_t i = 0; i < size_; i++) data_[i].~T();
    dealloc(data_);
    data_ = newdata;
    cap_ = newcap;
}

template<typename T>
T& MyVector<T>::operator[](std::size_t index) {
    return data_[index];
}

template<typename T>
const T& MyVector<T>::operator[](std::size_t index) const {
    return data_[index];
}

template<typename T>
T& MyVector<T>::at(std::size_t index) {
    if(index >= size_) throw std::out_of_range("at");
    return data_[index];
}

template<typename T>
const T& MyVector<T>::at(std::size_t index) const {
    if(index >= size_) throw std::out_of_range("at");
    return data_[index];
}

template<typename T>
T& MyVector<T>::front() {
    return data_[0];
}

template<typename T>
const T& MyVector<T>::front() const {
    return data_[0];
}

template<typename T>
T& MyVector<T>::back() {
    return data_[size_ - 1];
}

template<typename T>
const T& MyVector<T>::back() const {
    return data_[size_ - 1];
}

template<typename T>
T* MyVector<T>::data() {
    return data_;
}

template<typename T>
const T* MyVector<T>::data() const {
    return data_;
}

template<typename T>
std::size_t MyVector<T>::size() const noexcept {
    return size_;
}

template<typename T>
std::size_t MyVector<T>::capacity() const noexcept {
    return cap_;
}

template<typename T>
bool MyVector<T>::empty() const noexcept {
    return size_ == 0;
}

template<typename T>
std::size_t MyVector<T>::max_size() const noexcept { //理论最大容量
    return static_cast<std::size_t> (-1) / sizeof(T);
}

template<typename T>
void MyVector<T>::reserve(std::size_t n) {
    if(n <= cap_) return;
    if(n > max_size()) throw std::length_error("reserve");
    grow(n);
}

template<typename T>
void MyVector<T>::shrink_to_fit() {
    if(size_ == cap_) return;
    if(size_ == 0){
        free_all();
        return;
    }

    T* newdata = alloc(size_);
    std::size_t constructed = 0;
    try{
        for(; constructed < size_; constructed++){
            new(newdata + constructed) T (std::move_if_noexcept(data_[constructed]));
        }
    }catch(...){
        for(std::size_t i = 0; i < constructed; i++){
            newdata[i].~T();
        }
        dealloc(newdata);
        throw;
    }
    for(std::size_t i = 0; i < size_; i++){
        data_[i].~T();
    }
    dealloc(data_);
    data_ = newdata;
    cap_ = size_;
}

template<typename T>
void MyVector<T>::resize(std::size_t n) {
    if(n < size_){
        for(std::size_t i = n; i < size_; i++){
            data_[i].~T();
        }
        size_ = n;
    }
    else if(n > size_){
        if(n > cap_) grow(std::max(cap_*2, n));
        for(; size_ < n; size_++){
            new(data_ + size_) T();
        }
    }
}

template<typename T>
void MyVector<T>::resize(std::size_t n, const T& val) {
    if(n < size_){
        for(std::size_t i = n; i < size_; i++){
            data_[i].~T();
        }
        size_ = n;
    }
    else if(n > size_){
        if(n > cap_) grow(std::max(cap_*2, n));
        for(; size_ < n; size_++){
            new(data_ + size_) T(val);
        }
    }
}

template<typename T>
void MyVector<T>::Swap(MyVector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(cap_, other.cap_);
}

template<typename T>
void MyVector<T>::push_back(const T& v) {
    if(size_ == cap_) grow(cap_ == 0 ? 10 : cap_ * 2);
    new(data_ + size_) T (v);
    size_++;
}

template<typename T>
void MyVector<T>::push_back(T&& v) {
    if(cap_ == size_) grow(cap_ == 0 ? 10 : cap_*2);
    new(data_ + size_) T (std::move(v));
    size_++;
}

template<typename T>
void MyVector<T>::pop_back() {
    if(size_ == 0) throw std::out_of_range("pop_back");
    size_--;
    data_[size_].~T();
}

template<typename T>
void MyVector<T>::clear() noexcept {
    for(std::size_t i = 0; i < size_; i++){
        data_[i].~T();
    }
    size_ = 0;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::insert(std::size_t pos, const T& val) {
    return emplace(pos, val);
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::insert(std::size_t pos, T&& val) {
    return emplace(pos, std::move(val));
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::insert(std::size_t pos, std::size_t count, const T& val) {
    if(pos > size_) throw std::out_of_range("insert");
    if(count == 0) return data_ + pos;

    std::size_t newcap = std::max(cap_ * 2, size_ + count);
    T* newdata = alloc(newcap);
    std::size_t constructed = 0;
    try{
        for(; constructed < pos; constructed++){
            new(newdata + constructed) T(std::move_if_noexcept(data_[constructed]));
        }
        for(std::size_t k = 0; k < count; k++, constructed++){
            new(newdata + constructed) T(val);
        }
        for(std::size_t k = pos; k < size_; k++, constructed++){
            new(newdata + constructed) T(std::move_if_noexcept(data_[k]));
        }
    }catch(...){
        for(std::size_t i = 0; i < constructed; i++){
            newdata[i].~T();
        }
        dealloc(newdata);
        throw;
    }
    for(std::size_t i = 0; i < size_; i++){
        data_[i].~T();
    }
    dealloc(data_);
    data_ = newdata;
    cap_ = newcap;
    size_ = size_ + count;
    return data_ + pos;
}

template<typename T>
template<class InputIt>
typename MyVector<T>::iterator MyVector<T>::insert(std::size_t pos, InputIt first, InputIt last) {
    if(pos > size_) throw std::out_of_range("insert");
    MyVector tmp(first, last);

    std::size_t n = tmp.size();
    if(n == 0) return data_ + pos;
    std::size_t newcap = std::max(cap_*2, size_ + n);
    T* newdata = alloc(newcap);
    std::size_t constructed = 0;
    try{
        for(; constructed < pos; constructed++){
            new(newdata + constructed) T(std::move_if_noexcept(data_[constructed]));
        }
        for(std::size_t k = 0; k < n; k++, constructed++){
            new(newdata + constructed) T(std::move_if_noexcept(tmp.data_[k]));
        }
        for(std::size_t k = pos; k < size_; k++, constructed++){
            new(newdata + constructed) T(std::move_if_noexcept(data_[k]));
        }
    }catch(...){
        for(std::size_t i = 0; i < constructed; i++){
            newdata[i].~T();
        }
        dealloc(newdata);
        throw;
    }
    for(std::size_t i = 0; i < size_; i++){
        data_[i].~T();
    }
    dealloc(data_);
    data_ = newdata;
    cap_ = newcap;
    size_ = size_ + n;
    return data_ + pos;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::erase(std::size_t pos) {
    if(pos >= size_){
        throw std::out_of_range("erase");
    }
    for(std::size_t i = pos; i+1 < size_; i++){
        data_[i] = std::move(data_[i+1]);
    }
    size_--;
    data_[size_].~T();
    return data_ + pos;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::erase(std::size_t first, std::size_t last) {
    if(first > last || last > size_) throw std::out_of_range("erase");
    std::size_t n = last - first;
    if (n == 0) return data_ + first;
    for(std::size_t i = first; i + n < size_; i++){
        data_[i] = std::move(data_[i+n]);
    }
    for(std::size_t i = size_ - n; i < size_; i++){
        data_[i].~T();
    }
    size_ -= n;
    return data_ + first;
}

template<typename T>
template<class... Args>
void MyVector<T>::emplace_back(Args&&... args) {
    if(size_ == cap_){  
        grow(cap_ == 0 ? 10 : cap_*2);
    }
    new(data_ + size_) T(std::forward<Args>(args)...);
    size_++;
}

template<typename T>
template<typename... Args>
typename MyVector<T>::iterator MyVector<T>::emplace(std::size_t pos, Args&&... args) {
    if(pos > size_) throw std::out_of_range("emplace");
    std::size_t index = pos;

    if(index == size_){
        emplace_back(std::forward<Args>(args)...);
        return data_ + index;
    }

    if(size_ == cap_){
        grow(cap_ == 0 ? 10 : cap_*2);
    }

    new(data_ + size_) T(std::move(data_[size_ - 1]));
    size_++;

    for(std::size_t i = size_ - 2; i > index; i--){
        data_[i] = std::move(data_[i - 1]);
    }
    
    data_[index] =  T(std::forward<Args>(args)...);
    
    return data_ + index;
}

#endif
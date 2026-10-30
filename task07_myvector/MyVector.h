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
    static T* alloc(std::size_t n){
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    static void dealloc(T* p) noexcept{
        ::operator delete(p);
    }
    void free_all() noexcept {
        for(std::size_t i = 0; i < size_; i++){
            data[i].~T();
        }
        dealloc(data_);
        data_ = nullptr;
        size_ = 0;
        cap_ = 0;
    }

public:
    MyVector() noexcept : data_(nullptr), size_(0), cap_(0) {}
    MyVector(std::size_t ca) : data(ca ? alloc(ca) : nullptr), size_(0), cap_(ca) {}
    MyVector(std::size_t num, T val) : data(num ? alloc(num) : nullptr), size_(0), cap_(num) {
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
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const ;


    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other);

    void grow(std::size_t newcap);

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
    }catch{
        for(std::size_t i = 0; i < size_; i++){
            data_[i].~T();
        }
        ::operator detele(data_);
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
            emplce_back(*first);
        }
    }catch{
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
void MyVector<T>::grow(std::size_t newcap){
    if(newcap == cap_) return;

    T* newdata = alloc(newcap);
    std::size_t constrructd = 0;
    try{
        for(; constructed < size_; i++){
            new(newdata + constructed) T(std::move_if_noexcept(data_[construceted]));
        }
    }catch(...){
        for(std::size_t i = 0; i < constructed; i++){
            newdata[i].~T();
        }
        dealloc(newdata);
        throw;
    }
    dealloc(data_);
    data_ = newdata;
    cap_ = newcap;
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
void MyVector<T>::push_back(const T& v) {
    if(size_ == cap_){
        std::size_t newcap = (cap_ == 0 ? 10 : 2*cap_);
        reserve(newcap);
        cap_ = newcap;
    }
    data_[size_++] = v;
}

template<typename T>
void MyVector<T>::push_back(T&& v) {
    if(size_ == cap_){
        std::size_t newcap = (cap_ == 0 ? 10 : 2*cap_);
        reserve(newcap);
        cap_ = newcap;
    }
    T tmp = v;
    v = 0;
    data_[size_++] = tmp;
}

template<typename T>
void MyVector<T>::pop() {
    if(size_ == 0){
        throw std::out_of_range("empty");
    }
    if(cap_ == 0){
        throw std::out_of_range("empty");
    }
    if(data_ == nullptr){
        theow std::invailed_argument("nullptr pointer");
    }
    --size_;
}

template<typename T>
void MyVector<T>::clear() {
    cap_ = 0;
    size_ = 0;
    delete[] data_;
    data_ = nullptr;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::insert(std::size_t pos, T& val) {
    if(pos > size_){
        throw std::invaild_argument("unvaild");
    }
    if(pos == size_){
        push_back(val);
    }
    else{
        T* tmp = new T[cap_ + 1];
        size_++;
        for(std::size_t i = 0; i < size_; i++){
            if(i < pos){
                tmp[i] = data_[i];
            }
            if(i == pos){
                tmp[i] = val;
            }
            if(i > pos){
                tmp[i] = data_[i-1];
            }
        }
        std::swap(data_, tmp);
    }
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::insert(std::size_t pos, int count, T& val) {
    if(pos > size_){
        throw std::invaild_argument("unvaild");
    }
    if(pos == size_){
        while(pos + count > size_){
            push_back(val);
        }
    }
    else{
        T* tmp = new T[cap_ + count];
        size_+= count;
        for(std::size_t i = 0; i < size_; i++){
            if(i < pos){
                tmp[i] = data_[i];
            }
            if(i >= pos && i < pos + count){
                tmp[i] = val;
            }
            if(i >= pos + count){
                tmp[i] = data_[i-count];
            }
        }
        std::swap(data_, tmp);
    }
}

template<typename T>
template<class InputIt>
typename MyVector<T>::iterator MyVector<T>::insert(std::size_t pos, InputIt first, InputIt last) {
    std::size_t index = static_cast<std::size_t>(pos - data_);
    MyVector tmp(first, last);
    if(tmp.size_ == 0){
        throw std::invaild_argument("empty");
    }

    if(size_ + tmp.size_ >= cap_){
        grow(std::max(cap_*2, size_ + tmp.size_));
    }

    std::size_t n = tmp.size_;
    for(std::size_t i = size_ - 1; i > index; i--){
        new(data_ + i + n) = T(std::move(data_[i]));
        data_[i].~T();
    }

    for(std::sizr_t i = 0; i < n; i++){
        new(data_ + index + i) T(std::move(tmp.data_[i]));
    }
    size_ += n;

    return data_ + index;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::erase(std::size_t pos) {
    if(pos >= size_){
        throw std::invaild_argument("invaild");
    }
    T* tmp = new T[cap_ - 1];
    for(std::size_t i = 0; i < size_; i++){
        if(i < pos){
            tmp[i] = data_[i]
        }
        if(i > pos){
            tmp[i] = data_[i-1];
        }
    }
    std::swap(tmp, data_);
    size_--;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::erase(std::size_t first, std::size_t last) {
    if(pos >= size_){
        throw std::invaild_argument("invaild");
    }
    std::size_t count = last - first + 1;
    T* tmp = new T[cap_ - count];
    for(std::size_t i = 0; i < size_; i++){
        if(i < first){
            tmp[i] = data_[i]
        }
        if(i > last){
            tmp[i] = data_[i- count - 1];
        }
    }
    std::swap(tmp, data_);
    size_ -= count;
}

template<typename T>
template<typename... Args>
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
    std::size_t index = static_cast<std::size_t>(pos - data_);

    if(index == size_){
        emplace_back(std::forward<Args>(args)...);
        return data_ + index;
    }

    if(size_ == cap_){
        grow(cap_ == 0 ? 10 : cap_*2);
    }

    new(data_ + size_) T(std::move(data_[size_ - 1]));
    size_++;

    for(std::size_ t i = size_ - 2; i > index; i--){
        data_[i] = std::move(data[i - 1]);
    }

    data_[index] = T(std::forward<Args>(args)...);
    
    return data_ + index;
}

#endif
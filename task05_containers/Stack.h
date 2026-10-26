#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <iomanip>
#include <stdexcept>

template<class T>
class Stack{
private:
    std::size_t capacity;
    std::size_t count;
    T* data;
public:
    Stack() : capacity(0), count(0), data(nullptr) {}
    ~Stack();

    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
    Stack(Stack&& other) noexcept;
    Stack& operator=(Stack&& other) noexcept;

    void push(const T& v);
    void pop();
    T& top();
    const T& top() const;
    bool empty() const;
    std::size_t size() const;
    void clear() ;

};

template<typename T>
Stack<T>::~Stack() {
    clear();
}

template<typename T>
Stack<T>::Stack(const Stack& other) 
    : capacity(other.capacity), 
    count(other.count), 
    data(new T[other.capacity]){

    for(std::size_t i; i < count; i++){
        data[i] = other.data[i];
    }
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if(this == &other){
        return *this;
    }
    Stack tmp(other);
    std::swap(count, tmp.count);
    std::swap(data, tmp.data);
    std::swap(capacity, tmp.capacity);
    return *this;
}

template<typename T>
Stack<T>::Stack(Stack&& other) noexcept
    : capacity(other.capacity), count(other.count), data(other.data){
    other.data = nullptr;
    other.count = 0;
    other.capacity = 0;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if(this == &other){
        return *this;
    }
    clear();
    data = other.data;
    count = other.count;
    capacity = other.capacity;
    other.data = nullptr;
    other.count = 0;
    other.capacity = 0;
    return *this;
}

template<typename T>
void Stack<T>::push(const T& v) {
    if(count == capacity){
        std::size_t newcap = (capacity == 0 ? 10 : capacity*2);
        T* tmp = new T[newcap];
        for(std::size_t i = 0; i < count; i++){
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
        capacity = newcap;
    }
    data[count] = v;
    count++;
    
}

template<typename T>
void Stack<T>::pop() {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    else{
        count--;
    }
}

template<typename T>
T& Stack<T>::top() {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    else{
        return data[count-1];
    }
}

template<typename T>
const T& Stack<T>::top() const {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    else{
        return data[count-1];
    }
}

template<typename T>
bool Stack<T>::empty() const {
    return count == 0;
}

template<typename T>
std::size_t Stack<T>::size() const {
    return count;
}

template<typename T>
void Stack<T>::clear() {
    delete[] data;
    capacity = 0;
    count = 0;
    data = nullptr;
}

#endif
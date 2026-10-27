#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

template<class T>
class Queue{
private:
    std::size_t capacity;
    std::size_t count;
    std::size_t head;
    std::size_t tail;
    T* data;
public:
    Queue(): capacity(0), count(0), head(0), tail(0), data(nullptr) {}
    ~Queue();

    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    Queue(Queue&& other) noexcept;
    Queue& operator=(Queue&& other) noexcept;

    void push(const T& b);
    void pop();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    bool empty() const;
    std::size_t size() const;
    void clear();

};

template<typename T>
Queue<T>::~Queue() {
    clear();
}

template<typename T>
Queue<T>::Queue(const Queue& other)
    : capacity(other.capacity), 
    count(other.count), 
    head(other.head), 
    tail(other.tail), 
    data(other.data) {
        if(capacity > 0){
            data = new T[capacity];
            for(std::size_t i = 0; i < capacity; i++){
                data[i] = other.data[i];
            }
        }
    }

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if(this == &other){
        return *this;
    }
    Queue tmp(other);
    std::swap(capacity, tmp.capacity);
    std::swap(count, tmp.count);
    std::swap(head, tmp.head);
    std::swap(tail, tmp.tail);
    std::swap(data, tmp.data);
    return *this;
}

template<typename T>
Queue<T>::Queue(Queue&& other) noexcept
    : capacity(other.capacity), 
    count(other.count), 
    head(other.head),
    tail(other.tail),
    data(other.data) {
        other.capacity = 0;
        other.count = 0;
        other.head = 0;
        other.tail = 0;
        other.data = nullptr;        
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept {
    if(this == &other){
        return *this;
    }
    clear();
    std::swap(capacity, other.capacity);
    std::swap(count, other.count);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(data, other.data);
    return *this;
}

template<typename T>
void Queue<T>::push(const T& b) {
    if(count == capacity){
        std::size_t newcap = (capacity == 0 ? 10 : capacity*2);
        T* tmp = new T[newcap];
        for(std::size_t i = 0; i < count; i++){
            std::size_t k = (head + i) % capacity;
            tmp[i] = data[k];
        }
        std::swap(tmp, data);
        delete[] tmp;
        capacity = newcap;
        head = 0;
        tail = count;
    }
    data[tail] = b;
    tail = (tail + 1) % capacity;
    count++;
    return;
}

template<typename T>
void Queue<T>::pop() {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    head = (head + 1) % capacity;
    count--;
    return;
}

template<typename T>
T& Queue<T>::front() {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    return data[head];
}

template<typename T>
const T& Queue<T>::front() const {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    return data[head];
}

template<typename T>
T& Queue<T>::back() {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    std::size_t index = tail;
    index = (index - 1 + capacity) % capacity;
    return data[index]; 
}

template<typename T>
const T& Queue<T>::back() const {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    std::size_t index = tail;
    index = (index - 1 + capacity) % capacity;
    return data[index]; 
}

template<typename T>
bool Queue<T>::empty() const {
    return count == 0;
}

template<typename T>
std::size_t Queue<T>::size() const {
    return count;
}

template<typename T>
void Queue<T>::clear() {
    capacity = 0;
    count = 0;
    head = 0;
    tail = 0;
    delete[] data;
    data = nullptr;
}

#endif
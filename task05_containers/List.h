#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
using std::string;

//int, double, char, bool, string

template<class T>
class List{
private:
    struct Node{
        T val;
        Node* next;
    };
    Node* head;
    Node* tail;
    size_t count;
public:
    explicit List() : head(nullptr), tail(nullptr), count(0) {}
    ~List() {
        clear();
    }

    List(const List& other);
    List& operator=(const List& other);   
    List(List&& other) noexcept;
    List& operator=(List&& other) noexcept;
    
    void push_back(const T& t);
    void push_front(const T& t);
    void pop_back();
    void pop_front();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    bool empty() const;
    int size() const;
    void clear();
};

template<typename T>
List<T>::List(const List& other) : head(nullptr), tail(nullptr), count(0) {
    for(Node*cur = other.head; cur; cur = cur->next){
        push_back(cur->val);
    }
}

template<typename T>
List<T>& List<T>::operator=(const List& other){
    if(this == &other){
        return *this;
    }
    List tmp(other);
    std::swap(head, tmp.head);
    std::swap(tail, tmp.tail);
    std::swap(count, tmp.count);
    return *this;
}

template<typename T>
List<T>::List(List&& other) noexcept
    : head(other.head), tail(other.tail), count(other.count){
    other.head = other.tail = nullptr;
    other.count = 0;
}

template<typename T>
List<T>& List<T>::operator=(List&& other) noexcept{
    if(this == &other){
        return *this;
    }
    clear();
    head = other.head;
    tail = other.tail; 
    count = other.count;
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
    return *this;
}

template<typename T>
void List<T>::push_back(const T& t) {
    Node* tmp = new Node{t, nullptr};
    if(count != 0){
        tail->next = tmp;
    }
    else{
        head = tmp;
    }
    tail = tmp;
    count++;
}

template<typename T>
void List<T>::push_front(const T& t) {
    Node* tmp = new Node{t, nullptr};
    if(count != 0){
        tmp->next = head;
    }
    else{
        tmp->next = nullptr;
        tail = tmp;
    }
    head = tmp;
    count++;
}


template<typename T>
void List<T>::pop_back() {
    if(count == 0){
        throw std::out_of_range("count == 0");
    }
    Node* cur = head;
    if(count > 1){
        while(cur->next != tail){
            cur = cur->next;
        }
        Node* tmp;
        tmp = tail;
        tail = cur;
        cur = tmp;
        tail->next = nullptr;
    }
    else{
        head = nullptr;
        tail = nullptr;
    }
    delete cur;
    count--;
}

template<typename T>
void List<T>::pop_front() {
    if(count == 0){
        throw std::out_of_range("count == 0");
    }
    Node* cur = head;
    if(count == 1){
        head = nullptr;
        tail = nullptr;
    }
    else{
        head = head->next;
    }
    delete cur;
    count--;
}

template<typename T>
T& List<T>::front() {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    return head->val;
}

template<typename T>

const T& List<T>::front() const {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    return head->val;
}

template<typename T>
T& List<T>::back() {
    if(count == 0){
        throw std::out_of_range("empty");
    }
    return tail->val;
}

template<typename T>
const T& List<T>::back() const{
    if(count == 0){
        throw std::out_of_range("empty");
    }
    return tail->val;
}

template<typename T>
bool List<T>::empty() const  {
    return count == 0;
}

template<typename T>
int List<T>::size() const {
    return count;
}

template<typename T>
void List<T>::clear() {
    while(count != 0){
        pop_front();
    }
}

#endif
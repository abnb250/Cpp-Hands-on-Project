#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <algorithm>
#include <cmath>
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
    explicit List(List& other);
    List& operator=(List& other);   
    ~List() {}
    void push_back(const T& t);
    void push_front(const T& t);
    void pop_back();
    void pop_front();
    T& front();
    T& back();
    bool empty();
    int size();
    void clear();
};

template<typename T>
List<T>::List(List& t){
    for(Node*cur = t.head; cur; cur = cur->tail){
        *this.push_back(cur->val);
    }
}

template<typename T>
List<T>& List<T>::operator=(List& other){
    if(this == &other){
        return *this;
    }
    
}

template<typename T>
void List<T>::push_back(const T& t) {
    Node* tmp;
    tmp->val = t;
    tmp->next = nullptr;
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
    Node* tmp;
    tmp->val = t;
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
        throw std:out_of_range("count == 0");
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
}

template<typename T>
T& List<T>::front() {
    return head->val;
}

template<typename T>
T& List<T>::back() {
    return tail->val;
}

template<typename T>
bool List<T>::empty() {
    return count == 0;
}

template<typename T>
int List<T>::size() {
    return count;
}

template<typename T>
void List<T>::clear() {
    while(count != 0){
        *this.pop_front();
    }
}

#endif
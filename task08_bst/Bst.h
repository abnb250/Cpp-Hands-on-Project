#ifndef BST_H
#define BST_H

#include <iostream>
#include <stdexcept>
#include <utility>  
#include <cstddef>
#include <queue>


template<class T>
class BST{
private:
    struct Node{
        T v;
        Node* left = nullptr;
        Node* right = nullptr;
        explicit Node(const T& val) : v(val) {}
        explicit Node(T&& val) : v(std::move(val));
    };
    Node* root_ = nullptr;
    std::size_t size_ = 0;

    Node* clearRec(Node* n) noexcept{
        
    }

    Node* minNode(Node* n) const {}
    Node* maxNode(Node* n) const {}

    Node* eraseRec(Node* n, const T& val, bool& erased) {}

    Node* find(const T& v) {}

    std::size_t heightRec(const Node* n) {}

    Node* clone(const Node* n) {}

    template<class Fn> void inorderRec(Node* n, Fn& fn) const {}
    template<class Fn> void preorderRec(Node* n, Fn& fn) const {}
    template<class Fn> void postorderRec(Node* n, Fn& fn) const {}

public:
    BST() noexcept = default;
    ~BST() noexcept;

    BST(const BST& other);
    BST& operator=(BST& other);
    BST(BST&& other) noexcept;
    BST& operator=(BST&& other);

    void swap(BST& other) noexcept;
    friend void swap(BST& a, BST& b) noexcept {a.swap(b);}

    bool insert(const T& val);
    bool insert(T&& val);

    bool contains(const T& val) const;

    const T& minimum() const;
    const T& maximum() const;

    bool erase(const T& v);

    template<class Fn> void inorder(Fn&& fn) const;
    template<class Fn> void preorder(Fn&& fn) const;
    template<class Fn> void postorder(Fn&& fn) const;
    template<class Fn> void levelorder(Fn&& fn) const;

    std::size_t size() const noexcept {return size_;}
    bool empty() const noexcept {return size_ == 0;}
    std::size_t height() const;
    void clear() noexcept;
};

template<typename T>
BST<T>::~BST() noexcept {}

template<typename T>
BST<T>::BST(const BST& other) {}

template<typename T>
BST<T>& BST<T>::operator=(BST& other) {}

template<typename T>
BST<T>::BST(BST&& other) noexcept {}

template<typename T>
BST<T>& BST<T>::operator=(BST&& other) {}

template<typename T>
void BST<T>::swap(BST& other) noexcept {}

template<typename T>
bool BST<T>::insert(const T& val) {}

template<typename T>
bool BST<T>::insert(T&& val) {}

template<typename T>
bool BST<T>::contains(const T& val) const {}

template<typename T>
const T& BST<T>::minimum() const {}

template<typename T>
const T& BST<T>::maximum() const {}

template<typename T>
bool BST<T>::erase(const T& v) {}

template<typename T>
template<class Fn> 
void BST<T>::inorder(Fn&& fn) const {}

template<typename T>
template<class Fn> 
void BST<T>::preorder(Fn&& fn) const {}

template<typename T>
template<class Fn>
void BST<T>::postorder(Fn&& fn) const {}

template<typename T>
template<class Fn> 
void BST<T>::levelorder(Fn&& fn) const {}


template<typename T>
std::size_t BST<T>::height() const {}

template<typename T>
void BST<T>::clear() noexcept {}

#endif BST_H


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
        explicit Node(T&& val) : v(std::move(val)) {}
    };
    Node* root_ = nullptr;
    std::size_t size_ = 0;

    void clearRec(Node* n) noexcept;

    Node* minNode(Node* n) const;
    Node* maxNode(Node* n) const;

    Node* insertRec(Node* n, const T& val, bool& inserted);
    Node* insertRec(Node* n, T&& val, bool& inserted);

    Node* eraseRec(Node* n, const T& val, bool& erased);

    Node* findNode(const T& val) const;

    std::size_t heightRec(const Node* n);
    Node* cloneRec(const Node* n);

    template<class Fn> void inorderRec(Node* n, Fn& fn) const;
    template<class Fn> void preorderRec(Node* n, Fn& fn) const;
    template<class Fn> void postorderRec(Node* n, Fn& fn) const;

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

template <typename T>
void BST<T>::clearRec(Node *n) noexcept
{
    if (n == nullptr)
        return;
    if (n->left)
        clearRec(n->left);
    if (n->right)
        clearRec(n->right);
    delete n;
}

template <typename T>
typename BST<T>::Node* BST<T>::minNode(Node *n) const
{
    if (n == nullptr)
    {
        throw std::invaild_argument("nullptr pointer");
    }
    if (n->left)
        return minNode(n->left);
    return n;
}
template <typename T>
typename BST<T>::Node* BST<T>::maxNode(Node *n) const
{
    if (n == nullptr)
    {
        throw std::invaild_argument("nullptr pointer");
    }
    if (n->right)
        return maxNode(n->right);
    return n;
}

template <typename T>
typename BST<T>::Node* BST<T>::insertRec(Node *n, const T &val, bool &inserted)
{
    if (n == nullptr)
    {
        inserted = true;
        n = new Node(val);
        return n;
    }

    if (val > n->v)
        n->right = insertRec(n->right, val, inserted);
    else if (val < n->v)
        n->left = insertRec(n->left, val, inserted);
    return n;
}

template <typename T>
typename BST<T>::Node* BST<T>::insertRec(Node *n, T&& val, bool &inserted)
{
    if (n == nullptr)
    {
        inserted = true;
        return n = new Node(std::move(val));
    }

    if (val < n->v)
        n->left = insertRec(n, std::move(val), inserted);
    else if (val > n->v)
        n->right = insertRec(n, std::move(val), inserted);
    return n;
}

template <typename T>
typename BST<T>::Node* BST<T>::eraseRec(Node *n, const T &val, bool &erased)
{
    if (n == nullptr)
        return nullptr;

    if (val < n->v)
    {
        n->left = eraseRec(n->left, val, erased);
        return n;
    }
    else if (val > n->v)
    {
        n->right = eraseRec(n->right, val, erased);
        return n;
    }

    erased = true;

    if (!n->left && !n->right)
    {
        delete n;
        return n;
    }

    if (!(n->left))
    {
        n = n->right;
        return n;
    }
    if (!(n->right))
    {
        n = n->left;
        return n;
    }

    Node *tmp = minNode(n->right);
    std::swap(n->v, tmp->v);
    bool dummy = false;
    n->right = eraseReec(n->right, tmp->v, dummy);
    return n;
}

template <typename T>
typename BST<T>::Node* BST<T>::findNode(const T &val) const
{
    Node *tmp = root_;
    while (tmp)
    {
        if (val > tmp->v)
            tmp = tmp->right;
        else if (val < tmp->v)
            tmp = tmp->left;
        else
            return tmp;
    }
    return nullptr;
}

template <typename T>
std::size_t BST<T>::heightRec(const Node *n)
{
    if (n == nullptr)
        return static_cast<std::size_t>(0);
    return std::max(heightRec(n->left), heightRec(n->right)) + 1;
}

template <typename T>
typename BST<T>::Node* BST<T>::cloneRec(const Node *n)
{
    if (n == nullptr)
        return nullptr;
    Node *tmp = new Node(n->v);
    try
    {
        tmp->left = cloneRec(tmp->left);
        tmp->right = cloneRec(tmp->right);
    }
    catch (...)
    {
        clearRec(tmp);
        throw;
    }
    return tmp;
}

template <typename T>
template <class Fn>
void BST<T>::inorderRec(Node *n, Fn &fn) const
{
    if (n == nullptr)
        return;
    inorderRec(n->left, fn);
    fn(n->v);
    inorderRec(n->right, fn);
}
template <typename T>
template <class Fn>
void BST<T>::preorderRec(Node *n, Fn &fn) const
{
    if (n == nullptr)
        return;
    fn(n->v);
    preorderRec(n->left, fn);
    preorderRec(n->right, , fn);
}
template <typename T>
template <class Fn>
void BST<T>::postorderRec(Node *n, Fn &fn) const
{
    if (n == nullptr)
        return;
    postorderRec(n->left, fn);
    postorderRec(n->right, fn);
    fn(n->v);
}

template<typename T>
BST<T>::~BST() noexcept {
    clear();
}

template<typename T>
BST<T>::BST(const BST& other):
    root_(nullptr), size_(other.size_) {
    if(other.root_ == nullptr) return;

    Node* tmp = new Node(other.root_->val);
    tmp = cloneRec(other.root_);
    std::swap(tmp, root_);
}

template<typename T>
BST<T>& BST<T>::operator=(BST& other) {
    if(this == &other) return *this;
    BST tmp(other);
    swap(tmp);
    return *this;
}

template<typename T>
BST<T>::BST(BST&& other) noexcept : root_(other.root_), size_(other.size_){
    other.root_ = nullptr;
    other.size_ = 0;
}

template<typename T>
BST<T>& BST<T>::operator=(BST&& other) {
    if(this == &other) return *this;
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    other.root = nullptr;
    other.size_ = 0;
    return *this;
}

template<typename T>
void BST<T>::swap(BST& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
}

template<typename T>
bool BST<T>::insert(const T& val) {
    bool dummy = false;
    root_ = insertRec(root_, val, dummy);
    return dummy;
}

template<typename T>
bool BST<T>::insert(T&& val) {
    bool dummy = false;
    root_ = insertRec(root, std::move(val), dummy);
    return dummy;
}

template<typename T>
bool BST<T>::contains(const T& val) const {
    return findNode(val) != nullptr
}

template<typename T>
const T& BST<T>::minimum() const {
    Node* tmp = minNode(root_);
    return tmp.root_->v;
}

template<typename T>
const T& BST<T>::maximum() const {
    Node* tmp = maxNode(root_);
    return tmp.root_->v;
}

template<typename T>
bool BST<T>::erase(const T& v) {
    bool dummy = false;
    root_ = eraseRec(root_, val, dummy);
    return dummy;
}

template<typename T>
template<class Fn> 
void BST<T>::inorder(Fn&& fn) const {
    inorderRec(root_, fn);
}
template<typename T>
template<class Fn> 
void BST<T>::preorder(Fn&& fn) const {
    preorderRec(root_, fn);
}

template<typename T>
template<class Fn>
void BST<T>::postorder(Fn&& fn) const {
    postorderRec(root_, fn);
}

template<typename T>
template<class Fn> 
void BST<T>::levelorder(Fn&& fn) const {
    queue<Node*> q;
    q.push(root_);
    while(!q.empty()){
        Node* tmp = q.front();
        q.pop();
        fn(tmp->v);
        if(tmp->left) q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
    }
}


template<typename T>
std::size_t BST<T>::height() const {
    return heigetRec(root_);
}

template<typename T>
void BST<T>::clear() noexcept {
    clearRec(root_);
}

#endif BST_H


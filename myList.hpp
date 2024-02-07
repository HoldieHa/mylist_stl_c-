#ifndef __MY_LIST_H_
#define __MY_LIST_H_

#include <iostream>
#include <initializer_list>

template<class T>
class myList
{
public:
    struct Node;
    class myIterator;

private:
    size_t size;
    Node* head;
    Node* tail;

public:
    myList(std::initializer_list<T> ls);
    myIterator begin(void);
    myIterator end(void);
    void push_back(T val);
    void push_front(T val);
    void pop_back(void);
    void pop_front(void);
    void insert(const myIterator& posi, const T val);
    void insert(const myIterator& posi, const size_t eleNum, const T val);
    void erase(const myIterator& posi);
    void erase(myIterator startPosi, myIterator endPosi);
    void remove(const T val);
    void display(void);
};

/****************************************------NODE------*******************************************************************/
template<class T>
struct myList<T>::Node
{
    T data;
    Node* next;
    Node* prev;

    Node(T val);
};

typedef struct Node Node;

template<typename T>
myList<T>::Node::Node(T val) : data{val}, next{nullptr}, prev{nullptr} {};

/****************************************------ITERATOR------*******************************************************************/
template<class T>
class myList<T>::myIterator
{
public:
    Node* ptr_iter;
public:
    explicit myIterator(Node* p);
    myIterator(const myIterator& src);
    ~myIterator();
    Node* getPtr(void);
    T& operator*(void) const;
    Node* operator->(void) const;
    myIterator operator+(const size_t num);
    int operator-(const myIterator& iter);
    myIterator operator-(const size_t num) const;
    myIterator operator++(void);
    myIterator operator--(void);
    bool operator!=(const myIterator& iter) const;
    bool operator==(const myIterator& iter) const;
    bool operator<=(const myIterator& iter) const;
    myIterator operator=(const myIterator& iter);
};

template<typename T>
typename myList<T>::Node* myList<T>::myIterator::getPtr(void)
{
    return ptr_iter;
}

template<typename T>
myList<T>::myIterator::myIterator(Node* p) : ptr_iter{p} {};

template<typename T>
myList<T>::myIterator::myIterator(const myIterator& src)
{
    ptr_iter = src.ptr_iter;
}

template<typename T>
myList<T>::myIterator::~myIterator(void) {}

template<typename T>
T& myList<T>::myIterator::operator*(void) const
{
    return ptr_iter->data;
}

template<typename T>
typename myList<T>::Node* myList<T>::myIterator::operator->(void) const
{
    return ptr_iter;
}

template<typename T>
typename myList<T>::myIterator myList<T>::myIterator::operator+(const size_t num)
{
    auto i = num;

    while ((i != 0) && (ptr_iter != nullptr))
    {
        --i;
        this->ptr_iter = this->ptr_iter->next;
    }
    if (i != 0)
    {
        std::cout << "Error: Invalid position" << std::endl;
        exit(0);
    }

    return *this;
}

template<typename T>
int myList<T>::myIterator::operator-(const myIterator& iter)
{
    int range = 0;

    while (ptr_iter != iter.ptr_iter)
    {
        ++range;
        ptr_iter = ptr_iter->prev;
    }

    return range;
}

template<typename T>
typename myList<T>::myIterator myList<T>::myIterator::operator-(const size_t num) const
{
    auto i = num;

    while ((num != 0) && (ptr_iter != head))
    {
        ptr_iter = ptr_iter->prev;
        --i;
    }
    if (i != 0)
    {
        std::cout << "Error: Invalid position" << std::endl;
        exit(0);
    }

    return *this;
}

template<typename T>
typename myList<T>::myIterator myList<T>::myIterator::operator++(void)
{
    if (ptr_iter != nullptr)
    {
        ptr_iter = ptr_iter->next;
    }
    else
    {
        std::cout << "Error: Invalid position" << std::endl;
        exit(0);
    }
    return *this;
}

template<typename T>
typename myList<T>::myIterator myList<T>::myIterator::operator--(void)
{
    ptr_iter = ptr_iter->prev;
    return *this;
}

template<typename T>
bool myList<T>::myIterator::operator!=(const myIterator& iter) const
{
    return (ptr_iter != iter.ptr_iter);
}

template<typename T>
bool myList<T>::myIterator::operator==(const myIterator& iter) const
{
    return (ptr_iter == iter.ptr_iter);
}

template<typename T>
bool myList<T>::myIterator::operator<=(const myIterator& iter) const
{
    return (ptr_iter <= iter.ptr_iter);
}

template<typename T>
typename myList<T>::myIterator myList<T>::myIterator::operator=(const myIterator& iter)
{
    ptr_iter = iter.ptr_iter;
    return *this;
}

/****************************************------LIST------*******************************************************************/

template<typename T>
typename myList<T>::myIterator myList<T>::begin(void)
{
    return myIterator(head);
}

template<typename T>
typename myList<T>::myIterator myList<T>::end(void)
{
    return myIterator(tail);
}

template<typename T>
void myList<T>::push_back(T val)
{
    Node* newNode = new Node(val);

    if ((head == nullptr) || (size == 0))
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++size;
}

template<typename T>
void myList<T>::push_front(T val)
{
    Node* newNode = new Node(val);

    if ((head == nullptr) || (size == 0))
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    ++size;
}

template<typename T>
myList<T>::myList(std::initializer_list<T> ls) : size{0}, head{nullptr}, tail{nullptr}
{
    for (auto element : ls)
    {
        push_back(element);
    }
}

template<typename T>
void myList<T>::pop_back(void)
{
    tail = tail->prev;
    tail->next = nullptr;
    --size;
}

template<typename T>
void myList<T>::pop_front(void)
{
    head = head->next;
    head->prev = nullptr;
    --size;
}

template<typename T>
void myList<T>::insert(const myIterator& posi, const T val)
{
    Node* newNode = new Node(val);

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        if (posi == begin())
        {
            push_front(val);
        }
        else if (posi == end() + 1U)
        {
            push_back(val);
        }
        else
        {
            newNode->next = posi.ptr_iter;
            newNode->prev = posi->prev;
            posi->prev->next = newNode;
            posi->prev = newNode;
            ++size;
        }
    }
}

template<typename T>
void myList<T>::insert(const myIterator& posi, const size_t eleNum, const T val)
{
    auto i = eleNum;

    while (i != 0)
    {
        insert(posi, val);
        --i;
    }
}

template<typename T>
void myList<T>::erase(const myIterator& posi)
{
    myIterator tmp(posi);

    if (head != nullptr)
    {
        if ((begin() == tmp) && (end() != tmp))
        {
            head = head->next;
            head->prev = nullptr;
        }
        else if ((end() == tmp) && (begin() != tmp))
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else if ((end() != tmp) && (begin() != tmp))
        {
            posi->prev->next = posi->next;
            posi->next->prev = posi->prev;
        }
        delete tmp.ptr_iter;
        --size;
    }
}

template<typename T>
void myList<T>::remove(const T val)
{
    Node* current = head;
    Node* remove = nullptr;

    while (current != nullptr)
    {
        if (current->data == val)
        {
            if (current == head)
            {
                remove = current;
                current = current->next;
                head = current;
                head->prev = nullptr;
                delete remove;
            }
            else if (current == tail)
            {
                remove = current;
                tail = current->prev;
                tail->next = nullptr;
                current = current->next;
                delete remove;
            }
            else
            {
                remove = current;
                current->prev->next = current->next;
                current->next->prev = current->prev;
                current = current->next;
                delete remove;
            }
        }
        else
        {
            current = current->next;
        }
    }
}

template<typename T>
void myList<T>::erase(myIterator startPosi, myIterator endPosi)
{
    auto range = 0;
    auto startOffset = 0;

    range = endPosi - startPosi;
    startOffset = startPosi - begin();
    for (auto i = range + 1U; i != 0; --i)
    {
        erase(begin() + startOffset);
    }
}

template<typename T>
void myList<T>::display(void)
{
    Node* tmp = head;

    std::cout << "[ ";
    while ((tmp != nullptr) && (size != 0))
    {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    std::cout << "]" << std::endl;
}

#endif /* __MY_LIST_H */

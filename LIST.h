#ifndef LIST_H
#define LIST_H
#include<iostream>
template<typename T>
class List
{
    public:
        struct Node
        {
            T value;
            Node* next;
        };
        typedef Node* PtrToNode;
    private:
        PtrToNode head;
    public:
        List();
        ~List();
        PtrToNode getHead(){return head;}
        void Insert(T x);
        void show();
};

template<typename T>
List<T>::List()
{
    head = nullptr;
}
template<typename T>
List<T>::~List(){}

template<typename T>
void List<T>::Insert(T value)
{
    PtrToNode newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    if( head == nullptr )
    {
        head = newNode;

    }
    else
    {
        PtrToNode P = head;
        while( P->next != nullptr )
        {
            P = P->next;
        }
        P->next = newNode;
    }
}
template<typename T>
void List<T>::show()
{
    PtrToNode P = head;
    while( P != nullptr )
    {
        std::cout << P->value << ",";
        P = P->next;
    }
}

#endif
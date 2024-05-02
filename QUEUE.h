#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>
template<typename T>
class Queue
{
    public:
        struct Node
        {
            T value;
            Node *next;
        };
    typedef Node* PtrToNode;

    private:
        PtrToNode front;
        PtrToNode rear;
    public:
        bool isEmpty();
        Queue();
        ~Queue();
        void enqueue(T x);
        T dequeue();
};
template<typename T>
void Queue<T>::enqueue(T x)
{
    PtrToNode newNode = new Node;
    newNode->value = x;
    if( front == nullptr )
    {
        newNode->next = nullptr;
        front = rear = newNode;
    }
    else
    {
        newNode->next = rear;
        rear = newNode;
    }
}
template<typename T>
bool Queue<T>::isEmpty()
{
    return front == nullptr;
}

template<typename T>
T Queue<T>::dequeue()
{
    if( isEmpty() )
    {
        return T(-1);
    }
    T x = front->value;
    PtrToNode temp = front;
    if( rear == front )
    {
        rear = front = nullptr;
    }
    else
    {
        front = rear;
        while( front->next != temp )
        {
            front = front->next;
        }
    }
    delete temp;
    return x;
}
template<typename T>
Queue<T>::Queue()
{
    front = rear = nullptr;
}
template<typename T>
Queue<T>::~Queue()
{
    while(!isEmpty())
    {
        dequeue();
    }
}

#endif
#ifndef STACK_H
#define STACK_H
template<typename T>
class Stack
{
    private:
        struct Node
        {
            T value;
            Node *next;
        };
        typedef Node* PtrToNode;
        PtrToNode top;
    public:
        Stack();
        ~Stack();

        T Pop();
        T getTop();
        void Push(T x);
        bool IsEmpty();
};
template<typename T>
Stack<T>::Stack()
{
    top = nullptr;
}
template<typename T>
Stack<T>::~Stack(){}

template<typename T>
bool Stack<T>::IsEmpty()
{
    return top == nullptr;
}

template<typename T>
T Stack<T>::Pop()
{
    PtrToNode target = top;
    top = top->next;
    T answer = target->value;
    delete target;
    return answer;
}
template<typename T>
void Stack<T>::Push(T x)
{
    PtrToNode newNode = new Node;
    newNode->value = x;
    if( top == nullptr )
    {
        top = newNode;
        newNode->next = nullptr;
    }
    else
    {
        newNode->next = top;
        top = newNode;
    }
}
template<typename T>
T Stack<T>::getTop()
{
    return top->value;
}
#endif
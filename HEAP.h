#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <vector>
template <typename T>
class Heap
{
private:
    std::vector<T> heapArray;
    int cap;
    using CompareFunction = bool (*)(const T &, const T &);
    CompareFunction BiggerFunc;
    bool Bigger(const T &A, const T &B)
    {
        return BiggerFunc(A, B);
    }
    using AssignFunction = T (*)();
    AssignFunction AssignFunc;
    void Assign(T &ArrayZero)
    {
        ArrayZero = AssignFunc();
    }
    CompareFunction EqualFunc;
    bool Equal(const T &A, const T &B)
    {
        return EqualFunc(A, B);
    }
    void swap(T & a, T & b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

public:
    void Insert(T value);
    void Delete();
    Heap(CompareFunction funcBigger, AssignFunction funcAssign, CompareFunction funcEqual, int size);
    ~Heap(){};
    bool IsEmpty();
    int FindMin();
    T PopMin();
    void DecreaseKey(int i, T newValue);
    int Contain(T target);
};
template <typename T>
int Heap<T>::Contain(T target)
{
    for( int i = 1 ; i <= cap ; ++i )
    {
        if(Equal(heapArray[i], target))
        {
            return i;
        }
    }
    return -1;
}
template <typename T>
bool Heap<T>::IsEmpty()
{
    return cap == 0;
}
template <typename T>
Heap<T>::Heap(CompareFunction funcBigger, AssignFunction funcAssign, CompareFunction funcEqual,int size)
{
    heapArray.resize(size);
    AssignFunc = funcAssign;
    BiggerFunc = funcBigger;
    EqualFunc = funcEqual;
    Assign(heapArray[0]);
    cap = 0;
}
template <typename T>
void Heap<T>::Insert(T value)
{
    int i;
    for (i = ++cap; Bigger(heapArray[i / 2], value); i /= 2)
    {
        heapArray[i] = heapArray[i / 2];
    }
    heapArray[i] = value;
}

template <typename T>
void Heap<T>::DecreaseKey(int i,T newValue)
{
    int father;
    heapArray[i] = newValue;
    for( ; i/2 >= 1 ; i = father )
    {
        father = i/2;
        if(Bigger(heapArray[father], heapArray[i]))
        {
            swap(heapArray[father], heapArray[i]);
        }
    }
}

template <typename T>
T Heap<T>::PopMin()
{
    int i, Child;
    T MinElement, LastElement;
    if (IsEmpty())
    {
        std::cout << "Priority queue is empty";
        return heapArray[0];
    }
    MinElement = heapArray[1];
    LastElement = heapArray[cap];
    for (i = 1; i * 2 <= cap; i = Child)
    {
        Child = 2 * i;
        if (Child != cap && Bigger(heapArray[Child], heapArray[Child + 1]))
        {
            ++Child;
        }

        if (Bigger(LastElement, heapArray[Child]))
        {
            heapArray[i] = heapArray[Child];
        }
        else
        {
            break;
        }
    }
    heapArray[i] = LastElement;
    cap--;
    return MinElement;
}

#endif

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "QUEUE.h"
#include "STACK.h"
class Tree
{
public:
    struct Node
    {
        int value;
        Node *left;
        Node *right;
    };
    typedef Node *PtrToNode;
    typedef PtrToNode Root;

private:
    Root root;
    Root Insert(Root root_, int x);
    void MakeEmpty(Root root_);

public:
    Root getRoot() const { return root; };
    Tree();
    ~Tree();
    void CreateTree();
    bool PreOrderTree(Root root_) const;
    bool InOrderTreeByRecursion(Root root_) const;
    void InOrderTree(Root root_) const;
    bool LaOrderTree(Root root_) const;
    void BFS(Root root_);
};

Tree::Tree()
{
    root = nullptr;
}

void Tree::MakeEmpty(Root root_)
{
    if (root_ != nullptr)
    {
        MakeEmpty(root_->left);
        MakeEmpty(root_->right);
        delete root_;
    }
}

Tree::~Tree()
{
    MakeEmpty(root);
}

Tree::Root Tree::Insert(Root root_, int x)
{
    if (root_ == nullptr)
    {
        PtrToNode newNode = new Node;
        newNode->left = newNode->right = nullptr;
        newNode->value = x;
        return newNode;
    }
    else if (x > root_->value)
    {
        root_->right = Insert(root_->right, x);
    }
    else
    {
        root_->left = Insert(root_->left, x);
    }
    return root_;
}

void Tree::CreateTree()
{
    while (true)
    {
        int x;
        if (std::cin >> x)
        {
            root = Insert(root, x);
        }
        else
        {
            break;
        }
    }
}

bool Tree::PreOrderTree(Root root_) const
{
    if (root_ == nullptr)
    {
        return false;
    }
    std::cout << root_->value << ",";
    PreOrderTree(root_->left);
    PreOrderTree(root_->right);
    return true;
}

bool Tree::InOrderTreeByRecursion(Root root_) const
{
    if (root_ == nullptr)
    {
        return false;
    }
    InOrderTreeByRecursion(root_->left);
    std::cout << root_->value << ",";
    InOrderTreeByRecursion(root_->right);
    return true;
}

bool Tree::LaOrderTree(Root root_) const
{
    if (root_ == nullptr)
    {
        return false;
    }
    LaOrderTree(root_->left);
    LaOrderTree(root_->right);
    std::cout << root_->value << ",";
    return true;
}

void Tree::BFS(Root root_)
{
    static Queue<Root> Q;
    Q.enqueue(root_);
    while (!Q.isEmpty())
    {
        Root deal_root = Q.dequeue();
        std::cout << deal_root->value << ",";
        if (deal_root->left != nullptr)
        {
            Q.enqueue(deal_root->left);
        }
        if (deal_root->right != nullptr)
        {
            Q.enqueue(deal_root->right);
        }
    }
}

void Tree::InOrderTree(Root root_) const
{
    Stack<Root> S;
    Queue<int> Q;
    Root temp = root_;
    while (temp != nullptr || !S.IsEmpty())
    {
        while (temp != nullptr) // 不断将节点的左子树压入栈
        {
            S.Push(temp);
            temp = temp->left;
        }
        temp = S.Pop();         //<1>
        Q.enqueue(temp->value); // 当触底时，将其弹出至输出队列
        temp = temp->right;     // 尝试向右子树移动，进入循环：如果有则处理，没有则通过<1>重新赋值为上一级节点
    }
    while (!Q.isEmpty())
    {
        std::cout << Q.dequeue() << ",";
    }
}
#endif
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <stack>
using namespace std;


//------------------------------------------------------------------------------
//
//  Print a tree in zig-zag order. Zig-zag order is a breath first iteration
//  where each successive level is printed in the reverse direction of the
//  previous.
//
//            [10]
//           /    \
//        [4]      [16]
//        / \      /  \
//      [2] [8]  [12] [18]
//          /      \     \
//        [6]      [14]  [20]
//                          \
//                          [24]
//                          /
//                       [22]
//
//  Traversal sequence is 10, 4, 16, 18, 12, 8, 2, 6, 14, 20, 24, 22
//
//------------------------------------------------------------------------------
template<class Object>
class BinaryTreeNode
{
public:
    BinaryTreeNode(const Object& object);
    ~BinaryTreeNode();
    void Add(const Object& object);

    Object m_object;
    BinaryTreeNode<Object>* m_pLeft;
    BinaryTreeNode<Object>* m_pRight;
};


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
void PrintZigZag(BinaryTreeNode<Object>* pRoot)
{
    stack<BinaryTreeNode<Object>*> stack1;
    stack<BinaryTreeNode<Object>*> stack2;
    stack<BinaryTreeNode<Object>*>* pStackCurrent = &stack1;
    stack<BinaryTreeNode<Object>*>* pStackNext = &stack2;
    bool forward = false;

    if (pRoot != nullptr)
    {
        pStackCurrent->push(pRoot);
    }

    while (!pStackCurrent->empty() || !pStackNext->empty())
    {
        if (pStackCurrent->empty())
        {
            swap(pStackCurrent, pStackNext);
            forward = !forward;
        }

        BinaryTreeNode<Object>* pNode = pStackCurrent->top();
        pStackCurrent->pop();
        cout << pNode->m_object << " ";
        BinaryTreeNode<Object>* pChild1 = pNode->m_pLeft;
        BinaryTreeNode<Object>* pChild2 = pNode->m_pRight;

        if (!forward)
        {
            swap(pChild1, pChild2);
        }

        if (pChild1 != nullptr)
        {
            pStackNext->push(pChild1);
        }

        if (pChild2 != nullptr)
        {
            pStackNext->push(pChild2);
        }
    }
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
template<class Object>
BinaryTreeNode<Object>::BinaryTreeNode(const Object& object)
    : m_object(object), m_pLeft(nullptr), m_pRight(nullptr)
{
}


template<class Object>
BinaryTreeNode<Object>::~BinaryTreeNode()
{
    if (m_pLeft != nullptr)
    {
        delete m_pLeft;
    }

    if (m_pRight != nullptr)
    {
        delete m_pRight;
    }
}


template<class Object>
void BinaryTreeNode<Object>::Add(const Object& object)
{
    if (object < m_object)
    {
        if (nullptr == m_pLeft)
        {
            m_pLeft = new BinaryTreeNode<Object>(object);
        }
        else
        {
            m_pLeft->Add(object);
        }
    }

    if (object > m_object)
    {
        if (nullptr == m_pRight)
        {
            m_pRight = new BinaryTreeNode<Object>(object);
        }
        else
        {
            m_pRight->Add(object);
        }
    }
}


int _tmain(int argc, _TCHAR* argv[])
{
    BinaryTreeNode<int> root(10);
    root.Add(4);
    root.Add(2);
    root.Add(8);
    root.Add(6);
    root.Add(16);
    root.Add(12);
    root.Add(18);
    root.Add(14);
    root.Add(20);
    root.Add(24);
    root.Add(22);
    PrintZigZag(&root);
    cout << endl;
    return 0;
}

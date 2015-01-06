// {"category": "Tree", "notes": "In-order traversal (recursive)"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <memory>
using namespace std;


//------------------------------------------------------------------------------
//
//  In-order binary tree traversal
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
//  In-order traversal sequence is 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24
//
//------------------------------------------------------------------------------
template<class Object>
class BinaryTreeNode
{
public:
    BinaryTreeNode(
        const Object& object,
        BinaryTreeNode<Object>* pParent = nullptr);

    ~BinaryTreeNode();
    void Add(const Object& object);

    Object m_object;
    BinaryTreeNode<Object>* m_pLeft;
    BinaryTreeNode<Object>* m_pRight;
    BinaryTreeNode<Object>* m_pParent;


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
    void PrintInOrder(BinaryTreeNode<Object>* pNode);
};


template<class Object>
void BinaryTreeNode<Object>::PrintInOrder(BinaryTreeNode<Object>* pNode)
{
    if (pNode != nullptr)
    {
        PrintInOrder(pNode->m_pLeft);
        cout << pNode->m_object << " ";
        PrintInOrder(pNode->m_pRight);
    }
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
template<class Object>
BinaryTreeNode<Object>::BinaryTreeNode(
    const Object& object,
    BinaryTreeNode<Object>* pParent)
    : m_object(object), m_pLeft(nullptr), m_pRight(nullptr), m_pParent(pParent)
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
            m_pLeft = new BinaryTreeNode<Object>(object, this);
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
            m_pRight = new BinaryTreeNode<Object>(object, this);
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
    root.PrintInOrder(&root);
    cout << endl;
    return 0;
}

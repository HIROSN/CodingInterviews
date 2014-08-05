#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <memory>
using namespace std;


//------------------------------------------------------------------------------
//
//  Post-order binary tree traversal
//
//            [10]
//           /    \
//        [6]      [14]
//        / \      /  \
//      [4] [8]  [12] [16]
//
//  Post-order traversal sequence is 4, 8, 6, 12, 16, 14, 10
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
    BinaryTreeNode<Object>* GetFirst();

    Object m_object;
    BinaryTreeNode<Object>* m_pLeft;
    BinaryTreeNode<Object>* m_pRight;
    BinaryTreeNode<Object>* m_pParent;


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
    BinaryTreeNode<Object>* GetNext();
};


template<class Object>
BinaryTreeNode<Object>* BinaryTreeNode<Object>::GetNext()
{
    if (nullptr == m_pParent)
    {
        return nullptr;
    }

    BinaryTreeNode<Object>* pNext = m_pParent->m_pRight;

    if (nullptr == pNext || this == pNext)
    {
        pNext = m_pParent;
    }
    else
    {
        while (pNext->m_pLeft != nullptr)
        {
            pNext = pNext->m_pLeft;
        }
    }

    return pNext;
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


template<class Object>
BinaryTreeNode<Object>* BinaryTreeNode<Object>::GetFirst()
{
    BinaryTreeNode<Object>* pFirst = this;

    while (pFirst->m_pParent != nullptr)
    {
        pFirst = pFirst->m_pParent;
    }

    while (pFirst->m_pLeft != nullptr)
    {
        pFirst = pFirst->m_pLeft;
    }

    return pFirst;
}


int _tmain(int argc, _TCHAR* argv[])
{
    BinaryTreeNode<int> root(10);
    root.Add(6);
    root.Add(4);
    root.Add(8);
    root.Add(14);
    root.Add(12);
    root.Add(16);
    BinaryTreeNode<int>* pNode = root.GetFirst();

    while (pNode != nullptr)
    {
        cout << pNode->m_object << " ";
        pNode = pNode->GetNext();
    }

    cout << endl;
    return 0;
}

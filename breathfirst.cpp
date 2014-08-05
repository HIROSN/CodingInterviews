#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <memory>
using namespace std;


//------------------------------------------------------------------------------
//
//  Breath-first binary tree traversal
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
//  Breath-first traversal sequence: 10, 4, 16, 2, 8, 12, 18, 6, 14, 20, 24, 22
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
    BinaryTreeNode<Object>* GetFirst(int* pLevel = nullptr);

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

private:
    BinaryTreeNode<Object>* GetNextPreOrder(int* pLevel);
};


template<class Object>
BinaryTreeNode<Object>* BinaryTreeNode<Object>::GetNext()
{
    BinaryTreeNode<Object>* pNext = this;
    int level = 0;

    do {
        pNext = pNext->GetNextPreOrder(&level);
    } while (level != 0 && pNext != nullptr);

    if (nullptr == pNext)
    {
        level = 0;
        pNext = GetFirst(&level);

        do {
            pNext = pNext->GetNextPreOrder(&level);
        } while (level != 1 && pNext != nullptr);
    }

    return pNext;
}


template<class Object>
BinaryTreeNode<Object>* BinaryTreeNode<Object>::GetNextPreOrder(
    int* pLevel)
{
    if (nullptr == pLevel)
    {
        return nullptr;
    }

    if (m_pLeft != nullptr)
    {
        ++*pLevel;
        return m_pLeft;
    }

    if (m_pRight != nullptr)
    {
        ++*pLevel;
        return m_pRight;
    }

    BinaryTreeNode<Object>* pCurrent = this;
    BinaryTreeNode<Object>* pParent = pCurrent->m_pParent;

    while (pParent != nullptr && (
        nullptr == pParent->m_pRight || pCurrent == pParent->m_pRight))
    {
        --*pLevel;
        pCurrent = pParent;
        pParent = pCurrent->m_pParent;
    }

    if (pParent != nullptr)
    {
        return pParent->m_pRight;
    }

    return nullptr;
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
BinaryTreeNode<Object>* BinaryTreeNode<Object>::GetFirst(int* pLevel)
{
    BinaryTreeNode<Object>* pFirst = this;

    while (pFirst->m_pParent != nullptr)
    {
        if (pLevel != nullptr)
        {
            --*pLevel;
        }

        pFirst = pFirst->m_pParent;
    }

    return pFirst;
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
    BinaryTreeNode<int>* pNode = root.GetFirst();

    while (pNode != nullptr)
    {
        cout << pNode->m_object << " ";
        pNode = pNode->GetNext();
    }

    cout << endl;
    return 0;
}

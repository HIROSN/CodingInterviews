#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given a large array of integers where each number appears twice, except for
//  a single entry that appears once, write an algorithm that will return the
//  value of the entry that appears only once.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
class BinarySearchTree
{
public:
    BinarySearchTree() : m_pRoot(nullptr) {}
    ~BinarySearchTree() { Cleanup(m_pRoot); }

    bool Insert(const Object& object) { return Insert(object, m_pRoot); }
    void Remove(const Object& object) { Remove(object, m_pRoot); }

    Object GetRoot()
    {
        return (m_pRoot != nullptr) ? m_pRoot->m_object : Object();
    }

private:
    template<class Object>
    struct TreeNode
    {
        Object m_object;
        TreeNode<Object>* m_pLeft;
        TreeNode<Object>* m_pRight;

        TreeNode(const Object& object)
            : m_object(object), m_pLeft(nullptr), m_pRight(nullptr) {}
    };

private:
    TreeNode<Object>* m_pRoot;

private:
    bool Insert(const Object& object, TreeNode<Object>*& pNode)
    {
        if (nullptr == pNode)
        {
            pNode = new TreeNode<Object>(object);
            return true;
        }

        if (object < pNode->m_object)
        {
            return Insert(object, pNode->m_pLeft);
        }

        if (object > pNode->m_object)
        {
            return Insert(object, pNode->m_pRight);
        }

        return false;
    }

    void Remove(const Object& object, TreeNode<Object>*& pNode)
    {
        if (nullptr == pNode)
        {
            return;
        }

        if (object < pNode->m_object)
        {
            Remove(object, pNode->m_pLeft);
        }
        else if (object > pNode->m_object)
        {
            Remove(object, pNode->m_pRight);
        }
        else if (pNode->m_pLeft != nullptr && pNode->m_pRight != nullptr)
        {
            pNode->m_object = GetMinimum(pNode->m_pRight);
            Remove(pNode->m_object, pNode->m_pRight);
        }
        else
        {
            TreeNode<Object>* pDelete = pNode;

            if (pNode->m_pLeft != nullptr)
            {
                pNode = pNode->m_pLeft;
            }
            else
            {
                pNode = pNode->m_pRight;
            }

            delete pDelete;
        }
    }

    Object GetMinimum(TreeNode<Object>*& pNode)
    {
        if (nullptr == pNode)
        {
            return Object();
        }

        if (pNode->m_pLeft != nullptr)
        {
            return GetMinimum(pNode->m_pLeft);
        }

        return pNode->m_object;
    }

    void Cleanup(TreeNode<Object>*& pNode)
    {
        if (nullptr == pNode)
        {
            return;
        }

        Cleanup(pNode->m_pLeft);
        Cleanup(pNode->m_pRight);
        delete pNode;
        pNode = nullptr;
    }
};


int FindValueAppearsOnce(int array[], int length)
{
    BinarySearchTree<int> bst;

    for (int i = 0; i < length; i++)
    {
        if (!bst.Insert(array[i]))
        {
            bst.Remove(array[i]);
        }
    }

    return bst.GetRoot();
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int array[] = { 4, 1, 2, 3, 5, 6, 7, 4, 1, 2, /*3,*/ 5, 6, 7 };
    cout << FindValueAppearsOnce(array, ARRAYSIZE(array)) << endl;
    return 0;
}

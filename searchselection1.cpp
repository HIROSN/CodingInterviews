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
class TreeNode
{
public:
    int m_value;
    TreeNode* m_pLeft;
    TreeNode* m_pRight;

    TreeNode(int value)
        : m_value(value), m_pLeft(nullptr), m_pRight(nullptr) {}
};


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
void insertOrRemove(int value, TreeNode*& pNode);
void remove(int value, TreeNode*& pNode);
int findMin(TreeNode* pNode);
int cleanup(TreeNode*& pNode);


int findValueAppearsOnce(int array[], int length)
{
    int valueAppearsOnce = -1;
    TreeNode* pNode = nullptr;

    for (int i = 0; i < length; i++)
    {
        insertOrRemove(array[i], pNode);
    }

    if (pNode != nullptr)
    {
        valueAppearsOnce = pNode->m_value;
    }

    if (cleanup(pNode) != 1)
    {
        valueAppearsOnce = -1;
    }

    return valueAppearsOnce;
}


void insertOrRemove(int value, TreeNode*& pNode)
{
    if (nullptr == pNode)
    {
        pNode = new TreeNode(value);
    }
    else if (value < pNode->m_value)
    {
        insertOrRemove(value, pNode->m_pLeft);
    }
    else if (value > pNode->m_value)
    {
        insertOrRemove(value, pNode->m_pRight);
    }
    else
    {
        remove(value, pNode);
    }
}


void remove(int value, TreeNode*& pNode)
{
    if (nullptr == pNode)
    {
        return;
    }

    if (value < pNode->m_value)
    {
        remove(value, pNode->m_pLeft);
    }
    else if (value > pNode->m_value)
    {
        remove(value, pNode->m_pRight);
    }
    else if (pNode->m_pLeft != nullptr && pNode->m_pRight != nullptr)
    {
        pNode->m_value = findMin(pNode->m_pRight);
        remove(pNode->m_value, pNode->m_pRight);
    }
    else
    {
        TreeNode* pDelete = pNode;

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


int findMin(TreeNode* pNode)
{
    if (nullptr == pNode)
    {
        return -1;
    }

    if (pNode->m_pLeft != nullptr)
    {
        return findMin(pNode->m_pLeft);
    }

    return pNode->m_value;
}


int cleanup(TreeNode*& pNode)
{
    int count = 0;

    if (pNode != nullptr)
    {
        count += cleanup(pNode->m_pLeft);
        count += cleanup(pNode->m_pRight);
        delete pNode;
        pNode = nullptr;
        ++count;
    }

    return count;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int array[] = { 4, 1, 2, 3, 5, 6, 7, 4, 1, 2, /*3,*/ 5, 6, 7 };
    cout << findValueAppearsOnce(array, ARRAYSIZE(array)) << endl;
    return 0;
}

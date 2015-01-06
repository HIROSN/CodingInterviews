// {"category": "Tree", "notes": "Check if binary search tree"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------
//
//  Implement a function to check if a binary tree is a binary search tree.
//
//------------------------------------------------------------------------------
class TreeNode
{
public:
    int m_value;
    TreeNode* m_pLeft;
    TreeNode* m_pRight;

    TreeNode(int value, TreeNode* pLeft = nullptr, TreeNode* pRight = nullptr)
        : m_value(value), m_pLeft(pLeft), m_pRight(pRight) {}
};


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
bool IsBST(TreeNode* pNode, int*& pLastValue)
{
    if (nullptr == pNode)
    {
        return true;
    }

    if (!IsBST(pNode->m_pLeft, pLastValue))
    {
        return false;
    }

    if (nullptr == pLastValue)
    {
        pLastValue = new int;
    }
    else if (pNode->m_value <= *pLastValue)
    {
        return false;
    }

    *pLastValue = pNode->m_value;

    if (!IsBST(pNode->m_pRight, pLastValue))
    {
        return false;
    }

    return true;
}


bool IsBST(TreeNode* pNode)
{
    if (nullptr == pNode)
    {
        return false;
    }

    int* pLastValue = nullptr;
    bool isBST = IsBST(pNode, pLastValue);

    if (pLastValue != nullptr)
    {
        delete pLastValue;
    }

    return isBST;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    TreeNode node1(1);
    TreeNode node3(3);
    TreeNode node5(5);
    TreeNode node7(7);
    TreeNode node2(2, &node1, &node3);
    TreeNode node6(6, &node5, &node7);
    TreeNode node4(4, &node2, &node6);
    cout << (IsBST(&node4) ? "TRUE" : "FALSE") << endl;
    node3.m_value = 4;
    cout << (IsBST(&node4) ? "TRUE" : "FALSE") << endl;
    node3.m_value = 3;
    node5.m_value = 4;
    cout << (IsBST(&node4) ? "TRUE" : "FALSE") << endl;
    node5.m_value = 5;
    cout << (IsBST(&node4) ? "TRUE" : "FALSE") << endl;
    return 0;
}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------
//
//  Write code to find the first common ancestor of two nodes in a binary tree.
//
//------------------------------------------------------------------------------
class TreeNode {
public:
    TreeNode* m_pLeft;
    TreeNode* m_pRight;
    int m_value;

    TreeNode(int value)
        : m_value(value), m_pLeft(nullptr), m_pRight(nullptr) {}
};


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
bool findAncestor(
    TreeNode* pCurrent,
    TreeNode* pNode1,
    TreeNode* pNode2,
    TreeNode*& pFound)
{
    if (nullptr == pCurrent || nullptr == pNode1 || nullptr == pNode2)
    {
        pFound = nullptr;
        return false;
    }

    if (pCurrent == pNode1 || pCurrent == pNode2)
    {
        pFound = pCurrent;
        return (pCurrent == pNode1 && pCurrent == pNode2);
    }

    TreeNode* pFoundLeft = nullptr;
    TreeNode* pFoundRight = nullptr;

    if (findAncestor(pCurrent->m_pLeft, pNode1, pNode2, pFoundLeft))
    {
        pFound = pFoundLeft;
        return true;
    }

    if (findAncestor(pCurrent->m_pRight, pNode1, pNode2, pFoundRight))
    {
        pFound = pFoundRight;
        return true;
    }

    if (pFoundLeft != nullptr && pFoundRight != nullptr)
    {
        pFound = pCurrent;
        return true;
    }

    pFound = (pFoundLeft != nullptr) ? pFoundLeft : pFoundRight;
    return false;
}


TreeNode* findAncestor(TreeNode* pRoot, TreeNode* pNode1, TreeNode* pNode2)
{
    TreeNode* pAncestor = nullptr;

    if (!findAncestor(pRoot, pNode1, pNode2, pAncestor))
    {
        return nullptr;
    }

    return pAncestor;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    //            [1]
    //           /   \
    //        [2]     [3]
    //       /   \
    //     [4]   [5]
    //              \
    //              [6]
    //
    TreeNode node1(1), node2(2), node3(3), node4(4), node5(5), node6(6);
    node1.m_pLeft = &node2;
    node1.m_pRight = &node3;
    node2.m_pLeft = &node4;
    node2.m_pRight = &node5;
    node5.m_pRight = &node6;
    cout << findAncestor(&node1, &node3, &node5)->m_value << endl;
    cout << findAncestor(&node1, &node4, &node6)->m_value << endl;
    return 0;
}

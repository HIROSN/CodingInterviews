#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given two lists of node values that represent the pre-order and in-order
//  traversal of a tree, reconstruct the tree from the given data.
//
//------------------------------------------------------------------------------
template<class Object>
class TreeNode
{
public:
    Object m_object;
    TreeNode<Object>* m_pLeft;
    TreeNode<Object>* m_pRight;

    TreeNode(const Object& object) : m_object(object),
        m_pLeft(nullptr), m_pRight(nullptr) {}

    ~TreeNode()
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
};


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
TreeNode<Object>* CreateTree(Object* pPreOrder, Object* pInOrder, int treeSize)
{
    if (nullptr == pPreOrder || nullptr == pInOrder || treeSize <= 0)
    {
        return nullptr;
    }

    int indexRoot = -1;

    for (int i = 0; i < treeSize; i++)
    {
        if (pPreOrder[0] == pInOrder[i])
        {
            indexRoot = i;
            break;
        }
    }

    if (indexRoot < 0)
    {
        return nullptr;
    }

    TreeNode<Object>* pRoot = new TreeNode<Object>(pPreOrder[0]);

    pRoot->m_pLeft = CreateTree(
        pPreOrder + 1,
        pInOrder,
        indexRoot);

    pRoot->m_pRight = CreateTree(
        pPreOrder + indexRoot + 1,
        pInOrder + indexRoot + 1,
        treeSize - indexRoot - 1);

    return pRoot;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
void PreOrder(TreeNode<int>* pRoot, vector<int>* pPreOrder)
{
    if (pRoot != nullptr)
    {
        pPreOrder->push_back(pRoot->m_object);
        PreOrder(pRoot->m_pLeft, pPreOrder);
        PreOrder(pRoot->m_pRight, pPreOrder);
    }
}


void InOrder(TreeNode<int>* pRoot, vector<int>* pInOrder)
{
    if (pRoot != nullptr)
    {
        InOrder(pRoot->m_pLeft, pInOrder);
        pInOrder->push_back(pRoot->m_object);
        InOrder(pRoot->m_pRight, pInOrder);
    }
}


int _tmain(int argc, _TCHAR* argv[])
{
    int preOrder[] = { 10, 4, 2, 8, 6, 16, 12, 14, 18, 20, 24, 22 };
    int inOrder[] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24 };
    TreeNode<int>* pRoot = CreateTree(preOrder, inOrder, ARRAYSIZE(preOrder));

    vector<int> preOrderResult;
    vector<int> inOrderResult;
    PreOrder(pRoot, &preOrderResult);
    InOrder(pRoot, &inOrderResult);

    if (preOrderResult.size() != ARRAYSIZE(preOrder) ||
        inOrderResult.size() != ARRAYSIZE(inOrder) ||
        ARRAYSIZE(preOrder) != ARRAYSIZE(inOrder))
    {
        cout << "FAIL - incorrect size." << endl;
    }
    else
    {
        bool failed = false;

        for (int i = 0; !failed && i < ARRAYSIZE(preOrder); i++)
        {
            if (preOrderResult[i] != preOrder[i] ||
                inOrderResult[i] != inOrder[i])
            {
                cout << "FAIL - incorrect int value." << endl;
                failed = true;
            }
        }

        if (!failed)
        {
            cout << "PASS" << endl;
        }
    }

    delete pRoot;
    return 0;
}

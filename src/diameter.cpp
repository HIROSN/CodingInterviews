// {"category": "Tree", "notes": "Diameter of a tree"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  The diameter of a tree (sometimes called the width) is the number of nodes
//  on the longest path between two leaves in the tree. The diagram below shows
//  two trees with diameter nine.
//
//            [4]                   [n]
//           /   \                 /   \
//        [3]     [5]           [n]     [5]
//        / \     / \           / \     / \
//      [n] [2] [n] [6]       [n] [n] [4] [6]
//          /     \   \                 \   \
//        [1]     [n] [7]               [3] [7]
//                      \               /     \
//                      [8]           [2]     [8]
//                        \             \       \
//                        [9]           [1]     [9]
//
//------------------------------------------------------------------------------
template<class Object>
class TreeNode
{
public:
    Object m_object;
    TreeNode<Object>* m_pLeft;
    TreeNode<Object>* m_pRight;

    TreeNode() : m_object(Object()), m_pLeft(nullptr), m_pRight(nullptr) {}
};


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
int Diameter(TreeNode<Object>* pNode, int& height)
{
    if (nullptr == pNode)
    {
        height = 0;
        return 0;
    }

    int heightLeft = 0;
    int heightRight = 0;

    int diameterLeft = Diameter(pNode->m_pLeft, heightLeft);
    int diameterRight = Diameter(pNode->m_pRight, heightRight);

    height = max(heightLeft, heightRight) + 1;
    int diameter = heightLeft + heightRight + 1;

    return max(diameter, max(diameterLeft, diameterRight));
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    //            [1]                   [1]
    //           /   \                 /   \
    //        [2]     [3]           [2]     [3]
    //        / \     / \           / \     / \
    //      [4] [5] [6] [7]       [4] [5] [6] [7]
    //          /     \   \                 \   \
    //       [12]    [11] [8]              [11] [8]
    //                      \               /     \
    //                      [9]          [12]     [9]
    //                        \             \       \
    //                        [10]          [13]    [10]
    TreeNode<int> n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13;
    n1.m_pLeft = &n2;
    n1.m_pRight = &n3;
    n2.m_pLeft = &n4;
    n2.m_pRight = &n5;
    n3.m_pLeft = &n6;
    n3.m_pRight = &n7;
    n7.m_pRight = &n8;
    n8.m_pRight = &n9;
    n9.m_pRight = &n10;
    n6.m_pRight = &n11;
    n5.m_pLeft = &n12;
    int height = 0;
    cout << Diameter(&n1, height) << endl;
    n5.m_pLeft = nullptr;
    n11.m_pLeft = &n12;
    n12.m_pRight = &n13;
    cout << Diameter(&n1, height) << endl;
    return 0;
}

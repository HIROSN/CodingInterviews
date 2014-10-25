#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------
//
//  Implement a function to check if a linked list is a palindrome.
//
//------------------------------------------------------------------------------
template<class Object>
class ListNode
{
public:
    Object m_object;
    ListNode<Object>* m_pNext;
};


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
bool IsPalindrome(ListNode<Object>*& pHead, ListNode<Object>* pTail)
{
    if (nullptr == pHead || nullptr == pTail)
    {
        return false;
    }

    if (pTail->m_pNext != nullptr)
    {
        if (!IsPalindrome(pHead, pTail->m_pNext))
        {
            return false;
        }
    }

    bool result = (pHead->m_object == pTail->m_object);
    pHead = pHead->m_pNext;
    return result;
}


template<class Object>
bool IsPalindrome(ListNode<Object>* pRoot)
{
    return IsPalindrome(pRoot, pRoot);
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
void printResult(ListNode<char>* pNode)
{
    cout << (IsPalindrome(pNode) ? "Yes : " : "No  : ");

    for (ListNode<char>* p = pNode; p != nullptr; p = p->m_pNext)
    {
        cout << p->m_object << (p->m_pNext ? " -> " : "");
    }

    cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
    ListNode<char> node1, node2, node3, node4, node5;

    node1.m_object = 'a';
    node2.m_object = 'b';
    node3.m_object = 'c';
    node4.m_object = 'b';
    node5.m_object = 'a';
    node1.m_pNext = &node2;
    node2.m_pNext = &node3;
    node3.m_pNext = &node4;
    node4.m_pNext = &node5;
    node5.m_pNext = nullptr;
    printResult(&node1);

    node1.m_object = 'a';
    node2.m_object = 'b';
    node3.m_object = 'b';
    node4.m_object = 'a';
    node1.m_pNext = &node2;
    node2.m_pNext = &node3;
    node3.m_pNext = &node4;
    node4.m_pNext = nullptr;
    printResult(&node1);

    node1.m_object = 'a';
    node2.m_object = 'b';
    node3.m_object = 'c';
    node1.m_pNext = &node2;
    node2.m_pNext = &node3;
    node3.m_pNext = nullptr;
    printResult(&node1);

    node1.m_object = 'a';
    node2.m_object = 'b';
    node3.m_object = 'c';
    node4.m_object = 'a';
    node1.m_pNext = &node2;
    node2.m_pNext = &node3;
    node3.m_pNext = &node4;
    node4.m_pNext = nullptr;
    printResult(&node1);

    node1.m_object = 'a';
    node1.m_pNext = nullptr;
    printResult(&node1);

    node1.m_object = 'a';
    node2.m_object = 'b';
    node1.m_pNext = &node2;
    node2.m_pNext = nullptr;
    printResult(&node1);

    return 0;
}

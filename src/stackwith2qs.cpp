// {"category": "Stack", "notes": "Stack with two queues"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <queue>
using namespace std;


//------------------------------------------------------------------------------
//
//  Please design a stack with two queues and implement the methods to push and
//  pop items.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
class Stack
{
public:
    void Push(const Object& object);
    Object Pop();

private:
    queue<Object> m_queue1;
    queue<Object> m_queue2;
};


template<class Object>
void Stack<Object>::Push(const Object& object)
{
    if (m_queue2.empty())
    {
        m_queue1.push(object);
    }
    else
    {
        m_queue2.push(object);
    }
}


template<class Object>
Object Stack<Object>::Pop()
{
    queue<Object>* pEmptyQueue;
    queue<Object>* pNonEmptyQueue;

    if (m_queue2.empty())
    {
        pEmptyQueue = &m_queue2;
        pNonEmptyQueue = &m_queue1;
    }
    else
    {
        pEmptyQueue = &m_queue1;
        pNonEmptyQueue = &m_queue2;
    }

    if (!pEmptyQueue->empty() ||
        pNonEmptyQueue->empty())
    {
        throw exception();
    }

    while (pNonEmptyQueue->size() > 1)
    {
        pEmptyQueue->push(pNonEmptyQueue->front());
        pNonEmptyQueue->pop();
    }

    Object object = pNonEmptyQueue->front();
    pNonEmptyQueue->pop();
    return object;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    Stack<int> intStack;
    intStack.Push(3);
    intStack.Push(1);
    cout << intStack.Pop() << " ";
    intStack.Push(2);
    cout << intStack.Pop() << " ";
    cout << intStack.Pop() << " ";
    cout << endl;
    return 0;
}

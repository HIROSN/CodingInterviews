// {"category": "Queue", "notes": "Queue with two stacks"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <stack>
using namespace std;


//------------------------------------------------------------------------------
//
//  Please design a queue with two stacks and implement methods to enqueue and
//  dequeue items.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
class Queue
{
public:
    void Enqueue(const Object& object);
    Object Dequeue();

private:
    stack<Object> m_stack1;
    stack<Object> m_stack2;
};


template<class Object>
void Queue<Object>::Enqueue(const Object& object)
{
    m_stack1.push(object);
}


template<class Object>
Object Queue<Object>::Dequeue()
{
    if (m_stack2.empty())
    {
        while (!m_stack1.empty())
        {
            m_stack2.push(m_stack1.top());
            m_stack1.pop();
        }
    }

    if (m_stack2.empty())
    {
        throw exception();
    }

    Object object = m_stack2.top();
    m_stack2.pop();
    return object;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    Queue<int> intQueue;
    intQueue.Enqueue(1);
    intQueue.Enqueue(2);
    cout << intQueue.Dequeue() << " ";
    intQueue.Enqueue(3);
    cout << intQueue.Dequeue() << " ";
    cout << intQueue.Dequeue() << " ";
    cout << endl;

    return 0;
}

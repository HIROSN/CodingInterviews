// {"category": "Queue", "notes": "Priority queue using two queues"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <queue>
using namespace std;


//------------------------------------------------------------------------------
//
//  Implement a priority queue using two queues. A priority queue can always
//  return the next element in the queue with highest priority. Elements can be
//  inserted at any time with any priority.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
class PriorityQueue
{
public:
    PriorityQueue();

    void Enqueue(const Object& object);
    Object Dequeue();

    bool IsEmpty();

private:
    queue<Object> m_queue1;
    queue<Object> m_queue2;
    queue<Object>* m_pQueue1;
    queue<Object>* m_pQueue2;
    Object m_min;
};


template<class Object>
PriorityQueue<Object>::PriorityQueue()
    : m_pQueue1(&m_queue1), m_pQueue2(&m_queue2), m_min(Object())
{
}


template<class Object>
void PriorityQueue<Object>::Enqueue(const Object& object)
{
    if (m_pQueue1->empty() || object < m_min)
    {
        m_pQueue1->push(object);
        m_min = object;
    }
    else
    {
        while (!m_pQueue1->empty())
        {
            Object front = m_pQueue1->front();
            m_pQueue1->pop();

            if (front > object)
            {
                m_pQueue2->push(front);
            }
            else
            {
                m_pQueue2->push(object);
                m_pQueue2->push(front);
                break;
            }
        }

        while (!m_pQueue1->empty())
        {
            m_pQueue2->push(m_pQueue1->front());
            m_pQueue1->pop();
        }

        swap(m_pQueue1, m_pQueue2);
    }
}


template<class Object>
Object PriorityQueue<Object>::Dequeue()
{
    if (m_pQueue1->empty())
    {
        throw exception();
    }

    Object front = m_pQueue1->front();
    m_pQueue1->pop();
    return front;
}


template<class Object>
bool PriorityQueue<Object>::IsEmpty()
{
    return m_pQueue1->empty();
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    PriorityQueue<int> intQueue;
    intQueue.Enqueue(1);
    while (!intQueue.IsEmpty()) cout << intQueue.Dequeue() << " "; cout << endl;
    intQueue.Enqueue(3);
    intQueue.Enqueue(2);
    intQueue.Enqueue(4);
    while (!intQueue.IsEmpty()) cout << intQueue.Dequeue() << " "; cout << endl;
    return 0;
}

// {"category": "Queue", "notes": "Fixed size queue using array"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------
//
//  Write a fixed size queue using an array as the backing store.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
class FixedQueue
{
public:
    FixedQueue(unsigned int size);
    ~FixedQueue();

    void Enqueue(const Object& object);
    Object Dequeue();

    bool IsEmpty();

private:
    Object* m_pObject;
    unsigned int m_size;
    unsigned int m_front;
    unsigned int m_back;
};


template<class Object>
FixedQueue<Object>::FixedQueue(unsigned int size)
    : m_size(size), m_front(0), m_back(0)
{
    if (m_size > 0)
    {
        m_pObject = new Object[m_size];
    }

    if (nullptr == m_pObject)
    {
        throw exception();
    }
}


template<class Object>
FixedQueue<Object>::~FixedQueue()
{
    if (m_pObject != nullptr)
    {
        delete[] m_pObject;
    }
}


template<class Object>
void FixedQueue<Object>::Enqueue(const Object& object)
{
    m_pObject[m_back] = object;
    m_back = (m_back + 1) % m_size;
}


template<class Object>
Object FixedQueue<Object>::Dequeue()
{
    Object object = m_pObject[m_front];

    if (!IsEmpty())
    {
        m_front = (m_front + 1) % m_size;
    }

    return object;
}


template<class Object>
bool FixedQueue<Object>::IsEmpty()
{
    return (m_front == m_back);
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    FixedQueue<int> intQueue(5);
    intQueue.Enqueue(1);
    while (!intQueue.IsEmpty()) cout << intQueue.Dequeue() << " "; cout << endl;
    intQueue.Enqueue(2);
    intQueue.Enqueue(3);
    intQueue.Enqueue(4);
    while (!intQueue.IsEmpty()) cout << intQueue.Dequeue() << " "; cout << endl;
    return 0;
}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Write an array class which allows for an initial size, supports Add, Remove
//  and RemoveAt methods, and automatically grows when you run out of initial
//  space. 
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
class DynamicArray
{
public:
    DynamicArray();
    ~DynamicArray();

    void Add(const Object& object);
    Object Remove();
    Object RemoveAt(unsigned int index);

    unsigned int Count();
    Object& operator[](unsigned int index);

private:
    Object* m_pObject;
    unsigned int m_count;
    unsigned int m_size;
};


template<class Object>
DynamicArray<Object>::DynamicArray()
    : m_pObject(nullptr), m_count(0), m_size(0)
{
}


template<class Object>
DynamicArray<Object>::~DynamicArray()
{
    if (m_pObject != nullptr)
    {
        delete[] m_pObject;
    }
}


template<class Object>
void DynamicArray<Object>::Add(const Object& object)
{
    if (m_count + 1 > m_size)
    {
        unsigned int sizeNew = max(4, m_count + 1);
        sizeNew = max(sizeNew, m_size * 3 / 2);
        Object* pObjectNew = new Object[sizeNew];

        if (m_pObject != nullptr)
        {
            CopyMemory(pObjectNew, m_pObject, sizeof(Object) * m_count);
            delete[] m_pObject;
        }

        m_size = sizeNew;
        m_pObject = pObjectNew;
    }

    m_pObject[m_count++] = object;
}


template<class Object>
Object DynamicArray<Object>::Remove()
{
    if (0 == m_count)
    {
        throw exception();
    }

    return m_pObject[--m_count];
}


template<class Object>
Object DynamicArray<Object>::RemoveAt(unsigned int index)
{
    if (index >= m_count)
    {
        throw exception();
    }

    Object object = m_pObject[index];
    unsigned int countMove = m_count - index - 1;

    if (countMove > 0)
    {
        MoveMemory(
            m_pObject + index,
            m_pObject + index + 1,
            sizeof(Object) * countMove);
    }

    --m_count;
    return object;
}


template<class Object>
unsigned int DynamicArray<Object>::Count()
{
    return m_count;
}


template<class Object>
Object& DynamicArray<Object>::operator[](unsigned int index)
{
    if (index >= m_count)
    {
        throw exception();
    }

    return m_pObject[index];
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
void Print(DynamicArray<int>& intArray)
{
    for (unsigned int i = 0; i < intArray.Count(); i++)
    {
        cout << intArray[i] << " ";
    }

    cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
    DynamicArray<int> intArray;
    intArray.Add(1);
    Print(intArray);
    cout << "removed " << intArray.Remove() << endl;
    intArray.Add(2);
    Print(intArray);
    cout << "removed " << intArray.RemoveAt(0) << endl;
    intArray.Add(3);
    Print(intArray);
    intArray.Add(4);
    intArray.Add(5);
    intArray.Add(6);
    Print(intArray);
    cout << "removed " << intArray.RemoveAt(3) << endl;
    Print(intArray);
    cout << "removed " << intArray.RemoveAt(1) << endl;
    Print(intArray);
    intArray.Add(7);
    intArray.Add(8);
    intArray.Add(9);
    intArray.Add(10);
    Print(intArray);
    return 0;
}

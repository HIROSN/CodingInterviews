#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <queue>
#include <memory>
using namespace std;


//------------------------------------------------------------------------------
//
//  An animal shelter holds only dogs and cats, and operates on a first in
//  first out basis. Create data structures to maintain this system and
//  implement operations enqueue, dequeueAny, dequeueDog and dequeueCat.
//  You may use the built-in LinkedList data structure.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
class Animal
{
public:
    Animal(const char* name) : m_name(name) {}
    virtual string GetKind() { return "Any"; }
    const char* GetName() { return m_name.c_str(); }

protected:
    string m_name;
};


class Dog : public Animal
{
public:
    Dog(const char* name) : Animal(name) {}
    virtual string GetKind() { return "Dog"; }
};


class Cat : public Animal
{
public:
    Cat(const char* name) : Animal(name) {}
    virtual string GetKind() { return "Cat"; }
};


class Shelter
{
public:
    void enqueue(shared_ptr<Dog> dog)
    {
        m_dogQueue.push(dog);
        m_pAnyQueue->push(dog);
    }

    void enqueue(shared_ptr<Cat> cat)
    {
        m_catQueue.push(cat);
        m_pAnyQueue->push(cat);
    }

    shared_ptr<Animal> dequeueAny()
    {
        if (m_pAnyQueue->empty())
        {
            throw exception();
        }

        shared_ptr<Animal> animal = m_pAnyQueue->front();
        m_pAnyQueue->pop();

        if (animal->GetKind() == "Dog")
        {
            m_dogQueue.pop();
        }
        else if (animal->GetKind() == "Cat")
        {
            m_catQueue.pop();
        }
        else
        {
            throw exception();
        }

        return animal;
    }

    shared_ptr<Dog> dequeueDog()
    {
        if (m_dogQueue.empty())
        {
            throw exception();
        }

        shared_ptr<Dog> dog = m_dogQueue.front();
        m_dogQueue.pop();
        dequeueDogOrCat(dog);
        return dog;
    }

    shared_ptr<Cat> dequeueCat()
    {
        if (m_catQueue.empty())
        {
            throw exception();
        }

        shared_ptr<Cat> cat = m_catQueue.front();
        m_catQueue.pop();
        dequeueDogOrCat(cat);
        return cat;
    }

    Shelter()
        : m_pAnyQueue(&m_queue1), m_pEmptyQueue(&m_queue2)
    {
    }

private:
    void dequeueDogOrCat(shared_ptr<Animal> animal)
    {
        while (!m_pAnyQueue->empty())
        {
            if (m_pAnyQueue->front() != animal)
            {
                m_pEmptyQueue->push(m_pAnyQueue->front());
            }

            m_pAnyQueue->pop();
        }

        swap(m_pAnyQueue, m_pEmptyQueue);
    }

private:
    queue<shared_ptr<Dog>> m_dogQueue;
    queue<shared_ptr<Cat>> m_catQueue;
    queue<shared_ptr<Animal>>* m_pAnyQueue;

    queue<shared_ptr<Animal>>* m_pEmptyQueue;
    queue<shared_ptr<Animal>> m_queue1;
    queue<shared_ptr<Animal>> m_queue2;
};


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    Shelter shelter;
    shared_ptr<Dog> dog1 = shared_ptr<Dog>(new Dog("Dog#1 "));
    shared_ptr<Dog> dog2 = shared_ptr<Dog>(new Dog("Dog#2 "));
    shared_ptr<Dog> dog3 = shared_ptr<Dog>(new Dog("Dog#3 "));
    shared_ptr<Cat> cat1 = shared_ptr<Cat>(new Cat("Cat#1 "));
    shared_ptr<Cat> cat2 = shared_ptr<Cat>(new Cat("Cat#2 "));
    shared_ptr<Cat> cat3 = shared_ptr<Cat>(new Cat("Cat#3 "));

    cout << "Enqueue: Dog#1 Cat#1 Cat#2 Dog#2 Cat#3 Dog#3" << endl;
    cout << "Dequeue: Cat   Any   Dog   Cat   Dog   Any" << endl;
    cout << "Results: ";

    shelter.enqueue(dog1);
    shelter.enqueue(cat1);
    shelter.enqueue(cat2);
    cout << shelter.dequeueCat()->GetName();
    cout << shelter.dequeueAny()->GetName();
    shelter.enqueue(dog2);
    shelter.enqueue(cat3);
    cout << shelter.dequeueDog()->GetName();
    cout << shelter.dequeueCat()->GetName();
    shelter.enqueue(dog3);
    cout << shelter.dequeueDog()->GetName();
    cout << shelter.dequeueAny()->GetName();
    cout << endl;

    return 0;
}

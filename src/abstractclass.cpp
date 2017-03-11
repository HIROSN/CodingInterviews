// {"category": "H-1B", "notes": "What is an abstract class"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  What is an abstract class, and why do you need it?
//
//  Source: http://www.bbc.com/news/blogs-trending-39127617
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
/*
    Abstract classes are classes that contain one or more abstract methods. An
    abstract method is a method that is declared, but contains no
    implementation. Abstract classes may not be instantiated, and require
    subclasses to provide implementations for the abstract methods. Let's look
    at an example of an abstract class, and an abstract method.

    Suppose we were modeling the behavior of animals, by creating a class
    hierachy that started with a base class called Animal. Animals are capable
    of doing different things like flying, digging and walking, but there are
    some common operations as well like eating and sleeping. Some common
    operations are performed by all animals, but in a different way as well.
    When an operation is performed in a different way, it is a good candidate
    for an abstract method (forcing subclasses to provide a custom
    implementation). Let's look at a very primitive Animal base class, which
    defines an abstract method for making a sound (such as a dog barking, a cow
    mooing, or a pig oinking).
*/

class Food {};

class Animal
{
    void eat(Food food)
    {
        // do something with food.... 
    }

    void sleep(int hours)
    {
        try
        {
            Sleep(1000 * 60 * 60 * hours);
        }
        catch (exception e)
        {
            /* ignore */
        }
    }

    virtual void makeNoise() = 0;
};


//------------------------------------------------------------------------------
//
//  No demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[]) {}

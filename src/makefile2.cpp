// {"category": "Other", "notes": "Process makefile"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given the following data structure for a makefile entry and support
//  functions, please implement a function to build a target.
//
//------------------------------------------------------------------------------
class Entry
{
public:
    string m_target;
    vector<Entry> m_deps;
    string m_command;

    Entry(
        string target,
        vector<Entry> deps = vector<Entry>(),
        string command = string())
        : m_target(target), m_deps(deps), m_command(command)
    {
    }
};


bool Exists(string target)
{
    return false;
}


void ExecuteCommand(string command)
{
    cout << "Executing " << command.c_str() << "..." << endl;
}


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
void Make(Entry entry)
{
    // Build the target if it does not already exist.
    if (!Exists(entry.m_target))
    {
        // First make all dependencies.
        for (vector<Entry>::size_type i = 0; i < entry.m_deps.size(); i++)
        {
            Make(entry.m_deps[i]);
        }

        // Make this target.
        if (entry.m_command.c_str() != nullptr &&
            strlen(entry.m_command.c_str()) != 0)
        {
            ExecuteCommand(entry.m_command);
        }
    }
}


//------------------------------------------------------------------------------
//
//  Sample data and demo execution.
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    // all: hello
    //
    // hello : main.o factorial.o hello.o
    //          g++ main.o factorial.o hello.o - o hello
    //
    // main.o : main.cpp
    //          g++ - c main.cpp
    //
    // factorial.o : factorial.cpp
    //          g++ - c factorial.cpp
    //
    // hello.o : hello.cpp
    //          g++ - c hello.cpp
    //
    // clean :
    //          rm - rf *o hello
    //
    Entry clean(
        string("clean"),
        vector<Entry>(),
        string("rm -rf *o hello"));

    Entry hello_cpp(string("hello.cpp"));

    vector<Entry> hello_o_deps;
    hello_o_deps.push_back(hello_cpp);

    Entry hello_o(
        string("hello.o"),
        hello_o_deps,
        string("g++ -c hello.cpp"));

    Entry factorial_cpp(string("factorial.cpp"));

    vector<Entry> factorial_o_deps;
    factorial_o_deps.push_back(factorial_cpp);

    Entry factorial_o(
        string("factorial.o"),
        factorial_o_deps,
        string("g++ -c factorial.cpp"));

    Entry main_cpp(string("main.cpp"));

    vector<Entry> main_o_deps;
    main_o_deps.push_back(main_cpp);

    Entry main_o(
        string("main.o"),
        main_o_deps,
        string("g++ -c main.cpp"));

    vector<Entry> hello_deps;

    hello_deps.push_back(main_o);
    hello_deps.push_back(factorial_o);
    hello_deps.push_back(hello_o);

    Entry hello(
        string("hello"),
        hello_deps,
        string("g++ main.o factorial.o hello.o -o hello"));

    vector<Entry> all_deps;
    all_deps.push_back(hello);

    Entry all(string("all"), all_deps);

    Make(all);

    return 0;
}

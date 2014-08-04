#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------
//
//  The declaration of class CMyString is found below. Please add an assignment
//  operator to it.
//
//------------------------------------------------------------------------------
class CMyString
{
public:
    CMyString(char* pData = nullptr);
    CMyString(const CMyString& str);
    ~CMyString();

private:
    char* m_pData;


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
public:
    CMyString& operator=(const CMyString& str);

    const char* c_str() { return m_pData; }
};


CMyString& CMyString::operator=(const CMyString& str)
{
    if (&str != this)
    {
        CMyString temp(str);
        char* pTemp = temp.m_pData;
        temp.m_pData = m_pData;
        m_pData = pTemp;
    }

    return *this;
}


//------------------------------------------------------------------------------
//
//  Unit tests
//
//------------------------------------------------------------------------------
CMyString::CMyString(char* pData)
    : m_pData(nullptr)
{
    if (pData != nullptr)
    {
        m_pData = new char[strlen(pData) + 1];

        if (m_pData != nullptr)
        {
            strcpy(m_pData, pData);
        }
    }
}


CMyString::CMyString(const CMyString& str)
    : m_pData(nullptr)
{
    if (str.m_pData != nullptr)
    {
        m_pData = new char[strlen(str.m_pData) + 1];

        if (m_pData != nullptr)
        {
            strcpy(m_pData, str.m_pData);
        }
    }
}


CMyString::~CMyString()
{
    if (m_pData != nullptr)
    {
        delete[] m_pData;
        m_pData = nullptr;
    }
}


int _tmain(int argc, _TCHAR* argv[])
{
    CMyString nullString;
    CMyString emptyString("");
    CMyString someString("some");

    CMyString str = nullString;
    if (str.c_str() == nullptr)
        cout << "(null)" << endl;
    else
        cout << "\"" << str.c_str() << "\"" << endl;

    str = emptyString;
    cout << "\"" << str.c_str() << "\"" << endl;

    str = someString;
    cout << "\"" << str.c_str() << "\"" << endl;

    return 0;
}

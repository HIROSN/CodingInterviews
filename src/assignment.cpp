// {"category": "Operator", "notes": "Add assignment operator to CMyString"}

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
        swap(m_pData, temp.m_pData);
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
        size_t cch = strlen(pData) + 1;
        m_pData = new char[cch];

        if (m_pData != nullptr)
        {
            if (strcpy_s(m_pData, cch, pData) != 0)
            {
                delete[] m_pData;
                m_pData = nullptr;
            }
        }
    }
}


CMyString::CMyString(const CMyString& str)
    : CMyString(str.m_pData)
{
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

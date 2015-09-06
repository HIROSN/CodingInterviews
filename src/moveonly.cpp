// {"category": "C++11", "notes": "Move only types"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <strsafe.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Move only types
//
//------------------------------------------------------------------------------
class text
{
    char* m_text = nullptr;

public:
    text() = default;

    text(const text&) = delete;
    text& operator=(const text&) = delete;

    text(text&& other) noexcept
    {
        *this = move(other);
    }

    text& operator=(text&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_text;
            m_text = other.m_text;
            other.m_text = nullptr;
        }
        return *this;
    }

    text operator+(const text& other) &&
    {
        size_t size = strlen(*this) + strlen(other) + 1;
        resize(size);
        StringCchCatA(m_text, size, other);
        return move(*this);
    }

    text(_In_opt_ const char* cstring)
    {
        if (cstring != nullptr)
        {
            size_t size = strlen(cstring) + 1;
            resize(size);
            StringCchCopyA(m_text, size, cstring);
        }
    }

    ~text()
    {
        delete[] m_text;
    }

    operator const char*() const
    {
        return (m_text != nullptr) ? m_text : "";
    }

private:
    void resize(size_t size)
    {
        char* cstring = new char[size];
        StringCchCopyA(cstring, size, *this);
        delete m_text;
        m_text = cstring;
    }
};


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    text lValue;
    lValue = text("L-value");
    vector<text> textVector;

    textVector.push_back(text("R-value"));
    textVector.push_back(move(lValue));

    cout << R"(")" << textVector[0] << R"(")" << endl;
    cout << R"(")" << textVector[1] << R"(")" << endl;

    text moved = move(textVector[0]);
    cout << R"(")" << moved << R"(")" << endl;
    cout << R"(")" << textVector[0] << R"(")" << endl;
    cout << R"(")" << textVector[1] << R"(")" << endl;

    lValue = text("hello") + text(", world");
    cout << lValue << endl;
    cout << text("abc") + text("123") << endl;

    return 0;
}

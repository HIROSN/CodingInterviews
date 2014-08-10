#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <queue>
#include <stack>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Design and code a set of structures and methods that can parse an arbitrary
//  CSS selector. A CSS selector will consist of a tag name consisting of mixed
//  case alpha characters which are separated by a matching operator called a
//  "combinator". The combinator can either be a space between adjoining tag
//  names, plus sign '+', or a greater than sign '>'. Extra whitespace can
//  appear between any tokens. Some example selectors are:
//      DIV
//      P
//      DIV P
//      DIV > P
//      DIV   + P
//      DIV+P
//      HTML BODY DIV > P + P
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
class Token
{
public:
    Token(string name) : m_name(name), m_isCombinator(false) {}

    Token(char combinator)
        : m_name(string()), m_isCombinator(true) { m_name = combinator; }

    string GetName() { return m_name; }
    bool IsCombinator() { return m_isCombinator; }
    char GetCombinator() { return (IsCombinator() ? *m_name.c_str() : '\0'); }

    static queue<Token> Parser(char* pString);

private:
    string m_name;
    bool m_isCombinator;

    static const char c_combinators[];
};

// Non-space combinators.
const char Token::c_combinators[] = { '+', '>' };


queue<Token> Token::Parser(char* pString)
{
    if (nullptr == pString)
    {
        throw exception("Input string is null.");
    }

    string input(pString);
    size_t indexToken = 0;
    stack<Token> stack1;

    for (size_t i = 0; i < strlen(pString) + 1; i++)
    {
        char combinator = '\0';

        if (isspace(pString[i]))
        {
            // Space is a combinator.
            combinator = pString[i];
        }
        else
        {
            for (int j = 0; j < ARRAYSIZE(c_combinators); j++)
            {
                if (c_combinators[j] == pString[i])
                {
                    combinator = pString[i];
                    break;
                }
            }
        }

        if ('\0' == pString[i] || combinator != '\0')
        {
            if (i > indexToken)
            {
                Token token(input.substr(indexToken, i - indexToken));
                stack1.push(token);
            }

            indexToken = i + 1;

            if (stack1.empty())
            {
                if (combinator != '\0')
                {
                    if (isspace(combinator))
                    {
                        // Ignore leading space.
                        continue;
                    }

                    throw exception("Starts with a combinator.");
                }

                continue;
            }

            if (stack1.top().IsCombinator())
            {
                if (combinator != '\0' && isspace(combinator))
                {
                    // Ignore extra space.
                    continue;
                }

                if (isspace(stack1.top().GetCombinator()))
                {
                    // Remove trailing space or space before another combinator.
                    stack1.pop();
                }
                else
                {
                    throw exception("Found more than one combinator.");
                }
            }

            if (combinator != '\0')
            {
                if (pString[i + 1] != '\0')
                {
                    stack1.push(Token(combinator));
                }
                else
                {
                    throw exception("Ends with a combinator.");
                }
            }

            continue;
        }

        if ((pString[i] < 'a' || pString[i] > 'z') &&
            (pString[i] < 'A' || pString[i] > 'Z'))
        {
            throw exception("Non-alpha character in tag name.");
        }
    }

    stack<Token> stack2;
    queue<Token> tokenQueue;

    while (!stack1.empty())
    {
        stack2.push(stack1.top());
        stack1.pop();
    }

    while (!stack2.empty())
    {
        tokenQueue.push(stack2.top());
        stack2.pop();
    }

    return tokenQueue;
}


//------------------------------------------------------------------------------
//
//  Unit tests
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    struct TestCase
    {
        char* input;
        char* parsed;
    };

    const TestCase tests[] =
    {
        { "DIV", "DIV" },
        { "P", "P" },
        { "DIV P", "DIV P" },
        { "DIV > P", "DIV>P" },
        { "DIV   + P", "DIV+P" },
        { "DIV+P", "DIV+P" },
        { "HTML BODY DIV > P + P", "HTML BODY DIV>P+P" },
        { nullptr, "Input string is null." },
        { "", "" },
        { "   ", "" },
        { "arbitrarytagname", "arbitrarytagname" },
        { "  div", "div" },
        { "p  ", "p" },
        { "div p", "div p" },
        { "div + p", "div+p" },
        { "div > child", "div>child" },
        { "div + p > ul", "div+p>ul" },
        { "div p + ul > li", "div p+ul>li" },
        { "div+p", "div+p" },
        { "div  +p", "div+p" },
        { " > P", "Starts with a combinator." },
        { "DIV>+P", "Found more than one combinator." },
        { "DIV + > P", "Found more than one combinator." },
        { "DIV-P", "Non-alpha character in tag name." },
        { "DIV - P", "Non-alpha character in tag name." },
        { "HTML BODY DIV+", "Ends with a combinator." },
    };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        string parsed;

        try
        {
            queue<Token> tokenQueue = Token::Parser(tests[i].input);

            while (!tokenQueue.empty())
            {
                parsed += tokenQueue.front().GetName();
                tokenQueue.pop();
            }
        }
        catch (exception e)
        {
            parsed = e.what();
        }

        cout << (parsed == string(tests[i].parsed) ? "PASS: " : "FAILED: ");
        cout << "\"" << (tests[i].input ? tests[i].input : "(null)");
        cout << "\"  =>  \"" << parsed.c_str() << "\"" << endl;
    }

    return 0;
}

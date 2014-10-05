#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <map>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Imagine you have a square matrix, where each cell (pixel) is either black
//  or white. Design an algorithm to find the maximum sub-square such that all
//  four borders are filled with black pixels.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
void FindSquare(HDC hdc, int bitmapSize)
{
    struct RunLength
    {
        WORD right;
        WORD down;
    };

    RunLength** runLength = new RunLength*[bitmapSize];
    RunLength* maxRunLength = new RunLength[bitmapSize];

    for (int i = 0; i < bitmapSize; i++)
    {
        maxRunLength[i].right = 0;
        maxRunLength[i].down = 0;
    }

    for (int x = bitmapSize - 1; x >= 0; x--)
    {
        runLength[x] = new RunLength[bitmapSize];

        for (int y = bitmapSize - 1; y >= 0; y--)
        {
            runLength[x][y].right = 0;
            runLength[x][y].down = 0;

            if (GetPixel(hdc, x, y) == 0)
            {
                runLength[x][y].right = 1;
                runLength[x][y].down = 1;

                if (x < bitmapSize - 1 && GetPixel(hdc, x + 1, y) == 0)
                {
                    runLength[x][y].right += runLength[x + 1][y].right;
                }

                if (y < bitmapSize - 1 && GetPixel(hdc, x, y + 1) == 0)
                {
                    runLength[x][y].down += runLength[x][y + 1].down;
                }

                if (runLength[x][y].right > maxRunLength[y].right)
                {
                    maxRunLength[y].right = runLength[x][y].right;
                }

                if (runLength[x][y].down > maxRunLength[x].down)
                {
                    maxRunLength[x].down = runLength[x][y].down;
                }
            }
        }
    }

    bool found = false;

    for (int squareSize = bitmapSize; !found && squareSize > 0; squareSize--)
    {
        int count = bitmapSize - squareSize + 1;

        for (int top = 0; !found && top < count; top++)
        {
            if (squareSize > maxRunLength[top].right ||
                squareSize > maxRunLength[top + squareSize - 1].right)
            {
                continue;
            }

            for (int left = 0; !found && left < count; left++)
            {
                if (squareSize > maxRunLength[left].down ||
                    squareSize > maxRunLength[left + squareSize - 1].down)
                {
                    continue;
                }

                if (runLength[left][top].right >= squareSize &&
                    runLength[left][top + squareSize - 1].right >= squareSize &&
                    runLength[left][top].down >= squareSize &&
                    runLength[left + squareSize - 1][top].down >= squareSize)
                {
                    cout << "Square size: " << squareSize << " at (";
                    cout << left << ", " << top << ")" << endl;
                    found = true;
                }
            }
        }
    }

    for (int i = 0; i < bitmapSize; i++)
    {
        delete[] runLength[i];
    }

    delete[] runLength;
    delete[] maxRunLength;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    HBITMAP hBitmap = NULL;
    HDC hdcMemory = CreateCompatibleDC(NULL);

    if (argc > 1)
    {
        hBitmap = static_cast<HBITMAP>(LoadImage(
            NULL,
            argv[1],
            IMAGE_BITMAP,
            0,
            0,
            LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE));
    }

    if (hBitmap != NULL)
    {
        BITMAP bm = {};
        GetObject(hBitmap, sizeof(BITMAP), &bm);
        cout << "Image size: " << bm.bmWidth << " x " << bm.bmHeight << endl;
        SelectObject(hdcMemory, hBitmap);
        DWORD start = GetTickCount();

        FindSquare(hdcMemory, min(bm.bmWidth, bm.bmHeight));

        DWORD end = GetTickCount();
        cout << "Elapsed time: " << (end - start) / 1000 << " sec." << endl;
        DeleteObject(hBitmap);
    }

    if (hdcMemory != NULL)
    {
        DeleteDC(hdcMemory);
    }

    return 0;
}

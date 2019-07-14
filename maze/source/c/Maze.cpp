
#include <tchar.h>
#include <windows.h>

#include "App.h"
#include "SimpleWnd.h"
#include "Maze.h"

MazeWin::MazeWin() :
    m_pMazeMatrix(NULL),
    m_isNeedReCalBitmap(true),
    m_pixFix(5),
    m_hBitMap(NULL)
{
}

MazeWin::~MazeWin()
{
    if (m_pMazeMatrix != NULL)
    {
        delete m_pMazeMatrix;
        m_pMazeMatrix = NULL;
    }
}

LRESULT MazeWin::_OnEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    bool isHandle = false;
    LRESULT result = 0;

    switch (msg)
    {
    case WM_PAINT:
        {
            if (m_isNeedReCalBitmap)
            {
                CreateBitmap();
                m_isNeedReCalBitmap = false;
            }

            PAINTSTRUCT ps;
            HDC hdc = ::BeginPaint(hWnd, &ps);
            HBRUSH backBrush = ::CreateSolidBrush(0xffffff);
            RECT backRect = {0, 0, GetWidth(), GetHeight()};
            ::FillRect(hdc, &backRect, backBrush);
            HBRUSH brush = ::CreatePatternBrush(m_hBitMap);
            RECT rect = { 0, 0, (LONG)m_pMazeMatrix->GetCol() * m_pixFix, (LONG)m_pMazeMatrix->GetRow() * m_pixFix };
            ::FillRect(hdc, &rect, brush);
            ::DeleteObject(backBrush);
            ::DeleteObject(brush);
            ::EndPaint(hWnd, &ps);
            isHandle = true;
            break;
        }
    case WM_INITDIALOG:
        {
             if (m_pMazeMatrix == NULL)
            {
                m_pMazeMatrix = new Maze_Matrix();

                if (!m_pMazeMatrix->Init(100, 100))
                {
                    delete m_pMazeMatrix;
                    m_pMazeMatrix = NULL;
                }
            }

            isHandle = true;
            break;
        }
    }

    if (!isHandle)
    {
        return SimpleWnd::_OnEvent(hWnd, msg, wParam, lParam);
    }

    return result;
}

void MazeWin::CreateBitmap()
{
    if (m_pMazeMatrix == NULL)
    {
        return;
    }

    if (m_hBitMap != NULL)
    {
        ::DeleteObject(m_hBitMap);
        m_hBitMap = NULL;
    }

    size_t row = m_pMazeMatrix->GetRow() * m_pixFix;
    size_t col = m_pMazeMatrix->GetCol() * m_pixFix;

    // 根据bitmap的格式，保证是2的倍数
    if (col % 2 != 0)
    {
        col = col / 2 * 2 + 2;
    }

    DWORD* pBuff = new (std::nothrow)DWORD[row * col];
    ::memset(pBuff, 0, row * col * sizeof(DWORD));

    if (pBuff == NULL)
    {
        return;
    }

    for (size_t i = 0; i < m_pMazeMatrix->GetRow(); ++i)
    {
        for (size_t j = 0; j < m_pMazeMatrix->GetCol(); ++j)
        {
            if (m_pMazeMatrix->GetNum(i, j) != 1)
            {
                for (size_t k = i * m_pixFix; k < i * m_pixFix + m_pixFix; ++k)
                {
                    for (size_t t = j * m_pixFix; t < j * m_pixFix + m_pixFix; ++t)
                    {
                        pBuff[k * col + t] = 0xff0000;
                    }
                }
            }
        }
    }

    m_hBitMap = ::CreateBitmap((int)col,
        (int)row,
        1,
        sizeof(DWORD) * 8,
        pBuff);

    ::delete[] pBuff;
}


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR    lpCmdLine, int       nCmdShow)
{
    App* pApp = &GetAppIns();
    pApp->SetIns(hInstance);
    pApp->RegistAllWnd();

    // 主逻辑
    {
        MazeWin mazaWin;
        mazaWin.SetRect({200, 200, 700, 700});
        mazaWin.DoModel();
    }

    pApp->UnRegistAllWnd();
    return 0;
}


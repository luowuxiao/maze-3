
#ifndef _MAZE_H__
#define _MAZE_H__

#include "SimpleWnd.h"
#include "Maze_Matrix.h"

class MazeWin : public SimpleWnd
{
public:
    MazeWin();
    ~MazeWin();

public:
    /** ����window��λ��
    @param [in] rect ����λ��
    */
    inline void SetRect(const RECT& rect)
    {
        SimpleWnd::SetX(rect.left);
        SimpleWnd::SetY(rect.top);
        SimpleWnd::SetWidth(rect.right - rect.left);
        SimpleWnd::SetHeight(rect.bottom - rect.top);
    }

protected:
    virtual LRESULT _OnEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void CreateBitmap();

private:
    /** ��������
    */
    Maze_Matrix* m_pMazeMatrix;

    /** �Ƿ���Ҫ���¼���bitmap����
    */
    bool m_isNeedReCalBitmap;

    /** ����� �����ص����������
    */
    int m_pixFix;

    /** ͼƬ����
    */
    HBITMAP m_hBitMap;
};


#endif // _MAZE_H__

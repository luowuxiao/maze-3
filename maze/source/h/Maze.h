
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
    /** 设置window的位置
    @param [in] rect 窗口位置
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
    /** 矩阵数组
    */
    Maze_Matrix* m_pMazeMatrix;

    /** 是否需要重新计算bitmap缓存
    */
    bool m_isNeedReCalBitmap;

    /** 矩阵点 到像素点的修正倍数
    */
    int m_pixFix;

    /** 图片缓存
    */
    HBITMAP m_hBitMap;
};


#endif // _MAZE_H__

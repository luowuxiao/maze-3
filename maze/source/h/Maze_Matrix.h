
#ifndef _MAZE_MATRIX_H__
#define _MAZE_MATRIX_H__
#include <new>

class Maze_Matrix
{
public:
    /** 构造函数
    */
    Maze_Matrix();
    ~Maze_Matrix();

    /** 初始化m_matrix
    @param [in] rowCount 行数，最小5
    @param [in] colCount 列数，最小5
    @return 是否成功
    */
    bool Init(const size_t rowCount, const size_t colCount);

    /** 生成迷宫
    */
    void GenMaze();

#ifdef _DEBUG
    void PrintMatrix();
#endif // _DEBUG

public:
    /** 获得矩阵行数
    @return 行数
    */
    inline size_t GetRow()
    {
        return m_rowCount;
    }

    /** 获得矩阵列数
    @return 列数
    */
    inline size_t GetCol()
    {
        return m_colCount;
    }

    /** 获得矩阵对应行，列的值
    @param [in] row 行号
    @param [in] col 列号
    @return 对应行，列的值
    */
    inline int GetNum(const size_t row, const size_t col)
    {
        if (row > m_rowCount || col > m_colCount || m_matrix == NULL)
        {
            return -1;
        }

        return (int)m_matrix[row * m_colCount + col];
    }

    /** 设置矩阵对应行，列的值
    @param [in] row 行号
    @param [in] col 列号
    @param [in] value 对应行，列的值
    */
    inline void SetNum(const size_t row, const size_t col, const size_t value)
    {
        if (row > m_rowCount || col > m_colCount || m_matrix == NULL)
        {
            return;
        }

        m_matrix[row * m_colCount + col] = value;
    }

private:
    /** 矩阵行数
    */
    size_t m_rowCount;

    /** 矩阵列数
    */
    size_t m_colCount;

    /** 矩阵数组
    */
    size_t* m_matrix;
};

#endif // _MAZE_MATRIX_H__




#ifndef _MAZE_MATRIX_H__
#define _MAZE_MATRIX_H__
#include <new>

class Maze_Matrix
{
public:
    /** ���캯��
    */
    Maze_Matrix();
    ~Maze_Matrix();

    /** ��ʼ��m_matrix
    @param [in] rowCount ��������С5
    @param [in] colCount ��������С5
    @return �Ƿ�ɹ�
    */
    bool Init(const size_t rowCount, const size_t colCount);

    /** �����Թ�
    */
    void GenMaze();

#ifdef _DEBUG
    void PrintMatrix();
#endif // _DEBUG

public:
    /** ��þ�������
    @return ����
    */
    inline size_t GetRow()
    {
        return m_rowCount;
    }

    /** ��þ�������
    @return ����
    */
    inline size_t GetCol()
    {
        return m_colCount;
    }

    /** ��þ����Ӧ�У��е�ֵ
    @param [in] row �к�
    @param [in] col �к�
    @return ��Ӧ�У��е�ֵ
    */
    inline int GetNum(const size_t row, const size_t col)
    {
        if (row > m_rowCount || col > m_colCount || m_matrix == NULL)
        {
            return -1;
        }

        return (int)m_matrix[row * m_colCount + col];
    }

    /** ���þ����Ӧ�У��е�ֵ
    @param [in] row �к�
    @param [in] col �к�
    @param [in] value ��Ӧ�У��е�ֵ
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
    /** ��������
    */
    size_t m_rowCount;

    /** ��������
    */
    size_t m_colCount;

    /** ��������
    */
    size_t* m_matrix;
};

#endif // _MAZE_MATRIX_H__



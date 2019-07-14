
#include "Maze_Matrix.h"
#include "rand.h"
#include "file_utils.h"
#include <unordered_set>
#include <vector>

Maze_Matrix::Maze_Matrix() :
    m_rowCount(0),
    m_colCount(0),
    m_matrix(NULL)
{
}

Maze_Matrix::~Maze_Matrix()
{
    if (m_matrix != NULL)
    {
        delete []m_matrix;
    }
}

bool Maze_Matrix::Init(const size_t rowCount, const size_t colCount)
{
    if (rowCount < 5 || colCount < 5)
    {
        return false;
    }

    m_rowCount = rowCount;
    m_colCount = colCount;

    if ((m_rowCount & 1) == 0)
    {
        ++m_rowCount;
    }

    if ((m_colCount & 1) == 0)
    {
        ++m_colCount;
    }

    m_matrix = new (std::nothrow) size_t[m_rowCount * m_colCount];

    if (m_matrix == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < m_rowCount; ++i)
    {
        for (size_t j = 0; j < m_colCount; ++j)
        {
            if (i == 0 || i == m_rowCount - 1 || j == 0 || j == m_colCount - 1)
            {
                SetNum(i, j, 1);
                continue;
            }

            // 偶数
            if ((i & 1) != 0 && (j & 1) != 0)
            {
                SetNum(i, j, 0);
            }
            else
            {
                SetNum(i, j, 1);
            }
        }
    }

    GenMaze();

#ifdef _DEBUG
    //PrintMatrix();
#endif // _DEBUG

    return true;
}

void Maze_Matrix::GenMaze()
{
    std::vector<size_t> unVisited;
    std::unordered_set<size_t> visited;

    for (size_t i = 0; i < m_rowCount * m_colCount; ++i)
    {
        if (m_matrix[i] == 0)
        {
            unVisited.push_back(i);
        }
    }

    size_t unVisitedCount = unVisited.size();
    int randNum = 0;
    GetRandNum(0, (int)unVisitedCount - 1, randNum);
    size_t index = unVisited[randNum];
    std::swap(unVisited[randNum], unVisited[unVisitedCount - 1]);
    --unVisitedCount;
    visited.insert(index);

    while (unVisitedCount > 0)
    {
        size_t row = index / m_colCount;
        size_t col = index % m_colCount;
        std::vector<size_t> tmp;

        if (col >= 3 &&
            visited.find(index - 2) == visited.end())
        {
            // 左
            tmp.push_back(0);
        }

        if (col + 3 < m_colCount &&
            visited.find(index + 2) == visited.end())
        {
            // 右
            tmp.push_back(1);
        }

        if (row >= 3 &&
            visited.find(index - m_colCount * 2) == visited.end())
        {
            // 上
            tmp.push_back(2);
        }

        if (row + 3 < m_rowCount  &&
            visited.find(index + m_colCount * 2) == visited.end())
        {
            // 下
            tmp.push_back(3);
        }

        if (tmp.size() > 0)
        {
            int randNumSel = 0;
            GetRandNum(0, (int)tmp.size() - 1, randNumSel);

            switch (tmp[randNumSel])
            {
            case 0:
                {
                    // 左
                    SetNum(row, col - 1, 0);
                    index = index - 2;
                    break;
                }
            case 1:
                {
                    // 右
                    SetNum(row, col + 1, 0);
                    index = index + 2;
                    break;
                }
            case 2:
                {
                    // 上
                    SetNum(row - 1, col, 0);
                    index = index - m_colCount * 2;
                    break;
                }
            case 3:
                {
                    // 下
                    SetNum(row + 1, col, 0);
                    index = index + m_colCount * 2;
                    break;
                }
            }

            for (size_t i = 0; i < unVisitedCount; ++i)
            {
                if (unVisited[i] == index)
                {
                    std::swap(unVisited[i], unVisited[unVisitedCount - 1]);
                    --unVisitedCount;
                    visited.insert(index);
                    break;
                }
            }
        }
        else
        {
            int tmpRand = 0;
            GetRandNum(0, (int)visited.size() - 1, tmpRand);
            size_t i = 0;

            for (auto it : visited)
            {
                if (i == (size_t)tmpRand)
                {
                    index = it;
                    break;
                }

                ++i;
            }
        }
    }
}

#ifdef _DEBUG
void Maze_Matrix::PrintMatrix()
{
    size_t i = 0;
    size_t index = 0;
    wchar_t buff[3] = { L'0', L'\r', L'\n' };
    WriteUCS2FileByBuff(L"C:\\Users\\29976\\Desktop\\a\\1.txt", [&](size_t& size, bool& hasNext)
    {
        const void * rtn = NULL;

        if (i < m_rowCount * m_colCount)
        {
            ++index;

            // wchar 别忘了乘2
            size = 1 * 2;

            if (m_matrix[i] == 1)
            {
                buff[0] = L'1';
            }
            else
            {
                buff[0] = L'0';
            }

            if (index == m_colCount)
            {
                index = 0;
                size = 3 * 2;
            }

            rtn = (const void *)buff;
            hasNext = true;
            ++i;
        }

        return rtn;
    });
}
#endif // _DEBUG


#include <iostream>
#include <vector>
#include "FileReader.h"

class Day04
{
public:
    Day04() {}
    ~Day04() {}

    void readInput(std::string filename)
    {
        FileReader file(filename);
        m_lines = file.getLines();
    }

    bool findWord(int y, int x, int offset_y, int offset_x)
    {

        if (offset_y == -1)
            if (y < m_target.size()-1)
                return false;
        if (offset_y == 1)
            if (y > m_lines.size()-m_target.size())
                return false;
        if (offset_x == -1)
            if (x < m_target.size()-1)
                return false;
        if (offset_x == 1)
            if (x > m_lines[y].size()-m_target.size())
                return false;
        
        for (int i = 0; i < m_target.size(); i++)
            if (m_lines[y + offset_y*i][x + offset_x*i] != m_target[i])
                return false;

        return true;
    }

    int checkCoordinate(int y, int x)
    {
        int xmas = 0;
        xmas += findWord(y, x, -1, -1) ? 1 : 0;
        xmas += findWord(y, x, -1,  0) ? 1 : 0;
        xmas += findWord(y, x, -1,  1) ? 1 : 0;
        xmas += findWord(y, x,  0, -1) ? 1 : 0;
        xmas += findWord(y, x,  0,  1) ? 1 : 0;
        xmas += findWord(y, x,  1, -1) ? 1 : 0;
        xmas += findWord(y, x,  1,  0) ? 1 : 0;
        xmas += findWord(y, x,  1,  1) ? 1 : 0;
        return xmas;
    }

    bool checkXMas(int y, int x)
    {
        if (y <= 0 || y >= m_lines.size()-1)
        {
            return false;
        }
        if (x <= 0 || x >= m_lines[y].size())
        {
            return false;
        }
        
        if (!(m_lines[y-1][x-1] == 'M' && m_lines[y+1][x+1] == 'S'))
        {
            if (!(m_lines[y-1][x-1] == 'S' && m_lines[y+1][x+1] == 'M'))
            {
                return false;
            }
        }

        if (!(m_lines[y+1][x-1] == 'M' && m_lines[y-1][x+1] == 'S'))
        {
            if (!(m_lines[y+1][x-1] == 'S' && m_lines[y-1][x+1] == 'M'))
            {
                return false;
            }
        }

        return true;
    }

    void countXmas()
    {
        int total_xmas = 0;
        int total_x_mas = 0;
        for (int y = 0; y < m_lines.size(); y++)
        {
            for (int x = 0; x < m_lines[y].size(); x++)
            {
                if (m_lines[y][x] == 'X')
                {
                    total_xmas += checkCoordinate(y, x);
                }
                if (m_lines[y][x] == 'A')
                {
                    if (checkXMas(y, x))
                    {
                        total_x_mas++;
                    }
                }
            }
        }
        std::cout << "XMAS: " << total_xmas << std::endl;
        std::cout << "X-MAS: " << total_x_mas << std::endl;
    }

private:
    std::vector<std::string> m_lines;
    std::string m_target = "XMAS";
};

int main()
{
    Day04 day04;
    day04.readInput("04_input.txt");
    day04.countXmas();

    return 0;
}
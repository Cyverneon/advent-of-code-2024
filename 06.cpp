#include <iostream>
#include <vector>
#include <map>
#include "FileReader.h"

struct Direction
{
    enum direction
    {
        up,
        down,
        left,
        right
    };

    direction direction = up;

    std::pair<int, int> getStepOffset()
    {
        if (direction == up)
            return {-1, 0};
        if (direction == down)
            return {1, 0};
        if (direction == left)
            return {0, -1};
        if (direction == right)
            return {0, 1};
        return {-1, 0};
    }

    void rotate()
    {
        switch(direction)
        {
            case up:
                direction = right;
                break;
            case right:
                direction = down;
                break;
            case down:
                direction = left;
                break;
            case left:
                direction = up;
                break;
        } 
    }
};

class Day06
{
public:
    Day06() {}
    ~Day06() {}

    void readInput(std::string filename)
    {
        FileReader file(filename);
        _map = file.getLines();

        for (int y = 0; y < _map.size(); y++)
        {
            for (int x = 0; x < _map.size(); x++)
            {
                if (_map[y][x] == '^')
                {
                    _guard_pos.first = y;
                    _guard_pos.second = x;
                    _map[y].replace(x, 1, 1, 'X');
                }
            }
        }
    }

    bool guardStep()
    {
        std::pair<int, int> target_pos = {_guard_pos.first + _guard_dir.getStepOffset().first, _guard_pos.second + _guard_dir.getStepOffset().second};

        if (target_pos.first < 0 || target_pos.first >= _map.size())
        {
            return false;
        }
        if (target_pos.second < 0 || target_pos.second >= _map[0].size())
        {
            return false;
        }

        if (_map[target_pos.first][target_pos.second] == '#')
        {
            _guard_dir.rotate();
        }
        else
        {
            _guard_pos = target_pos;
            _map[_guard_pos.first].replace(_guard_pos.second, 1, 1, 'X');
        }

        return true;
    }

    void guardPath()
    {
        while(guardStep())
        {
            continue;
        }
    }

    void countGuardVisits()
    {
        int total = 0;
        for (int y = 0; y < _map.size(); y++)
        {
            for (int x = 0; x < _map[y].size(); x++)
            {
                if (_map[y][x] == 'X')
                {
                    total++;
                }
            }
        }
        std::cout << total << std::endl;
    }

    void printMap()
    {
        for (int i = 0; i < _map.size(); i++)
        std::cout << _map[i] << std::endl;
    }

private:
    std::vector<std::string> _map;
    std::pair<int, int> _guard_pos;
    Direction _guard_dir;
};

int main()
{
    Day06 day06;
    day06.readInput("06_input.txt");
    day06.guardPath();
    day06.countGuardVisits();

    return 0;
}
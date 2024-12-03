//https://adventofcode.com/2024/day/3

#include <iostream>
#include <vector>
#include <regex>
#include "FileReader.h"

class Day03
{
public:
    Day03() {}
    ~Day03() {}

    void readInput(std::string filename)
    {
        FileReader file(filename);
        m_memory = file.getLines();  
    }

    int countTotal(std::string regex)
    {
        int total = 0;
        std::regex ex(regex);
        std::smatch match;
        std::string string = "";

        bool enabled = true;
        for (int i = 0; i < m_memory.size(); i++)
        {
            string = m_memory[i];
            while (std::regex_search(string, match, ex))
            {
                if (match.str(0) == "do()")
                {
                    enabled = true;
                }
                else if (match.str(0) == "don't()")
                {
                    enabled = false;
                }
                else if (enabled)
                {
                    int result = stoi(match.str(1)) * stoi(match.str(2));
                    total += result;
                }
                
                string = match.suffix().str();
            }
        }
        
        return total;
    }

    void displayTotals()
    {
        std::cout << "Part 1: " << countTotal(regex_part1) << std::endl;
        std::cout << "Part 2: " << countTotal(regex_part2) << std::endl;
    }

private:
    std::vector<std::string> m_memory;
    std::string regex_part1 = R"(mul\((\d+),(\d+)\))";
    std::string regex_part2 = R"((?:mul\((\d+),(\d+)\))|(?:do\(\))|(?:don't\(\)))";
};

int main()
{
    Day03 day03;
    day03.readInput("03_input.txt");
    day03.displayTotals();

    return 0;
}
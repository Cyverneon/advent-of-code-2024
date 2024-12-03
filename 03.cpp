//https://adventofcode.com/2024/day/3

#include <iostream>
#include <vector>
#include <regex>
#include "FileReader.h"

int main()
{
    FileReader file("03_input.txt");
    std::vector<std::string> memory = file.getLines();    

    int total = 0;
    
    std::regex ex("mul\\((\\d+),(\\d+)\\)");
    std::smatch match;
    std::string string = "";

    for (int i = 0; i < memory.size(); i++)
    {
        string = memory[i];
        while (std::regex_search(string, match, ex))
        {
            int result = stoi(match.str(1)) * stoi(match.str(2));
            total += result;
            //std::cout << "mul() instruction: " << match.str(0) << std::endl;
            //std::cout << "Result: " << result << std::endl;
            string = match.suffix().str();
        }
    }
    
    std::cout << total << std::endl;

    return 0;
}
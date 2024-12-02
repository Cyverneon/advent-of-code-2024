// https://adventofcode.com/2024/day/1

#include <iostream>
#include <vector>
#include "FileReader.h"

int main()
{
    FileReader file("test_input.txt");
    std::vector<std::string> input_lines = file.getLines();

    std::vector<int> list1;
    std::vector<int> list2;

    // input data contains lines of 2 ints separated by spaces
    // find index of first and last space in each line and use them to get ints as substrings
    for (int i = 0; i < input_lines.size(); i++)
    {
        int first_space = input_lines[i].find(" ");
        int last_space = input_lines[i].find_last_of(" ");

        std::string val1 = input_lines[i].substr(0, first_space);
        std::string val2 = input_lines[i].substr(last_space+1);

        list1.push_back(std::stoi(val1));
        list2.push_back(std::stoi(val2));
    }
    return 0;
}
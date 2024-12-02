// https://adventofcode.com/2024/day/1

#include <iostream>
#include <vector>
#include <algorithm>
#include "FileReader.h"

class HistorianHysteria
{
public:
    HistorianHysteria() {}
    ~HistorianHysteria() {}

    void getListsFromInput(std::string filename)
    {
        FileReader file(filename);
        std::vector<std::string> input_lines = file.getLines();

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

        // lists need to be sorted to calculate the total difference
        std::sort(list1.begin(), list1.end());
        std::sort(list2.begin(), list2.end());
    }

    int getTotalDiff()
    {
        int total_diff = 0;
        for (int i = 0; i < list1.size(); i++)
        {
            total_diff += abs(list1[i] - list2[i]);
        }
        return total_diff;
    }

    int getSimilarityScore()
    {
        int similarity_score = 0;
        for (int i = 0; i < list1.size(); i++)
        {
            int multiplier = 0;
            for (int j = 0; j < list2.size(); j++)
            {
                if (list1[i] == list2[j])
                {
                    multiplier++;
                }
            }
            similarity_score += list1[i] * multiplier;
        }
        return similarity_score;
    }

private:
    std::vector<int> list1;
    std::vector<int> list2;
};

int main()
{
    HistorianHysteria historian_hysteria;
    historian_hysteria.getListsFromInput("01_input.txt");
    std::cout << "The total difference is " << historian_hysteria.getTotalDiff() << std::endl;    
    std::cout << "The similarity score is " << historian_hysteria.getSimilarityScore() << std::endl;

    return 0;
}
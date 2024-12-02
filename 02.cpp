// https://adventofcode.com/2024/day/2

#include <iostream>
#include "FileReader.h"

class RedNosedReports
{
public:
    RedNosedReports() {}
    ~RedNosedReports() {}

    void getReports(std::string filename)
    {
        FileReader file(filename);
        m_reports = file.getLines();
    }

    std::vector<int> getReportLevels(int report_index)
    {
        std::string report = m_reports[report_index];
        std::vector<int> levels;

        std::string current_level = "";
        for (int i = 0; i < report.size(); i++)
        {
            if (report.substr(i, 1) == " ")
            {
                if (current_level.size() > 0)
                {
                    levels.push_back(stoi(current_level));
                    current_level = "";
                }
            }
            else
            {
                current_level += report[i];
            }
        }
        if (current_level.size() > 0)
        {
            levels.push_back(stoi(current_level));
        }
        return levels;
    }

    bool checkLevels(std::vector<int> levels)
    {
        // check if first two levels show an increase or decrease to determine which is desired
        bool increasing = levels[1] > levels[0];
        // starts at level at index 1 and loops through comparing with prev level
        for (int i = 1; i < levels.size(); i++)
        {
            // compare if current pair of levels is increasing or decreasing to desired result
            int change = (abs(levels[i] - levels[i-1]));
            if ((levels[i] > levels[i-1]) != increasing)
            {
                return false;
            }
            // and make sure change between levels is between 1 and 3
            if (change < 1 || change > 3)
            {
                return false;
            }
        }
        return true;
    }

    bool getReportSafety(int report_index, bool problem_dampener)
    {
        std::vector<int> levels = getReportLevels(report_index);
        int check = checkLevels(levels);
        if (checkLevels(levels))
        {
            return true;
        }
        else if (problem_dampener)
        {
            // brute force cause prev solution didn't work
            std::vector<int> temp_levels;
            for (int i = 0; i < levels.size(); i++)
            {
                temp_levels = levels;
                temp_levels.erase(temp_levels.begin() + i);
                if (checkLevels(temp_levels))
                {
                    return true;
                }
            }
        }
        return false;
    }

    void countSafeReports()
    {
        // without problem dampening (part 1)
        int safe_reports = 0;
        for (int i = 0; i < m_reports.size(); i++)
        {
            if (getReportSafety(i, false))
            {
                safe_reports++;
            }
        }
        std::cout << "Amount of safe reports: " << safe_reports << std::endl;

        // with problem dampening (part 2)
        safe_reports = 0;
        for (int i = 0; i < m_reports.size(); i++)
        {
            if (getReportSafety(i, true))
            {
                safe_reports++;
            }
        }
        std::cout << "Amount of safe reports with problem dampener: " << safe_reports << std::endl;
    }

private:
    std::vector<std::string> m_reports;
};

int main()
{
    RedNosedReports red_nosed_reports;
    red_nosed_reports.getReports("02_input.txt");
    red_nosed_reports.countSafeReports();

    return 0;
}
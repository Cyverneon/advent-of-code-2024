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

    bool checkReportSafety(int report_index)
    {
        std::vector<int> levels = getReportLevels(report_index);
        // levels must either all be increasing or all be decreasing
        // check if first two levels are increasing or decreasing to establish which we want
        bool increasing = levels[1] > levels[0];
        for (int i = 1; i < levels.size(); i++)
        {
            // compare if current pair of levels is increasing or decreasing to established desired result
            if ((levels[i] > levels[i-1]) != increasing)
            {
                return false;
            }
            int change = (abs(levels[i] - levels[i-1]));
            if (change < 1 || change > 3)
            {
                return false;
            }
        }
        return true;
    }

    int countSafeReports()
    {
        int safe_reports = 0;
        for (int i = 0; i < m_reports.size(); i++)
        {
            if (checkReportSafety(i))
            {
                safe_reports++;
            }
        }
        return safe_reports;
    }

private:
    std::vector<std::string> m_reports;
};

int main()
{
    RedNosedReports red_nosed_reports;
    red_nosed_reports.getReports("02_input.txt");
    std::cout << "Amount of safe reports: " << red_nosed_reports.countSafeReports() << std::endl;

    return 0;
}
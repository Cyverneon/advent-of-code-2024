#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "FileReader.h"

class Day05
{
public:
    Day05() {}
    ~Day05() {}

    std::vector<std::string> split(std::string str, std::string delimiter)
    {
        std::vector<std::string> substrings;
        size_t pos = str.find(delimiter);
        while (pos != std::string::npos)
        {
            substrings.push_back(str.substr(0, pos));
            str.erase(0, pos+delimiter.size());
            pos = str.find(delimiter);;
        }
        substrings.push_back(str);
        return substrings;
    }

    void readInput(std::string filename)
    {
        FileReader file(filename);
        std::vector<std::string> lines = file.getLines();

        bool first_section = true;
        for(int i = 0; i < lines.size(); i++)
        {
            if (lines[i] == "")
            {
                first_section = false;
                continue;
            }
            if (first_section)
            {
                std::vector<std::string> values = split(lines[i], "|");
                if (_after_rules.find(stoi(values[0])) == _after_rules.end())
                    _after_rules.insert({stoi(values[0]), std::set<int>()});
                _after_rules[stoi(values[0])].insert(stoi(values[1]));
                if (_before_rules.find(stoi(values[1])) == _before_rules.end())
                    _before_rules.insert({stoi(values[1]), std::set<int>()});
                _before_rules[stoi(values[1])].insert(stoi(values[0]));
            }
            else
            {
                _updates.push_back(lines[i]);
            }
        }
    }

    bool checkUpdate(std::vector<int> update)
    {
        for (int i = 0; i < update.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (_after_rules[update[i]].find(update[j]) != _after_rules[update[i]].end())
                {
                    return false;
                }
            }
            for (int j = i+1; j < update.size(); j++)
            {
                if (_before_rules[update[i]].find(update[j]) != _before_rules[update[i]].end())
                {
                    return false;
                }
            }
        }
        return true;
    }

    int sumMiddlePages()
    {
        int sum = 0;
        for (int i = 0; i < _updates.size(); i++)
        {
            std::vector<std::string> update_substr = split(_updates[i], ",");
            std::vector<int> update;
            for (int j = 0; j < update_substr.size(); j++)
                update.push_back(stoi(update_substr[j]));

            if (checkUpdate(update))
            {
                sum += update[update.size()/2];
            }
        }
        return sum;
    }

private:
    std::map<int, std::set<int>> _before_rules;
    std::map<int, std::set<int>> _after_rules;

    std::vector<std::string> _updates;
};

int main()
{
    Day05 day05;
    day05.readInput("05_input.txt");
    std::cout << day05.sumMiddlePages() << std::endl;

    return 0;
}
#include "FileReader.h"

FileReader::FileReader(std::string filename)
{
    std::ifstream input;
    input.open(filename);

    if (!input)
    {
        std::cout << "FileReader: Couldn't open input file: \"" << filename << "\".";
    }
    else
    {
        std::string line;
        while (std::getline(input, line))
        {
            m_lines.push_back(line);
        }
    }
}

FileReader::~FileReader() {}

std::vector<std::string> FileReader::getLines()
{
    return m_lines;
}
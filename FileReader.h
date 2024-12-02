#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <iostream>
#include <fstream>

class FileReader
{
public:
    FileReader();
    FileReader(std::string filename);
    ~FileReader();

    std::vector<std::string> getLines();

private:
    std::vector<std::string> m_lines;

};

#endif
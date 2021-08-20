#ifndef INTERPRETER_SERVICE_HPP
#define INTERPRETER_SERVICE_HPP

#include <string>
#include <vector>
#include <fstream>

class InterpreterService 
{
    private:
        std::string filePath;
        std::ifstream file;
        std::vector<std::string> fileText;
        std::string line;
        int rows;
        int cols;
        int foods;
        std::vector<std::string> data;

    public:
        InterpreterService(std::string filePath);
        int getRows();
        int getCols();
        int getFoods();
        std::vector<std::string> getData();
    private:    
        void openFile();
        void closeFile();
        void setFileText();
        void setLine();
        void setData();
        std::vector<int> splitLine(std::string line, std::string delim);
        void setGameValues();

};

#endif
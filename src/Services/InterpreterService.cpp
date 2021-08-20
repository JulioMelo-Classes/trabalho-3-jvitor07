#include "Services/InterpreterService.hpp"

InterpreterService::InterpreterService(std::string filePath) {
    this->filePath = filePath;
    this->openFile();
    this->setFileText();
    this->setLine();
    this->setData();
    this->setGameValues();
}

void InterpreterService::openFile() {
    this->file.open(this->filePath);
}

void InterpreterService::closeFile() {
    this->file.close();
}

void InterpreterService::setFileText() {
    
    while(!this->file.eof())
    {
        std::string line;
        getline(this->file, line);
        this->fileText.push_back(line);
    }

    this->closeFile();
}

void InterpreterService::setLine() {
    this->line = this->fileText.at(0);
}

void InterpreterService::setData() {
    for(auto it = this->fileText.begin() + 1; it != this->fileText.end(); it++) {
        this->data.push_back(*it);
    }
}

std::vector<int> InterpreterService::splitLine(std::string line, std::string delim) {
    std::vector<int> arrValues;
    size_t prev = 0, pos = 0;
    do{
        pos = line.find(delim, prev);
        if (pos == std::string::npos) pos = line.length();
        std::string token = line.substr(prev, pos-prev);
        if (!token.empty()) arrValues.push_back(stoi(token));
        prev = pos + delim.length();
    }while (pos < line.length() && prev < line.length());

    return arrValues;
}

void InterpreterService::setGameValues() {
    std::vector<int> values = this->splitLine(this->line, " ");

    this->rows = values.at(0);
    this->cols = values.at(1);
    this->foods = values.at(2);

}

int InterpreterService::getRows() {
    return this->rows;
}

int InterpreterService::getCols() {
    return this->cols;
}

int InterpreterService::getFoods() {
    return this->foods;
}

std::vector<std::string> InterpreterService::getData() {
    return this->data;
}
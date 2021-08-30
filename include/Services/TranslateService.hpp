#ifndef TRANSLATE_SERVICE_HPP
#define TRANSLATE_SERVICE_HPP

#include<string>
#include <vector>
#include<utility>

class TranslateService
{
    public:
        static std::vector<std::vector<int>> translate(std::pair<int, int> dimensions, std::vector<std::string> maze);
};

#endif
#ifndef SPLIT_LINE_SERVICE_HPP
#define SPLIT_LINE_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <bits/stdc++.h>


class SplitLineService
{
    public:
        static std::map<std::string, int> split(std::string line, char separator);
};

#endif
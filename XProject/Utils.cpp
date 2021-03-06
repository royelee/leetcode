//
//  Utils.cpp
//  XProject
//
//  Created by Roye Li on 11/28/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Utils.h"

using namespace std;

unsigned int factorial(unsigned int n)
{
    unsigned int ret = 1;
    for(unsigned int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

std::string ReadStringFromFile( const std::string& fileName )
{
    std::ifstream myfile(fileName);
    std::string contents((std::istreambuf_iterator<char>(myfile)),
                         std::istreambuf_iterator<char>());
    
    return contents;
}

std::vector<int> ReadIntVectorFromFile( const std::string& fileName )
{
    return ReadVectorFromFile<int>(fileName, [](std::string s) { return stoi(s); });
}

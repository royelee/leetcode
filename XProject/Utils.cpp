//
//  Utils.cpp
//  XProject
//
//  Created by Roye Li on 11/28/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Utils.h"

#include <fstream>
#include <iostream>

using namespace std;

unsigned int factorial(unsigned int n)
{
    unsigned int ret = 1;
    for(unsigned int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

std::vector<int> ReadIntVectorFromFile( const std::string& fileName )
{
    vector<int> v;
    string line;
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while ( getline (myfile,line, ',') )
        {
            v.push_back(stoi(line));
//            cout << line << '\n';
            
        }
        myfile.close();
    }
    
    return v;
}
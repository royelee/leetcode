//
//  Utils.h
//  XProject
//
//  Created by Roye Li on 11/28/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#ifndef __XProject__Utils__
#define __XProject__Utils__

#include <stdio.h>
#include <vector>
#include <functional>

#include <fstream>
#include <iostream>

template <typename T>
std::vector<T> ReadVectorFromFile( const std::string& fileName, const std::function<T(std::string)>& convertFun )
{
    std::vector<T> v;
    std::string line;
    std::ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while ( getline (myfile,line, ',') )
        {
            v.push_back(convertFun(line));
            //            cout << line << '\n';
            
        }
        myfile.close();
    }
    
    return v;
}

std::string ReadStringFromFile( const std::string& fileName );


unsigned int factorial(unsigned int n);
std::vector<int> ReadIntVectorFromFile( const std::string& fileName );


#endif /* defined(__XProject__Utils__) */

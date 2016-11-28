//
//  Level19.cpp
//  XProject
//
//  Created by Roye Li on 11/26/16.
//  Copyright © 2016 Roye Li. All rights reserved.
//

#include <stdio.h>

#include "Level.h"

#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <set>
#include <cmath>
#include <stack>
#include <unordered_set>
#include <queue>
#include <fstream>
#include <unordered_map>

using namespace std;

#pragma mark - isPowerOfTwo
//Given an integer, write a function to determine if it is a power of two.
bool isPowerOfTwo(int n)
{
    if( n<=0 )
        return false;

    int numOfOneBit = 0;
    while( n != 0 )
    {
        if( n & 1 )
            numOfOneBit++;
        
        n = n >> 1;
    }
    
    return numOfOneBit == 1;
}

void testIsPowerOfTwo()
{
    cout << sizeof(int) << endl;
    for( size_t i = 0; i < 100; i++ )
        cout << pow(2,i) << endl;
}

#pragma mark - run

void Level19::Run()
{
    testIsPowerOfTwo();
}
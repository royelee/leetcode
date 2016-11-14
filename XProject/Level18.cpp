//
//  Level18.cpp
//  XProject
//
//  Created by Roye Li on 11/9/16.
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

#pragma mark - maximalSquare
int maxS(vector<vector<char>>& matrix, int row, int col )
{
    if( matrix.size() == 0 )
        return 0;

    size_t rowCount = matrix.size();
    size_t colCount = matrix[0].size();
    if( row >= rowCount || col >= colCount || matrix[row][col] == '0' )
        return 0;
    
    int level = 1;
    queue<pair<int, int>> q;
    q.push(make_pair(row, col));
    while( true )
    {
        set<pair<int, int>> levelSet;
        while( !q.empty() )
        {
            auto current = q.front();
            q.pop();
            
            if( current.first + 1 < rowCount )
                levelSet.insert(make_pair(current.first+1, current.second));
            if( current.second + 1 < colCount )
                levelSet.insert(make_pair(current.first, current.second+1));
            if( current.first + 1 < rowCount && current.second + 1 < colCount )
                levelSet.insert(make_pair(current.first+1, current.second+1));
        }
        
        // Mistake 1 : Not count test case {1}
        // Mistake 2 : Not count test case {1,1}
        if( levelSet.size() != pow(level+1, 2) - pow(level, 2) )
            break;
        
        bool allTrue = true;
        for( auto& p : levelSet )
        {
            if( matrix[p.first][p.second] == '0' )
            {
                allTrue = false;
                break;
            }

            q.push(p);
        }
        
        if( allTrue )
        {
            level++;
        }
        else
            break;
    }
    
    return level;
}

//Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
//
//For example, given the following matrix:
//
//1 0 1 0 0
//1 0 1 1 1
//1 1 1 1 1
//1 0 0 1 0
//Return 4.
int maximalSquare(vector<vector<char>>& matrix)
{
    int rtn = 0;
    for( size_t row = 0; row < matrix.size(); row++ )
    {
        for( size_t col = 0; col < matrix[row].size(); col++ )
        {
            int v = maxS(matrix, (int)row, (int)col);
            if( v > 0 )
                rtn = max(v*v, rtn);
        }
    }
    return rtn;
}

void TestMaximalSquare()
{
    vector<string> m1 = {
        "1 0 1 0 0",
        "1 0 1 1 1",
        "1 1 1 1 1",
        "1 0 0 1 0"
    };
    vector<string> m2 = {
        "1"
    };
    vector<string> m3 = {
        "11"
    };
    vector<string> m4 = {
        {"1111","1111","1111"}
    };
    
    vector<vector<char>> tests;
    for( auto& s : m4 )
    {
        vector<char> vC;
        for( auto& c : s )
        {
            if( c == '1' || c == '0' )
                vC.push_back(c);
        }
        tests.push_back(vC);
    }
    cout << maximalSquare(tests);
}

#pragma mark - run

void Level18::Run()
{
    TestMaximalSquare();
}
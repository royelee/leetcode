//
//  Level6.cpp
//  XProject
//
//  Created by Roye Li on 11/13/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Level6.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <set>
#include <cmath>

using namespace std;

#pragma mark - minPathSum

//Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
//
//Note: You can only move either down or right at any point in time.
int minPathSum(vector<vector<int>>& grid)
{
    vector<vector<int>> dp( grid.size(), vector<int>( grid[0].size() ) );
    for( int i = dp.size() - 1; i >= 0; i-- )
    {
        for( int j = dp[i].size() - 1; j >= 0; j-- )
        {
            if( i == dp.size() - 1 )
            {
                if( j == dp[i].size() - 1 )
                    dp[i][j] = grid[i][j];
                else
                    dp[i][j] = dp[i][j+1] + grid[i][j];
            }
            else if( j == dp[i].size() - 1 )
            {
                dp[i][j] = dp[i+1][j] + grid[i][j];
            }
            else
            {
                dp[i][j] = min(dp[i+1][j], dp[i][j+1]) + grid[i][j];
            }
        }
    }
    
    return dp[0][0];
}

void testMinPathSum()
{
    vector<vector<vector<int>>> grids =
    {
//        {
//            {0}
//        },
//        {
//            {0, 0, 1}
//        },
//        {
//            {0},
//            {0},
//            {1}
//        },
//        {
//            {0, 1},
//            {1, 0}
//        },
//        {
//            {0, 0},
//            {1, 0}
//        },
//        {
//            {0, 1},
//            {0, 0}
//        },
//        {
//            {0, 0, 1},
//            {1, 0, 0},
//            {0, 1, 0}
//        },
//        {
//            {0, 1, 100},
//            {100, 100, 0},
//            {0, 0, 0}
//        }
        {
            {7,0,8,8,0,3,5,8,5,4},
            {4,1,2,9,9,6,0,8,6,9},
            {9,7,1,1,0,1,2,4,1,7}
        }
    };
    
    for( auto& grid : grids )
    {
        cout << minPathSum(grid) << endl;
    }
}

#pragma mark - plusOne

//Given a non-negative number represented as an array of digits, plus one to the number.
//
//The digits are stored such that the most significant digit is at the head of the list.
vector<int> plusOne(vector<int>& digits)
{
    vector<int> output = digits;
    bool addOne = true;
    for( int i = digits.size() - 1; i >= 0; i-- )
    {
        if( addOne )
        {
            if( digits[i] == 9 )
            {
                output[i] = 0;
            }
            else
            {
                addOne = false;
                output[i] = digits[i] + 1;
            }
        }
    }
    
    if( addOne )
        output.insert(output.begin(), 1);
    
    return output;
}

#pragma mark - addBinary
//Given two binary strings, return their sum (also a binary string).
//
//For example,
//a = "11"
//b = "1"
//Return "100".
string addBinary(string a, string b)
{
    bool addOne = false;
    string output;
    size_t length = max( a.size(), b.size() );
    for( int i = 0; i < length; i++ )
    {
        int number = 0;
        if( 1 + i <= a.size() )
            number += (a[a.size() - 1 - i] - '0');
        if( 1 + i <= b.size() )
            number += (b[b.size() - 1 - i] - '0');
        if( addOne )
            number++;
        
        output.insert(output.begin(), number % 2 == 1 ? '1' : '0' );
        addOne = number > 1;
    }
    
    if( addOne )
    {
        output.insert(output.begin(), '1');
    }
    
    return output;
}

void testAddBinary()
{
    cout << addBinary("11", "11");
}

#pragma mark - mySqrt
//implement int sqrt(int x).
//
//Compute and return the square root of x.
int mySqrt(int x)
{
    // https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
    if( x <= 0 )
        return 0;
    
    // init guess use highest bit 2^2n of x
    int bit = 0;
    int t = x;
    while( t > 0 )
    {
        t = t >> 1;
        bit++;
    }
    
    // x(n+1) = 1/2 * ( x(n) + s/x(n) )
    double pre = 1 << bit/2;
    double next = pre;
    do {
        pre = next;
        next = ( pre + x / pre ) / 2.0;
    } while( pre != next );
    
    return next;
}

void testMySqrt()
{
    for( int i = 0; i < 100; i++ )
    {
        cout << i << " : my -> " << mySqrt(i) << " correct ->" << floor(sqrt(i)) << endl;
    }
}

#pragma mark - climbStairs
//You are climbing a stair case. It takes n steps to reach to the top.
//
//Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
int climbStairs(int n)
{
    // 5 -> 1, 2, 3, 4, 5 | 1, 2, 3, 5 | 1, 3, 4, 5| 1, 3, 5 | 2, 3, 4, 5| 2, 3, 5| 2, 4, 5 --- 7
    // 4 -> 1, 2, 3, 4 | 1, 2, 4 | 1, 3, 4 | 2, 3, 4 | 2, 4 --- 4
    // 3 -> 1, 2, 3 | 1, 3 | 2, 3 --- 3
    // 2 -> 1, 2 | 2 --- 2
    // 1 -> 1 --- 1
    vector<int> output( 2 );
    output[0] = 1;
    output[1] = 2;
    
    if( n < 0 )
        return 0;
    if( n < 2 )
        return output[n - 1];
    
    for( int i = 0; i < n - 2; i++ )
    {
        int tmp = output[0] + output[1];
        output[0] = output[1];
        output[1] = tmp;
    }
    
    return output[1];
}


#pragma mark - simplifyPath

//Given an absolute path for a file (Unix-style), simplify it.
//
//For example,
//path = "/home/", => "/home"
//path = "/a/./b/../../c/", => "/c"
//
//Corner Cases:
//Did you consider the case where path = "/../"?
//In this case, you should return "/".
//Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
//In this case, you should ignore redundant slashes and return "/home/foo".
string simplifyPath(string path)
{
    // split the string by '/' and store it into array.
    vector<string> elements;
    stringstream ss(path);
    string tmp;
    while (getline(ss, tmp, '/')) {
        if( !tmp.empty() )
            elements.push_back(tmp);
    }
    
    vector<string> final;
    for( int i = 0; i < elements.size(); i++ )
    {
        if( elements[i] == ".." )
        {
            if( !final.empty() )
            {
                final.pop_back();
            }
        }
        else if( elements[i] != "." )
        {
            final.push_back( elements[i] );
        }
    }
    
    if( final.empty() )
    {
        return "/";
    }
    else
    {
        stringstream ss;
        for( auto& e : final )
        {
            ss << "/" << e;
        }
        
        return ss.str();
    }
}

void testSimplifyPath()
{
    vector<pair<string, string>> tests =
    {
        {"/home//foo/", "/home/foo"},
        {"/home/", "/home"},
        {"/a/./b/../../c/", "/c"},
        {"/../", "/"}
    };
    
    for( auto& p : tests )
    {
        cout << (simplifyPath(p.first) == p.second) << endl;
    }
}

#pragma mark - setZeroes
//Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
//
// Follow up:
//Did you use extra space?
//A straight forward solution using O(mn) space is probably a bad idea.
//A simple improvement uses O(m + n) space, but still not the best solution.
//Could you devise a constant space solution?
void setZeroes(vector<vector<int>>& matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();
    
    vector<bool> f( n );
    
    for( int i = 0; i < m; i++ )
    {
        bool currentLineHasZero = false;
        for( int j = 0; j < n; j++ )
        {
            if( matrix[i][j] == 0 )
            {
                if( !currentLineHasZero )
                {
                    for( int t = 0; t <= j; t++ )
                    {
                        matrix[i][t] = 0;
                    }
                    
                    currentLineHasZero = true;
                }
                
                if( !f[j] )
                {
                    for( int t = 0; t <= i; t++ )
                    {
                        matrix[t][j] = 0;
                    }
                    
                    f[j] = true;
                }
            }
            else if( f[j] || currentLineHasZero )
            {
                matrix[i][j] = 0;
            }
        }
    }
}

void testSetZeroes()
{
    vector<vector<int>> m = {
        { 1, 2, 3, 4 },
        { 1, 2, 0, 4 },
        { 0, 2, 3, 4 },
        { 1, 2, 3, 4 },
    };
    setZeroes( m );
    
    for( auto& v : m )
    {
        for( auto& i : v )
        {
            cout << i << " ";
        }
        
        cout << endl;
    }
}

void setZeroes1(vector<vector<int> > &matrix) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int row = matrix.size(), col = matrix[0].size();
    bool zerorow=false, zerocol=false;
    for(int i = 0; i< col; i++)
        if(matrix[0][i] ==0)
            zerorow = 1;
    for(int i = 0; i< row; i++)
        if(matrix[i][0] ==0)
            zerocol=1;
    for(int i =1; i < row; i++)
        for(int j = 1; j<col; j++)
            if(matrix[i][j] ==0)
            {
                matrix[0][j] =0;
                matrix[i][0] =0;
            }
    for(int i =1; i < row; i++)
        for(int j = 1; j<col; j++)
            if(matrix[i][0] ==0 || matrix[0][j] ==0)
                matrix[i][j] =0;
    if(zerorow ==1)
        for(int i =0; i< col; i++)
            matrix[0][i] =0;
    if(zerocol==1)
        for(int i =0; i< row; i++)
            matrix[i][0] =0;
}


#pragma mark - run

void Level6::Run()
{
    testSetZeroes();
}
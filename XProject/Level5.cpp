//
//  Level5.cpp
//  XProject
//
//  Created by Roye Li on 10/16/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Level5.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <set>
#include <cmath>

using namespace std;


#pragma mark - maxSubArray
//
//Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
//
//For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
//the contiguous subarray [4,−1,2,1] has the largest sum = 6.
int maxSubArray(vector<int>& nums)
{
    size_t size = nums.size();
    if( size == 1 )
        return nums[0];
    
    vector<int> dp( size );
    dp[size - 1] = nums[size - 1];
    
    int maxR = dp[size - 1];
    for( int i = size - 2; i >= 0; i-- )
    {
        dp[i] = max( nums[i] + dp[i + 1], nums[i] );
        maxR = max( dp[i], maxR );
    }
    
    return maxR;
}

void testMaxSubArray()
{
    vector<int> t {-2,1,-3,4,-1,2,1,-5,4};
    cout << maxSubArray(t) << endl;
}

#pragma mark - spiralOrder

//Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
//
//For example,
//Given the following matrix:
//
//[
// [ 1, 2, 3 ],
// [ 4, 5, 6 ],
// [ 7, 8, 9 ]
// ]
//You should return [1,2,3,6,9,8,7,4,5].
vector<int> spiralOrder(vector<vector<int>>& matrix)
{
    vector<int> r;
    
    int sizeH = matrix.size();
    if( sizeH == 0 )
        return r;
    
    int sizeW = matrix[0].size();
    if( sizeW == 0 )
        return r;
    
    struct Point
    {
        int x;
        int y;
    };
    
    Point start{ 0, 0 };
    Point innerSize { sizeW, sizeH };
    int n = (min( sizeW, sizeH ) - 1 )/ 2;
    for( int i = 0; i <= n; i++ )
    {
        Point current = start;
        r.push_back(matrix[current.y][current.x]);
        
        // Go right
        while( current.x + 1 < start.x + innerSize.x )
        {
            current.x++;
            r.push_back(matrix[current.y][current.x]);
        }
        
        // Go down
        bool goDown = false;
        while( current.y + 1 < start.y + innerSize.y )
        {
            goDown = true;
            current.y++;
            r.push_back(matrix[current.y][current.x]);
        }
        
        // Go left
        bool goLeft = false;
        while( goDown && current.x - 1 >= start.x )
        {
            goLeft = true;
            current.x--;
            r.push_back(matrix[current.y][current.x]);
        }
        
        // Go Up
        while( goLeft && current.y - 1 > start.y )
        {
            current.y--;
            r.push_back(matrix[current.y][current.x]);
        }
        
        start.x += 1;
        start.y += 1;
        innerSize.x -= 2;
        innerSize.y -= 2;
    }
    
    return r;
}

void testSpiralOrder()
{
    vector< vector<vector<int>>> ms =
    {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        },
        {
            {1, 2},
            {3, 4},
            {5, 6}
        },
        {
            {1, 2, 3},
            {4, 5, 6}
        },
        {
            {1, 2, 3}
        },
        {
            {1},
            {2},
            {3}
        }
    };
    
    for( auto& m : ms )
    {
        vector<int> r = spiralOrder( m );
        
        for( int& i : r )
        {
            cout << i << " ";
        }
        cout << endl;
    }
}

#pragma mark - canJump
//Given an array of non-negative integers, you are initially positioned at the first index of the array.
//
//Each element in the array represents your maximum jump length at that position.
//
//Determine if you are able to reach the last index.
//
//For example:
//A = [2,3,1,1,4], return true.
//
//A = [3,2,1,0,4], return false.
bool canJump(vector<int>& nums)
{
    if( nums.size() == 0 )
        return false;
    
//    vector< bool > possibles( nums.size(), false );
//    possibles[0] = true;
//    for( int i = 0; i < nums.size(); i++ )
//    {
//        if( possibles[i] )
//        {
//            for( int j = 1; j <= nums[i]; j++ )
//            {
//                if( i + j < nums.size() )
//                {
//                    possibles[i+j] = true;
//                    if( nums[i+j] <= nums[i] - j )
//                    {
//                        nums[i+j] = 0;
//                    }
//                }
//            }
//        }
//    }
//
//    return possibles[nums.size() - 1];
    
    int maxIndex = 0;
    for(int i=0; i<nums.size(); i++) {
        if(i>maxIndex || maxIndex>=(nums.size()-1)) break;
        maxIndex = max(maxIndex, i+nums[i]);
    }
    return maxIndex>=(nums.size()-1) ? true : false;
}

void testCanJump()
{
    vector< vector< int > > tests =
    {
        { 3,3,1,0,4 },
        { 2,3,1,1,4 },
        {2,0,6,9,8,4,5,0,8,9,1,2,9,6,8,8,0,6,3,1,2,2,1,2,6,5,3,1,2,2,6,4,2,4,3,0,0,0,3,8,2,4,0,1,2,0,1,4,6,5,8,0,7,9,3,4,6,6,5,8,9,3,4,3,7,0,4,9,0,9,8,4,3,0,7,7,1,9,1,9,4,9,0,1,9,5,7,7,1,5,8,2,8,2,6,8,2,2,7,5,1,7,9,6},
        { 3,2,1,0,4 },
        { },
        { 1 },
        { 0, 1 },
        { 1, 0 }
    };
    
    for( vector< int >& v : tests )
    {
        cout << ( canJump( v ) ? "true" : "false" ) << endl;
    }
}

#pragma mark - lengthOfLastWord

//Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
//
//If the last word does not exist, return 0.
//
//Note: A word is defined as a character sequence consists of non-space characters only.
//
//For example,
//Given s = "Hello World",
//return 5.
int lengthOfLastWord(string s)
{
    stringstream ss;
    string stack;
    for( int i = 0; i < s.size(); i++ )
    {
        if( s[i] != ' ' )
        {
            ss << s[i];
        }
        else
        {
            string l = ss.str();
            if( l.size() > 0 )
                stack = ss.str();

            ss.str("");
        }
    }
    
    string end = ss.str();
    return end.empty() ? stack.size() : end.size();
}

void testLengthOfLastWord()
{
    string s = "Hello World";
    cout << lengthOfLastWord(s) << endl;
    
    // failed
    s = "a ";
    cout << lengthOfLastWord(s) << endl;
    
    s = "b   a    ";
    cout << lengthOfLastWord(s) << endl;
}

#pragma mark - generateMatrix

//Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
//
//For example,
//Given n = 3,
//
//You should return the following matrix:
//[
// [ 1, 2, 3 ],
// [ 8, 9, 4 ],
// [ 7, 6, 5 ]
// ]
vector<vector<int>> generateMatrix(int n)
{
    vector<vector<int>> output(n, vector<int>(n) );
    int fill = 1;
    for( int start = 0; start < ( n + 1 ) / 2; start++ )
    {
        int end = n - start - 1;
        // go right
        for( int t = start; t <= end; t++ )
        {
            output[start][t] = fill++;
        }
        
        // go down
        for( int t = start + 1; t <= end; t++ )
        {
            output[t][end] = fill++;
        }
        
        // go left
        for( int t = end - 1; t >= start; t-- )
        {
            output[end][t] = fill++;
        }
        
        // go up
        for( int t = end - 1; t > start; t-- )
        {
            output[t][start] = fill++;
        }
    }

    return output;
}

void testGenerateMatrix()
{
    vector<vector<int>> output = generateMatrix(5);
    for( auto& v : output )
    {
        for( auto& i : v )
        {
            cout << i << " ";
        }
        
        cout << endl;
    }
}

#pragma mark - getPermutation

bool getNextPermutation( string& current )
{
    int first = -1;
    for( int i = 0; i < current.size() - 1; i++ )
    {
        if( current[i] < current[i+1] )
        {
            first = i;
        }
    }
    
    if( first == -1 )
        return false;
    
    int nextMax = first + 1;
    for( int i = first + 1; i < current.size(); i++ )
    {
        if( current[i] > current[first] )
            nextMax = i;
    }
    
    swap(current[first], current[nextMax]);
    
    int begin = first + 1;
    int end = current.size() - 1;
    while( begin < end )
    {
        swap( current[begin], current[end] );
        begin++;
        end--;
    }
    
    return true;
}

//The set [1,2,3,…,n] contains a total of n! unique permutations.
//
//By listing and labeling all of the permutations in order,
//We get the following sequence (ie, for n = 3):
//
//"123"
//"132"
//"213"
//"231"
//"312"
//"321"
//Given n and k, return the kth permutation sequence.
//
//Note: Given n will be between 1 and 9 inclusive.
string getPermutation(int n, int k)
{
    string output;
    if( n < 1 || n > 9 )
        return output;
    
    int max = 1;
    for( int i = 1; i <= n; i++ )
    {
        max *= i;
    }
    
    if( k > max || k <= 0 )
        return output;
    
    for( int i = 1; i <= n; i++ )
    {
        output.push_back( '0' + i );
    }
    
    int cout = 1;
    while( cout++ != k )
    {
        getNextPermutation( output );
    }
    
    return output;
}

void testGetNextPermutation()
{
    for( int i = 1; i < 7; i++ )
    {
        cout << getPermutation(5, i) << endl;
    }
}

#pragma mark - run

void Level5::Run()
{
    testGetNextPermutation();
}
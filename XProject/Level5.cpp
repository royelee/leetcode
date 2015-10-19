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

#pragma mark - run

void Level5::Run()
{
    testSpiralOrder();
}
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

class Node
{
public:
    int v;
    vector< Node* > nexts;
};

bool _canJump( Node* node, int expect )
{
    if( node == nullptr )
        return false;
    
    if( node->v == expect )
        return true;
    
    for( Node* subNodes : node->nexts )
    {
        if( _canJump( subNodes, expect ) )
            return true;
    }
    
    return false;
}

bool canJump(vector<int>& nums)
{
    if( nums.size() == 0 )
        return false;
    
    vector< unique_ptr< Node > > nodes;
    for( int i = 0; i < nums.size(); i++ )
    {
        unique_ptr< Node > node( new Node );
        node->v = i;
        nodes.push_back( std::move( node ) );
    }
    
    for( int i = 0; i < nums.size(); i++ )
    {
        vector< weak_ptr< Node > > nexts;
        for( int j = 0; j < nums[i]; j++ )
        {
            if( i + j + 1 < nums.size() )
            {
                nodes[i]->nexts.push_back( nodes[ i + j + 1 ].get() );
            }
        }
    }


    return _canJump( nodes[0].get(), nums.size() - 1 );
}

void testCanJump()
{
    vector< vector< int > > tests =
    {
        {2,0,6,9,8,4,5,0,8,9,1,2,9,6,8,8,0,6,3,1,2,2,1,2,6,5,3,1,2,2,6,4,2,4,3,0,0,0,3,8,2,4,0,1,2,0,1,4,6,5,8,0,7,9,3,4,6,6,5,8,9,3,4,3,7,0,4,9,0,9,8,4,3,0,7,7,1,9,1,9,4,9,0,1,9,5,7,7,1,5,8,2,8,2,6,8,2,2,7,5,1,7,9,6},
        { 3,2,1,0,4 },
        { 2,3,1,1,4 },
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

#pragma mark - run

void Level5::Run()
{
    testCanJump();
}
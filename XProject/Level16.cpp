//
//  Level16.cpp
//  XProject
//
//  Created by Roye Li on 10/17/16.
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

using namespace std;

#pragma mark - hammingWeight
//Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).
//
//For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, so the function should return 3.
int hammingWeight(uint32_t n)
{
    int count = 0;
    while( n > 0 )
    {
        if( ( n & 1 ) == 1 )
            count++;
        
        n = n >> 1;
    }
    
    return count;
}

void testHammingWeight()
{
    uint32_t t = 0b1011;
    cout << hammingWeight(t);
}

#pragma mark - rob
//You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
//
//Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
int rob(vector<int>& nums)
{
    if( nums.size() == 0 )
        return 0;
    else if( nums.size() == 1 )
        return nums[0];

    vector<int> dp(nums.size());
    dp[0] = nums[0];
    dp[1] = max( dp[0], nums[1] );
    for( size_t i = 2; i < nums.size(); i++ )
    {
        dp[i] = max( dp[i-1], dp[i-2] + nums[i] );
    }
    
    return dp.back();
}

void testRob()
{
    vector<int> t = {183,219,57,193,94,233,202,154,65,240,97,234,100,249,186,66,90,238,168,128,177,235,50,81,185,165,217,207,88,80,112,78,135,62,228,247,211};
    cout << rob(t);
}

#pragma mark - rightSideView
//Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
//
//For example:
//Given the following binary tree,
//   1            <---
// /   \
//2     3         <---
// \     \
//  5     4       <---
//You should return [1, 3, 4].
vector<int> rightSideView(TreeNode* root)
{
    struct LevelTreeNode
    {
        TreeNode* node{ nullptr };
        int level{ -1 };
        LevelTreeNode( TreeNode* n, int l ) : node( n ), level( l ) {}
    };
    
    queue<LevelTreeNode> q;
    q.push( { root, 1 } );
    
    vector<int> out;
    TreeNode* lastVisited = nullptr;
    int currentLevel = 1;
    while( !q.empty() )
    {
        LevelTreeNode tmp = q.front();
        q.pop();
        if( tmp.node != nullptr )
        {
            if( tmp.node->left )
                q.push( { tmp.node->left, tmp.level + 1 } );
            
            if( tmp.node->right )
                q.push( { tmp.node->right, tmp.level + 1 } );
        }
        
        if( tmp.level != currentLevel )
        {
            // Go into next level, now last visit is most right node.
            currentLevel = tmp.level;
            out.push_back(lastVisited->val);
        }
        
        lastVisited = tmp.node;
    }
    
    if( lastVisited )
        out.push_back(lastVisited->val);

    return out;
}

void testRightSideView()
{
    TreeNode* n1 = new TreeNode(1);
    n1->left = new TreeNode(2);
    n1->right = new TreeNode(3);
    
    vector<int> v = rightSideView(n1);
    for( auto& i : v )
        cout << i << ", ";
}

#pragma mark - numIslands
//Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
//
//Example 1:
//
//11110
//11010
//11000
//00000
//Answer: 1
//
//Example 2:
//
//11000
//11000
//00100
//00011
//Answer: 3
int numIslands(vector<vector<char>>& grid)
{
    int founded = 0;
    for( int i = 0; i < grid.size(); i++ )
    {
        for( int j = 0; j < grid[i].size(); j++ )
        {
            if( grid[i][j] == '1' )
            {
                founded++;
                grid[i][j] = 'X';
                
                // Dig the island.
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                while( !q.empty() )
                {
                    auto currentPos = q.front();
                    q.pop();
                    // Go four directions
                    if( currentPos.first - 1 >= 0 && grid[currentPos.first-1][currentPos.second] == '1' )
                    {
                        q.push(make_pair(currentPos.first-1, currentPos.second));
                        grid[currentPos.first-1][currentPos.second] = 'X';
                    }
                    if( currentPos.first + 1 < grid.size() && grid[currentPos.first+1][currentPos.second] == '1' )
                    {
                        q.push(make_pair(currentPos.first+1, currentPos.second));
                        grid[currentPos.first+1][currentPos.second] = 'X';
                    }
                    if( currentPos.second - 1 >= 0 && grid[currentPos.first][currentPos.second-1] == '1' )
                    {
                        q.push(make_pair(currentPos.first, currentPos.second-1));
                        grid[currentPos.first][currentPos.second-1] = 'X';
                    }
                    if( currentPos.second + 1 < grid[0].size() && grid[currentPos.first][currentPos.second+1] == '1' )
                    {
                        q.push(make_pair(currentPos.first, currentPos.second+1));
                        grid[currentPos.first][currentPos.second+1] = 'X';
                    }
                }
            }
        }
    }
    
    return founded;
}

void testNumIslands()
{
    vector<vector<char>> t = {
        { '1','1','0','0','0' },
        { '1','1','0','0','0' },
        { '0','0','1','0','0' },
        { '0','0','0','1','1' }
    };
    vector<vector<char>> t1 = {{'1','0','1','1','0','1','1'}};
    vector<vector<char>> t2 =
    {
        {'1','1','1'},
        {'0','1','0'},
        {'1','1','1'}
    };
    vector<string> t3s = {
        "11111011111111101011",
        "01111111111110111110",
        "10111001101111111111",
        "11110111111111111111",
        "10011111111111111111",
        "10111111011101110111",
        "01111111111101101111",
        "11111111111101111011",
        "11111111110111111111",
        "11111111111111111111",
        "01111111011111111111",
        "11111111111111111111",
        "11111111111111111111",
        "11111011111110111111",
        "10111110111011110111",
        "11111111111101111110",
        "11111111111110111100",
        "11111111111111111111",
        "11111111111111111111",
        "11111111111111111111"
    };
    vector<vector<char>> t3;
    for( auto& s : t3s )
    {
        vector<char> cs;
        for( auto& c : s )
            cs.push_back(c);
        t3.push_back(cs);
    }
    
    cout << numIslands(t3);
}

#pragma mark - run

void Level16::Run()
{
    testNumIslands();
}

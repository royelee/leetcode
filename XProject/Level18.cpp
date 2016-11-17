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
    int rowCount = (int)matrix.size();
    if(rowCount == 0 )
        return 0;

    int colCount = (int)matrix[0].size();
    vector<vector<int>> dp( matrix.size(), vector<int>( colCount ) );
    
    int maxSquare = 0;
    
    for( int row = 0; row < rowCount; row++ )
    {
        for( int col = 0; col < colCount; col++ )
        {
            int c = matrix[row][col];
            if( c == '1' )
            {
                int up = row - 1 >= 0 ? dp[row-1][col] : 0;
                int left = col - 1 >= 0 ? dp[row][col-1] : 0;
                int leftUp = row - 1 >= 0 && col - 1 >= 0 ? dp[row-1][col-1] : 0;
                dp[row][col] = min(min(up, left), leftUp) + 1;
                
                maxSquare = max( maxSquare, dp[row][col] * dp[row][col] );
            }
        }
    }
    
    return maxSquare;
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
    
    vector<vector<string>> ms = { m1, m2, m3, m4 };
    for( auto& m : ms )
    {
        vector<vector<char>> tests;
        for( auto& s : m )
        {
            vector<char> vC;
            for( auto& c : s )
            {
                if( c == '1' || c == '0' )
                    vC.push_back(c);
            }
            tests.push_back(vC);
        }
        cout << maximalSquare(tests) << endl;
    }
}

#pragma mark - countNodes
//Given a complete binary tree, count the number of nodes.
//
//Definition of a complete binary tree from Wikipedia:
//In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
int _countNode( TreeNode* node, int& visitedLastLevel, int currentLevel, const int expectedLevel )
{
    if( currentLevel > expectedLevel )
        return 0;

    if( currentLevel == expectedLevel )
    {
        if( node->left || node->right )
        {
            int nodeCount = 0;
            int fullNodeCount = (pow(2, expectedLevel-1) - visitedLastLevel - 1) * 2;
            nodeCount += fullNodeCount;
            nodeCount += node->left ? 1 : 0;
            nodeCount += node->right ? 1 : 0;
            nodeCount += pow(2, expectedLevel) - 1;
            return nodeCount;
        }
        else
        {
            visitedLastLevel++;
            if( visitedLastLevel == pow(2, expectedLevel-1) )
                return pow(2, expectedLevel) - 1;
        }
    }
    
    int r = _countNode(node->right, visitedLastLevel, currentLevel+1, expectedLevel);
    if( r != 0 )
        return r;
    
    return _countNode(node->left, visitedLastLevel, currentLevel+1, expectedLevel);
}


int countNodes(TreeNode* root)
{
    if( root == nullptr ) return 0;

    int lastFullLevel = 1;
    TreeNode* node = root;
    while( node->right )
    {
        node = node->right;
        lastFullLevel++;
    }
    
    int visitedLastLevel = 0;
    return _countNode(root, visitedLastLevel, 1, lastFullLevel);
}

void testCountNodes()
{
    auto F = [](bool a) -> string { return a ? "true" : "false"; };
    
    TreeNode* node = new TreeNode(1);
    auto P = [&](int expect){ cout << F( countNodes(node) == expect ) << endl; };
    
    P(1);
    
    node->left = new TreeNode(2);
    P(2);
    
    node->right = new TreeNode(3);
    P(3);

    node->left->left= new TreeNode(4);
    P(4);
    
    node->left->right= new TreeNode(4);
    P(5);
}


#pragma mark - run

void Level18::Run()
{
    testCountNodes();
}
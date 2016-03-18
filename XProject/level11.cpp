//
//  level11.cpp
//  XProject
//
//  Created by Roye Li on 1/31/16.
//  Copyright (c) 2016 Roye Li. All rights reserved.
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

using namespace std;

#pragma mark - hasPathSum

//Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
//
//For example:
//Given the below binary tree and sum = 22,
//5
/// \
//4   8
///   / \
//11  13  4
///  \      \
//7    2      1
//return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
bool hasPathSum(TreeNode* root, int sum)
{
    if( root == nullptr )
        return false;
    
    int r = sum - root->val;
    if( r == 0 && root->left == nullptr && root->right == nullptr)
        return true;
    
    return hasPathSum( root->left, r ) || hasPathSum( root->right, r );
}

#pragma pathSum vectors.
//Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
//
//For example:
//Given the below binary tree and sum = 22,
//5
/// \
//4   8
///   / \
//11  13  4
///  \    / \
//7    2  5   1
//return
//[
// [5,4,11,2],
// [5,8,4,5]
// ]
void _pathSum(TreeNode* root, int sum, vector<int>& current, vector<vector<int>>& results )
{
    if( root == nullptr )
        return;
    
    current.push_back(root->val);

    int r = sum - root->val;
    if( r == 0 && root->left == nullptr && root->right == nullptr)
    {
        results.push_back(current);
    }
    
    _pathSum( root->left, r, current, results );
    _pathSum( root->right, r, current, results );

    current.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int sum)
{
    vector<vector<int>> r;
    vector<int> current;
    _pathSum( root, sum, current, r);
    return r;
}

#pragma mark - flatten
//Given a binary tree, flatten it to a linked list in-place.
//
//For example,
//Given
//
//         1
//        / \
//       2   5
//      / \   \
//     3   4   6
//The flattened tree should look like:
//   1
//    \
//     2
//      \
//       3
//        \
//         4
//          \
//           5
//            \
//             6
TreeNode* preNode = nullptr;

void flatten( TreeNode* node )
{
    if( node == nullptr )
        return;
    
    TreeNode* left = node->left;
    TreeNode* right = node->right;
    
    if( preNode )
    {
        preNode->right = node;
        preNode->left = nullptr;
    }
    
    preNode = node;
    
    flatten( left );
    flatten( right );
}

void testFlatten()
{
    TreeNode* node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->right = new TreeNode(5);
    node->left->left = new TreeNode(3);
    node->left->right = new TreeNode(4);
    node->right->right = new TreeNode(6);
    
    preOrderTrasveral(node);

    flatten(node);
    
    preOrderTrasveral(node);
}

#pragma mark - generate

//Given numRows, generate the first numRows of Pascal's triangle.
//
//For example, given numRows = 5,
//Return
//
//[
//     [1],
//    [1,1],
//   [1,2,1],
//  [1,3,3,1],
// [1,4,6,4,1]
//]
vector<vector<int>> generate(int numRows)
{
    
    //The binomial coefficients can be arranged to form Pascal's triangle. which is C(n,k)
    vector<vector<int>> output;
    for( int i = 0; i < numRows; i++ )
    {
        vector<int> row( i + 1 );
        for( int j = 0; j < row.size(); j++ )
        {
            // => C(i, j)
            row[j] = factorial(i) / (factorial(j) * factorial(i-j));
        }
        output.push_back(row);
    }
    
    return output;
}

void testGenerate()
{
    vector<vector<int>> o = generate(14);
    for( auto& v : o )
    {
        for_each(v.begin(), v.end(), [](int value){
            cout << value << " ";
        });
        cout << endl;
    }
}

#pragma mark - getRow
uint64_t permutation(int n, int j)
{
    uint64_t ret = 1;
    for(uint64_t i = 0; i < j; i++, n--)
        ret *= n;
    return ret;
}

uint64_t factorial64(unsigned int n)
{
    uint64_t ret = 1;
    for(unsigned int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

//Given an index k, return the kth row of the Pascal's triangle.
//
//For example, given k = 3,
//Return [1,3,3,1].
//
//Note:
//Could you optimize your algorithm to use only O(k) extra space?
vector<int> getRow(int rowIndex)
{
    vector<int> output(rowIndex + 1, 1 );
    for( int i = 0; i < rowIndex + 1; i++ )
    {
        // from {1,2,1} => {3, 3, 1}
        for( int j = 0; j < i - 1; j++ )
        {
            output[j] = output[j] + output[j+1];
        }
        
        // from {3, 3, 1} move to { x, 3, 3}
        for( int j = i - 1; j > 0; j-- )
        {
            output[j] = output[j-1];
        }

        output[0] = 1;
        output[i] = 1;
    }
    
    return output;
}

void testGetRow()
{
    for( const auto& v : getRow(4) )
    {
        cout << v << " ";
    }
}

#pragma mark - minimumTotal
//Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
//
//For example, given the following triangle
//[
//     [2],
//    [3,4],
//   [6,5,7],
//  [4,1,8,3]
//]
//The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
//
//Note:
//Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
int minimumTotal(vector<vector<int>>& triangle)
{
    if( triangle.size() == 0 )
        return 0;

    vector<int> dp( triangle.size(), 0 );
    dp[0] = triangle[0][0];
    for( int i = 1; i < triangle.size(); i++ )
    {
        vector<int> lastDP( dp );
        for( int j = 0; j < triangle[i].size(); j++ )
        {
            int m;
            if( j == 0 )
                m = lastDP[0];
            else if( j == triangle[i].size() - 1 )
                m = lastDP[triangle[i].size() - 2];
            else
                m = min( lastDP[j-1] , lastDP[j] );
            dp[j] = m + triangle[i][j];
        }
    }
    
    int r = dp[0];
    for_each(dp.begin(), dp.end(), [&r]( int value )
             {
                 r = min( r, value );
             });
    return r;
}

void testMinimumTotal()
{
//    vector<vector<int>> triangle =
//    {
//        {2},
//        {3,4},
//        {6,5,7},
//        {4,1,8,3}
//    };
    vector<vector<int>> triangle =
    {
        {-7},
        {-2,1},
        {-5,-5,9},
        {-4,-5,4,4},
        {-6,-6,2,-1,-5},
        {3,7,8,-3,7,-9},
        {-9,-1,-9,6,9,0,7},
        {-7,0,-6,-8,7,1,-4,9},
        {-3,2,-6,-9,-7,-6,-9,4,0},
        {-8,-6,-3,-9,-2,-6,7,-5,0,7},
        {-9,-1,-2,4,-2,4,4,-1,2,-5,5},
        {1,1,-6,1,-2,-4,4,-2,6,-6,0,6},
        {-3,-3,-6,-2,-6,-2,7,-9,-5,-7,-5,5,1}
    };
    cout << minimumTotal(triangle);
}

#pragma mark - connect
//Given a binary tree
//
//    struct TreeLinkNode {
//      TreeLinkNode *left;
//      TreeLinkNode *right;
//      TreeLinkNode *next;
//    }
//Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
//
//Initially, all next pointers are set to NULL.
//
//Note:
//
//You may only use constant extra space.
//You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
//For example,
//Given the following perfect binary tree,
//         1
//       /  \
//      2    3
//     / \  / \
//    4  5  6  7
//After calling your function, the tree should look like:
//         1 -> NULL
//       /  \
//      2 -> 3 -> NULL
//     / \  / \
//    4->5->6->7 -> NULL
void connect(TreeLinkNode* parent)
{
    if( parent == nullptr || parent->left == nullptr )  // Current node is null or current layer is empty.
        return;
    
    TreeLinkNode* itParent = parent;
    TreeLinkNode* childHead = nullptr;
    TreeLinkNode* preNode = nullptr;
    while (itParent != nullptr)
    {
        if( childHead == nullptr )
            childHead = itParent->left;
        
        if( preNode )
            preNode->next = itParent->left;
        itParent->left->next = itParent->right;
        preNode = itParent->right;
        
        itParent = itParent->next;
    }
    
    connect( childHead );
}

void testConnect()
{
    TreeLinkNode* root = new TreeLinkNode( 1 );
    root->left = new TreeLinkNode( 2 );
    root->right = new TreeLinkNode( 3 );
    root->left->left = new TreeLinkNode( 4 );
    root->left->right = new TreeLinkNode( 5 );
    root->right->left = new TreeLinkNode( 6 );
    root->right->right = new TreeLinkNode( 7 );
    
    connect( root );
    cout << root->val;
}

#pragma mark - maxProfit
//Say you have an array for which the ith element is the price of a given stock on day i.
//
//If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
int maxProfit(vector<int>& prices)
{
    // Scan from left to right. And keep track the minimal price in left. So, each step, only calculate the difference between current price and minimal price.
    // If this diff large than the current max difference, replace it.
    int minValue = numeric_limits<int>::max();
    int profit = 0;
    for( int i = 0; i < prices.size(); i++ )
    {
        if( prices[i] < minValue )
            minValue = prices[i];
        if( prices[i] - minValue > profit )
            profit = prices[i] - minValue;
    }
    
    return profit;
}

void testMaxProfit()
{
    vector<vector<int>> tests = {
        {},
        {3,3},
        {1,2,3,4,5},
        {5,4,3,2,1},
        {4,5,3,1,2},
        {4,5,1,2,3}
    };
    
    for( auto& v : tests )
    {
        cout << maxProfit(v) << endl;
    }
}


#pragma mark - run

void Level11::Run()
{
    testMaxProfit();
}
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

#pragma mark - run

void Level11::Run()
{
    testFlatten();
}
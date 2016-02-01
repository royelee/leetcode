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

#pragma mark - run

void Level11::Run()
{
    cout << "hello";
}
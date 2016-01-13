//
//  Level10.cpp
//  XProject
//
//  Created by Roye Li on 1/6/16.
//  Copyright (c) 2016 Roye Li. All rights reserved.
//

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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


//Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
//
//For example:
//Given binary tree {3,9,20,#,#,15,7},
//3
/// \
//9  20
///  \
//15   7
//return its level order traversal as:
//[
// [3],
// [9,20],
// [15,7]
// ]
vector<vector<int>> levelOrder(TreeNode* root)
{
    vector<vector<int>> output;
    if( !root )
        return output;
    
    unique_ptr< vector<TreeNode*> > levelNodes( new vector<TreeNode*>() );
    levelNodes->push_back(root);
    while( !levelNodes->empty() )
    {
        unique_ptr< vector<TreeNode*> > newNodes( new vector<TreeNode*>() );

        vector<int> currentLevelValues;
        for( TreeNode* node : *levelNodes )
        {
            if( node )
            {
                currentLevelValues.push_back(node->val);
                if( node->left )
                    newNodes->push_back(node->left);
                if( node->right )
                    newNodes->push_back(node->right);
            }
        }
        
        output.push_back( currentLevelValues );
        swap( levelNodes, newNodes );
    }
    
    return output;
}

#pragma mark - zigzagLevelOrder
//Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
//
//For example:
//Given binary tree {3,9,20,#,#,15,7},
//3
/// \
//9  20
///  \
//15   7
//return its zigzag level order traversal as:
//[
// [3],
// [20,9],
// [15,7]
// ]
vector<vector<int>> zigzagLevelOrder(TreeNode* root)
{
    vector<vector<int>> output;
    if( !root )
        return output;
    
    bool left = true;
    unique_ptr< vector<TreeNode*> > levelNodes( new vector<TreeNode*>() );
    levelNodes->push_back(root);
    while( !levelNodes->empty() )
    {
        unique_ptr< vector<TreeNode*> > newNodes( new vector<TreeNode*>() );
        
        vector<int> currentLevelValues;
        for( TreeNode* node : *levelNodes )
        {
            if( node )
            {
                if( left )
                    currentLevelValues.push_back(node->val);
                else
                    currentLevelValues.insert(currentLevelValues.begin(), node->val);

            
                if( node->left )
                    newNodes->push_back(node->left);
                if( node->right )
                    newNodes->push_back(node->right);
            }
        }

        left = !left;
        output.push_back( currentLevelValues );
        swap( levelNodes, newNodes );
    }
    
    return output;
}

#pragma mark - maxDepth
//Given a binary tree, find its maximum depth.
//
//The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
void _maxDepth( TreeNode* node, int& maxLevel, int currentLevel )
{
    if( node )
    {
        currentLevel = currentLevel + 1;
        maxLevel = max(currentLevel, maxLevel);
        _maxDepth( node->left, maxLevel, currentLevel );
        _maxDepth( node->right, maxLevel, currentLevel );
    }
}

int maxDepth(TreeNode* root)
{
    int maxLevel = 0;
    _maxDepth( root, maxLevel, 0 );
    return maxLevel;
}

#pragma mark - buildTree
void _buildTree(TreeNode*& node, vector<int>& preorder, vector<int>& inorder, size_t preOrderStart, size_t inOrderStart, int length )
{
    if( length > 0)
    {
        // Has element we want.
        int value = preorder[preOrderStart];
        
        size_t inOrderMidIndex = inOrderStart;
        for( size_t i = inOrderStart; i < inOrderStart + length; i++ )
        {
            if( inorder[i] == value )
            {
                inOrderMidIndex = i;
                break;
            }
        }
        
        node = new TreeNode( value );
        
        int leftLength = inOrderMidIndex - inOrderStart;
        _buildTree( node->left, preorder, inorder, preOrderStart + 1, inOrderStart, leftLength );
        
        int rightLength = length - leftLength - 1;
        _buildTree( node->right, preorder, inorder, preOrderStart + leftLength + 1, inOrderMidIndex + 1, rightLength );
    }
}

//Given preorder and inorder traversal of a tree, construct the binary tree.
//Note:
//You may assume that duplicates do not exist in the tree.
//
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
{
    if( preorder.size() == 0 || preorder.size() != inorder.size() )
    {
        return nullptr;
    }
    
    TreeNode* root = nullptr;
    _buildTree( root, preorder, inorder, 0, 0, preorder.size() );
    
    return root;
}

void preOrderTrasveral( TreeNode* node )
{
    if( node )
    {
        cout << node->val << " ";
        preOrderTrasveral(node->left);
        preOrderTrasveral(node->right);
    }
}

void inOrderTrasveral( TreeNode* node )
{
    if( node )
    {
        inOrderTrasveral(node->left);
        cout << node->val << " ";
        inOrderTrasveral(node->right);
    }
}

void testBuildTree()
{
    vector<int> preorder = { 1, 2, 3, 4, 5, 6, 7 };
    vector<int> inorder = { 3, 2, 4, 1, 6, 5, 7 };
    TreeNode* root = buildTree( preorder, inorder );
    
    cout << "pre order :";
    preOrderTrasveral(root);
    cout << endl;
    
    cout << "in order :";
    inOrderTrasveral(root);
    cout << endl;
}


#pragma mark - run

void Level10::Run()
{
    testBuildTree();
}
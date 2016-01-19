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

void postOrderTrasveral( TreeNode* node )
{
    if( node )
    {
        postOrderTrasveral(node->left);
        postOrderTrasveral(node->right);
        cout << node->val << " ";
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
    
    cout << "post order :";
    postOrderTrasveral(root);
    cout << endl;
}


#pragma mark - build tree 2
//Given inorder and postorder traversal of a tree, construct the binary tree.
//
//Note:
//You may assume that duplicates do not exist in the tree.
void _buildTree2(TreeNode*& node, vector<int>& inorder, vector<int>& postorder,  size_t postOrderStart, size_t inOrderStart, int length )
{
    if( length > 0)
    {
        // Has element we want.
        int value = postorder[postOrderStart + length - 1];
        
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
        _buildTree2( node->left, inorder, postorder, postOrderStart, inOrderStart, leftLength );
        
        int rightLength = length - leftLength - 1;
        _buildTree2( node->right, inorder, postorder, postOrderStart + leftLength, inOrderMidIndex + 1, rightLength );
    }
}

TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder)
{
    if( inorder.size() == 0 || postorder.size() != inorder.size() )
    {
        return nullptr;
    }
    
    TreeNode* root = nullptr;
    _buildTree2( root, inorder, postorder, 0, 0, inorder.size() );
    
    return root;
}

void testBuildTree2()
{
    vector<int> postOrder = { 3, 4, 2, 6, 7, 5, 1  };
    vector<int> inorder = { 3, 2, 4, 1, 6, 5, 7 };
    TreeNode* root = buildTree2( inorder, postOrder );
    
    cout << "post order :";
    postOrderTrasveral(root);
    cout << endl;
    
    cout << "in order :";
    inOrderTrasveral(root);
    cout << endl;
}

#pragma mark - levelOrderBottom
//Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).
//
//For example:
//Given binary tree {3,9,20,#,#,15,7},
//3
/// \
//9  20
///  \
//15   7
//return its bottom-up level order traversal as:
//[
// [15,7],
// [9,20],
// [3]
// ]
vector<vector<int>> levelOrderBottom(TreeNode* root)
{
    vector<vector<int>> output;
    if( root == nullptr )
        return output;
    
    vector<TreeNode*> levelNodes;
    levelNodes.push_back( root );
    while (!levelNodes.empty())
    {
        vector<TreeNode*> nexts;
        vector<int> values;
        for( TreeNode* tmp : levelNodes )
        {
            values.push_back(tmp->val);
            if( tmp->left )
                nexts.push_back(tmp->left);
            if( tmp ->right )
                nexts.push_back(tmp->right);
        }
        
        levelNodes.clear();
        levelNodes.insert(levelNodes.begin(), nexts.begin(), nexts.end());
        
        output.insert(output.begin(), values);
    }
    
    return output;
}

#pragma mark - sortedArrayToBST
void _sortedArrayToBST(vector<int>& nums, TreeNode*& node, int start, int end)
{
    if( end >= start )
    {
        int mid = (start + end ) / 2;
        node = new TreeNode( nums[mid] );
        _sortedArrayToBST( nums, node->left, start, mid - 1 );
        _sortedArrayToBST( nums, node->right, mid + 1, end );
    }
}


//Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
TreeNode* sortedArrayToBST(vector<int>& nums)
{
    TreeNode* root = nullptr;
    _sortedArrayToBST(nums, root, 0, nums.size() - 1);
    return root;
}

void testSortedArrayToBST()
{
    vector<int> v = {1,2,3,4,5};
    TreeNode* root = sortedArrayToBST(v);
    inOrderTrasveral(root);
    
    v = {};
    root = sortedArrayToBST(v);
    inOrderTrasveral(root);
    
    v = {1};
    root = sortedArrayToBST(v);
    inOrderTrasveral(root);
    
    v = {1,2};
    root = sortedArrayToBST(v);
    inOrderTrasveral(root);
}

#pragma mark - sortedListToBST
//Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
TreeNode* sortedListToBST(ListNode* head)
{
    return nullptr;
}



#pragma mark - run

void Level10::Run()
{
    testSortedArrayToBST();
}
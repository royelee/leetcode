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
int countNodes(TreeNode* root)
{
    if( root == nullptr ) return 0;

    int leftHeight = 1;
    int rightHeight = 1;
    TreeNode* node = root;
    while( node->left ) { node = node->left; leftHeight++; }
    node = root;
    while( node->right ) { node = node->right; rightHeight++; }
    
    if( leftHeight == rightHeight ) return pow(2, leftHeight) - 1;
    return countNodes(root->left) + countNodes(root->right) + 1;
}

void testCountNodes()
{
    TreeNode* node = new TreeNode(1);
    auto P = [&](int expect){ cout << BoolToStr( countNodes(node) == expect ) << endl; };
    
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

#pragma mark - calculate
//Implement a basic calculator to evaluate a simple expression string.
//
//The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .
//
//You may assume that the given expression is always valid.
//
//Some examples:
//"1 + 1" = 2
//" 2-1 + 2 " = 3
//"(1+(4+5+2)-3)+(6+8)" = 23
//Note: Do not use the eval built-in library function.
uint64_t GetNextNumber(string s, size_t& start )
{
    uint64_t currentNum = 0;
    for( size_t i = start; i < s.size(); i++ )
    {
        char c = s[i];
        if( c >= '0' && c <= '9' )
            currentNum = currentNum * 10 + ( c - '0' );
        else
        {
            start = i + 1;
            break;
        }
    }
    
    return currentNum;
}

int calculate(string s)
{
    stack<uint64_t> numbers;
    stack<char> ops;
    
    // Not done yet!!!!
    return 0;
}

void testCacluate()
{
    vector<pair<string, int>> v = {
        {"1 + 1", 2},
        {" 2-1 + 2 ", 3},
        {"(1+(4+5+2)-3)+(6+8)", 23}
    };
    
    for( auto& p : v )
    {
        cout << BoolToStr( calculate(p.first) == p.second ) << endl;
    }
}

#pragma mark - Stack
//Implement the following operations of a stack using queues.
//
//push(x) -- Push element x onto stack.
//pop() -- Removes the element on top of the stack.
//top() -- Get the top element.
//empty() -- Return whether the stack is empty.
//Notes:
//You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
//Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.
//You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).
//Update (2015-06-11):
//The class name of the Java function had been updated to MyStack instead of Stack.
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        m_queue.push(x);
    }

    // Removes the element on top of the stack.
    void pop() {
        queue<int> newQueue;
        while( m_queue.size() > 1 )
        {
            newQueue.push(m_queue.front());
            m_queue.pop();
        }
        m_queue = std::move( newQueue );
    }

    // Get the top element.
    int top() {
        return m_queue.back();
    }

    // Return whether the stack is empty.
    bool empty() {
        return m_queue.empty();
    }
private:
    queue<int> m_queue;
};

#pragma mark - invertTree
//Invert a binary tree.
//
//     4
//   /   \
//  2     7
// / \   / \
//1   3 6   9
//to
//     4
//   /   \
//  7     2
// / \   / \
//9   6 3   1
TreeNode* invertTree(TreeNode* root)
{
    if( root == nullptr )   return root;

    queue<TreeNode*> q;
    q.push(root);
    while( !q.empty() )
    {
        size_t s = q.size();
        size_t i = 0;
        while( i++ < s )
        {
            TreeNode* n = q.front();
            q.pop();
            if( n->left != nullptr )    q.push(n->left);
            if( n->right != nullptr )   q.push(n->right);
            
            swap( n->left, n->right );
        }
    }
    
    return root;
}

#pragma mark - run

void Level18::Run()
{
    testCacluate();
}
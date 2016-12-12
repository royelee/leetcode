//
//  Level19.cpp
//  XProject
//
//  Created by Roye Li on 11/26/16.
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

#pragma mark - isPowerOfTwo
//Given an integer, write a function to determine if it is a power of two.
bool isPowerOfTwo(int n)
{
    if( n<=0 )
        return false;

    int numOfOneBit = 0;
    while( n != 0 )
    {
        if( n & 1 )
            numOfOneBit++;
        
        n = n >> 1;
    }
    
    return numOfOneBit == 1;
}

void testIsPowerOfTwo()
{
    cout << sizeof(int) << endl;
    for( size_t i = 0; i < 100; i++ )
        cout << pow(2,i) << endl;
}

//Implement the following operations of a queue using stacks.
//
//push(x) -- Push element x to the back of queue.
//pop() -- Removes the element from in front of queue.
//peek() -- Get the front element.
//empty() -- Return whether the queue is empty.
//Notes:
//You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
//Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
//You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).
class Queue {
    stack<int> m_stack;
    
public:
    // Push element x to the back of queue.
    void push(int x)
    {
        stack<int> b;
        
        while( !m_stack.empty() )
        {
            int v = m_stack.top();
            b.push(v);
            m_stack.pop();
        }
        b.push(x);
        
        while( !b.empty() )
        {
            int v = b.top();
            m_stack.push(v);
            b.pop();
        }
    }
    
    // Removes the element from in front of queue.
    void pop(void) {
        m_stack.pop();
    }
    
    // Get the front element.
    int peek(void) {
        return m_stack.top();
    }
    
    // Return whether the queue is empty.
    bool empty(void) {
        return m_stack.empty();
    }
};

#pragma mark - isPalindrome
//Given a singly linked list, determine if it is a palindrome.
//Follow up:
//Could you do it in O(n) time and O(1) space?
bool isPalindrome(ListNode* head)
{
    if( head == nullptr )
        return false;
    
    ListNode* oneStep = head;
    ListNode* twoStep = head;
    while( oneStep != nullptr && twoStep != nullptr )   // Alternative twoStep->next && twoStep->next->next, save the if( twoStep ) below
    {
        oneStep = oneStep->next;
        twoStep = twoStep->next;
        if( twoStep )
            twoStep = twoStep->next;
    }
    
    ListNode* pre = nullptr;
    ListNode* next = oneStep;
    while( next )
    {
        ListNode* nn = next->next;
        next->next = pre;
        pre = next;
        next = nn;
    }
    
    oneStep = head;
    while( oneStep )
    {
        if( oneStep->val != pre->val )
            return false;
        
        oneStep = oneStep->next;
        pre = pre->next;
    }
    
    return true;
}

static void TestIsPalindrome()
{
    ListNode* node = new ListNode(1);
    node->next = new ListNode(0);
    node->next->next = new ListNode(0);
    cout << BoolToStr(isPalindrome(node));
}

#pragma mark - lowestCommonAncestor

//Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.
//
//According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”
//
//        _______6______
//       /              \
//    ___2__          ___8__
//   /      \        /      \
//   0      _4       7       9
//         /  \
//         3   5
//For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if( root == nullptr || p == nullptr || q == nullptr )
        return nullptr;
    
    TreeNode* small = p->val < q->val ? p : q;
    TreeNode* big = small == p ? q : p;
    
    if( small->val <= root->val && root->val <= big->val )
        return root;
    else if( root->val < small->val )
        return lowestCommonAncestor(root->right, p, q);
    else
        return lowestCommonAncestor(root->left, p, q);
}

void testLowestCommonAncestor()
{
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    
    cout << ( lowestCommonAncestor(root, root->left, root->right)->val == 6 ) << endl;
    cout << ( lowestCommonAncestor(root, root->left->right, root->left)->val == 2 ) << endl;
    cout << ( lowestCommonAncestor(root, root->left, root->left->right)->val == 2 ) << endl;
}

#pragma mark - run

void Level19::Run()
{
    TestIsPalindrome();
}
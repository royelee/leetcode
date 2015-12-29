//
//  Level9.cpp
//  XProject
//
//  Created by Roye Li on 12/22/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
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

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//Reverse a linked list from position m to n. Do it in-place and in one-pass.
//
//For example:
//Given 1->2->3->4->5->NULL, m = 2 and n = 4,
//
//return 1->4->3->2->5->NULL.
//
//Note:
//Given m, n satisfy the following condition:
//1 ≤ m ≤ n ≤ length of list.
ListNode* reverseBetween(ListNode* head, int m, int n)
{
    ListNode* newHead = new ListNode(-1);
    newHead->next = head;
    if( m >= 1 && m <= n )
    {
        ListNode* iterM = nullptr;
        ListNode* iter = head;
        ListNode* beforeM = newHead;
        int i = 1;
        while( i < m )
        {
            beforeM = iter;
            iter = iter->next;
            i++;
        }
        iterM = iter;
        
        ListNode* next = iter->next;
        while( i < n )
        {
            ListNode* cur = iter;
            iter = next;
            next = next->next;
            iter->next = cur;
            i++;
        }
        
        beforeM->next = iter;
        iterM->next = next;
    }
    
    return newHead->next;
}

void tesetReverseBetween()
{
    vector<int> v = { 1, 2, 3, 4, 5 };
    ListNode* head = new ListNode(-1);
    ListNode* it = head;
    for( int i = 0; i < v.size(); i++ )
    {
        it->next = new ListNode(v[i]);
        it = it->next;
    }
    
    cout << "before" << endl;
    it = head->next;
    while( it )
    {
        cout << it->val << " ";
        it = it->next;
    }
    cout << endl;
    
    it = reverseBetween( head->next, 2, 5 );
    
    cout << "after" << endl;
    while( it )
    {
        cout << it->val << " ";
        it = it->next;
    }
    cout << endl;
}


#pragma mark - restoreIpAddresses
bool _isValidPart( string& token )
{
    if( token.size() == 1 )
        return true;
    if( token.size() > 1 )
    {
        if( token[0] == '0' )
            return false;
        
        int v = stoi(token);
        if( v <= 255 )
            return true;
    }
    
    return false;
}

//Given a string containing only digits, restore it by returning all possible valid IP address combinations.
//
//For example:
//Given "25525511135",
//
//return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

void _restoreIpAddresses( string s, int current, vector<string>& inserted, vector<string>& out )
{
    if( inserted.size() == 4 )
    {
        if( current == s.size() )
        {
            stringstream ss;
            for( int i = 0; i < 3; i++ )
            {
                ss << inserted[i] << ".";
            }
            
            ss << inserted[3];
            
            out.push_back(ss.str());
        }
        
        return;
    }
    
    for( int i = 1; i <= 3; i++ )
    {
        if( current + i - 1 < s.size() )
        {
            string sub = s.substr(current, i);
            bool isValid = _isValidPart(sub);
            if( isValid )
            {
                inserted.push_back(sub);
                _restoreIpAddresses(s, current+i, inserted, out);
                inserted.pop_back();
            }
        }
    }
}


vector<string> restoreIpAddresses(string s)
{
    vector<string> output;
    vector<string> inserted;
    _restoreIpAddresses( s, 0, inserted, output );
    return output;
}

void testRestoreIpAddresses()
{
    vector<string> out = restoreIpAddresses("1111");    //25525511135
    for( auto s : out )
        cout << s << endl;
}

#pragma mark - inorderTraversal
//Given a binary tree, return the inorder traversal of its nodes' values.
//
//For example:
//Given binary tree {1,#,2,3},
//1
//\
//2
///
//3
//return [1,3,2].
//
//Note: Recursive solution is trivial, could you do it iteratively?
//
//confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
//
//
//OJ's Binary Tree Serialization:
//The serialization of a binary tree follows a level order traversal, where '#' signifies a path terminator where no node exists below.
//
//Here's an example:
//1
/// \
//2   3
///
//4
//\
//5
//The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void _inOrderTraversal( TreeNode* root, vector<int>& out )
{
    if( root == nullptr )
        return;
    
    _inOrderTraversal(root->left, out );
    out.push_back(root->val);
    _inOrderTraversal(root->right, out );
}

vector<int> inorderTraversal(TreeNode* root)
{
    //In-order (symmetric)
    //Traverse the left subtree by recursively calling the in-order function.
    //Display the data part of current element.
    //Traverse the right subtree by recursively calling the in-order function.
    vector<int> out;
    
    if( root == nullptr )
        return out;
    
    vector<TreeNode*> parents;
    TreeNode* it = root;
    while( true )
    {
        bool goBack = false;
        if( !parents.empty() )
        {
            TreeNode* parent = parents.back();
            if( it == parent )
            {
                parents.pop_back();
                goBack = true;;
            }
        }
        
        if( it->left && !goBack )
        {
            parents.push_back(it);
            it = it->left;
        }
        else if( it->right )
        {
            out.push_back(it->val);
            it = it->right;
        }
        else
        {
            out.push_back(it->val);
            if( !parents.empty() )
            {
                TreeNode* parent = parents.back();
                it = parent;
            }
            else
            {
                break;
            }
        }
    }
    
    
    return out;
}

void testInorderTraversal()
{
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    //root->left->left = new TreeNode(3);
    
    vector<int> out = inorderTraversal( root );
    for( auto& v : out )
        cout << v << " ";
}

#pragma mark - run

void Level9::Run()
{
    testInorderTraversal();
}
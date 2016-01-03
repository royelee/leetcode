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
#include <stack>

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
    
    vector<TreeNode*> parents;
    TreeNode* it = root;
    while( it || !parents.empty() )
    {
        if( it )
        {
            parents.push_back( it );
            it = it->left;
        }
        else
        {
            it = parents.back();
            out.push_back(it->val);
            parents.pop_back();
            it = it->right;
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

#pragma mark - numTrees
//Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
//
//For example,
//Given n = 3, there are a total of 5 unique BST's.
//
//1         3     3      2      1
//\       /     /      / \      \
//3     2     1      1   3      2
///     /       \                 \
//2     1         2                 3
int numTrees(int n)
{
    // P(0) = 1
    // P(1) = 1
    // P(2) = P(1) + P(1) = 2( 1,0 0,1 )
    // P(3) = P(2) + P(2) + P(1)*P(1) = 5( 0,2 2,0 1,1)
    // P(4) = P(3) + P(3) + P(2)*P(1) + P(2)*P(1) + P(1)*P(2) = 14( 3,0 0,3, 2,1, 1,2 )
    // P(5) = P(4) + P(4) + P(3)*P(1) + P(1)*P(3) + P(2)*P(2) = 28 + 10 + 4 = 42( 4,0 0,4 3,1 1,3 2,2 )
    vector<int> dp( n + 1 );
    dp[0] = 1;
    dp[1] = 1;
    
    for( int j = 2; j <= n; j++ )
    {
        for( int i = 0; i < j; i++ )
        {
            dp[j] += dp[i]*dp[j-1-i];
        }
    }
    
    return dp[n];
}

void testNumTrees()
{
    for( int i = 2; i < 6; i++ )
    {
        cout << numTrees(i) << endl;
    }
}

//Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
//
//Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
//
//For example, you may serialize the following tree
//
//1
/// \
//2   3
/// \
//4   5
//as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
//Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
// Encodes a tree to a single string.
class Codec {
public:
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root)
    {
        stringstream ss;
        
        stack<TreeNode*> treeStack;
        treeStack.push(root);
        while( !treeStack.empty() )
        {
            TreeNode* it = treeStack.top();
            treeStack.pop();
            
            if( it )
            {
                treeStack.push(it->right);
                treeStack.push(it->left);
                
                ss << to_string(it->val) << "|";
            }
            else
            {
                ss << "#" << "|";
            }
        }
        
        return ss.str();
    }
    
    bool getNext(string& data, string& sub, size_t& startFrom )
    {
        size_t index = data.find('|', startFrom);
        if( index == string::npos )   // can't find it
        {
            return false;
        }
        else
        {
            sub = data.substr(startFrom, index - startFrom );
            startFrom = index + 1;
            return true;
        }
    }
    
    void testGetNext(string data)
    {
        size_t startFrom = 0;
        string sub;
        while (getNext(data, sub, startFrom ))
        {
            cout << sub;
        }
        cout << endl;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
    {
        size_t startFrom = 0;
        string sub;
        TreeNode* head = nullptr;
        stack<TreeNode**> treeStack;
        while (getNext(data, sub, startFrom ))
        {
            TreeNode* node;
            if( sub == "#" )
                node = nullptr;
            else
                node = new TreeNode( stoi( sub ) );
            
            if( head == nullptr )
            {
                head = node;
            }
            else
            {
                TreeNode** newNode = treeStack.top();
                treeStack.pop();
                
                *newNode = node;
            }
            
            if( node != nullptr )
            {
                treeStack.push( &node->right );
                treeStack.push( &node->left );
            }
        }
    
        return head;
    }
};

void testSerializeDeserialize()
{
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(1);
    Codec codec;
    TreeNode* output = codec.deserialize(codec.serialize(root));
    cout << codec.serialize(output) << endl;;
    
    root->left->left = new TreeNode(2);
    output = codec.deserialize(codec.serialize(root));
    cout << codec.serialize(output) << endl;
    
    root->left->left = nullptr;
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    output = codec.deserialize(codec.serialize(root));
    cout << codec.serialize(output) << endl;
    
    output = codec.deserialize(codec.serialize(nullptr));
    cout << codec.serialize(output) << endl;
}

#pragma mark - generateTrees

//Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.
//
//For example,
//Given n = 3, your program should return all 5 unique BST's shown below.
//
//1         3     3      2      1
//\       /     /      / \      \
//3     2     1      1   3      2
///     /       \                 \
//2     1         2                 3
//confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
void copyAndRewrite( TreeNode* node, TreeNode*& copied, int& n )
{
    if( node )
    {
        copied = new TreeNode( n );
        copyAndRewrite( node->left, copied->left, n );
        copied->val = n;
        n++;
        copyAndRewrite( node->right, copied->right, n );
    }
}

vector<TreeNode*> generateTrees(int n)
{
    if( n <= 0 )
        return vector<TreeNode*>();

    vector<vector<TreeNode*>> dp(n + 1, vector<TreeNode*>());
    dp[0] = {  nullptr };
    dp[1] = { new TreeNode(1) };
    for( int j = 2; j <= n; j++ )
    {
        for( int i = 0; i < j; i++ )
        {
            for( TreeNode* leftNode: dp[i] )
            {
                for( TreeNode* rightNode : dp[j-1-i])
                {
                    TreeNode* newNode = new TreeNode( j );
                    newNode->left = leftNode;
                    newNode->right = rightNode;
                    
                    dp[j].push_back( newNode );
                }
            }
        }
    }
    
    // Copy the tree and rewrite value.
    vector<TreeNode*> output;
    for( TreeNode* node : dp[n] )
    {
        TreeNode* newNode = nullptr;
        int i = 1;
        copyAndRewrite( node, newNode, i );
        output.push_back(newNode);
    }
    

    return output;
}

void testGenerateTrees()
{
    vector<TreeNode*> out = generateTrees(0);
    Codec codec;
    for( TreeNode* node : out )
    {
        cout << codec.serialize( node ) << endl;
    }
}

#pragma mark - run

void Level9::Run()
{
    testGenerateTrees();
}
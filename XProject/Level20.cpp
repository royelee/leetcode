//
//  Level20.cpp
//  XProject
//
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


#pragma mark - lowestCommonAncestor

//Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
//
//According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”
//
//        _______3______
//       /              \
//    ___5__          ___1__
//   /      \        /      \
//   6      _2       0       8
//         /  \
//         7   4
//For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
static TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
   if( root == nullptr || root == p || root == q ) return root;
   TreeNode* left = lowestCommonAncestor(root->left, p, q);
   TreeNode* right = lowestCommonAncestor(root->right, p, q);
   return left ? ( right ? root : left ) : right;
}

static void testLowestCommonAncestor()
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

#pragma mark - deleteNode
//Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
//
//Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.
void deleteNode(ListNode* node)
{
    if( node == nullptr )
        return;
    
    ListNode* next = node->next;
    node->val = next->val;
    node->next = next->next;
}

#pragma mark - productExceptSelf
//Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
//
//Solve it without division and in O(n).
//
//For example, given [1,2,3,4], return [24,12,8,6].
//
//Follow up:
//Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)
vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> output( nums.size() );
    
    // Left
    output[0] = 1;
    for( size_t i = 1; i < nums.size(); i++ )
        output[i] = output[i - 1] * nums[i - 1];
    
    // Right
    int right = 1;
    for( int i = (int)nums.size() - 1; i >= 0; i-- )
    {
        output[i] *= right;
        right *= nums[i];
    }
    
    return output;
}

void testProductExceptSelf()
{
    vector<int> t = {1, 2, 3, 4};
    vector<int> o = productExceptSelf(t);
    for(auto& i : o )
        cout << i << " ";
}

#pragma mark - isAnagram
//Given two strings s and t, write a function to determine if t is an anagram of s.
//
//For example,
//s = "anagram", t = "nagaram", return true.
//s = "rat", t = "car", return false.
//
//Note:
//You may assume the string contains only lowercase alphabets.
//
//Follow up:
//What if the inputs contain unicode characters? How would you adapt your solution to such case?
bool isAnagram(string s, string t)
{
    int hash[26]{};
    for( const auto& c : s )
        hash[c - 'a']++;
    
    for( const auto& c : t)
        hash[c - 'a']--;
    
    for( const auto i : hash )
        if( i != 0 ) return false;
    
    return true;
}

void testIsAnagram()
{
    cout << BoolToStr( isAnagram("anagram", "nagaram") == true ) << endl;
    cout << BoolToStr( isAnagram("rat", "car") == false ) << endl;
}


#pragma mark - run

void Level20::Run()
{
   testProductExceptSelf();
}

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

namespace Level20Functions {

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

#pragma mark - searchMatrix
//Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
//
//Integers in each row are sorted in ascending from left to right.
//Integers in each column are sorted in ascending from top to bottom.
//For example,
//
//Consider the following matrix:
//
//[
//  [1,   4,  7, 11, 15],
//  [2,   5,  8, 12, 19],
//  [3,   6,  9, 16, 22],
//  [10, 13, 14, 17, 24],
//  [18, 21, 23, 26, 30]
//]
//Given target = 5, return true.
//
//Given target = 20, return false.
bool searchMatrix(vector<vector<int>>& matrix, int target)
{
    if( matrix.size() == 0 )
        return false;

    int row = 0;
    int col = (int)matrix[0].size() - 1;
    while( row < matrix.size() && col >= 0 )
    {
        int v = matrix[row][col];
        if( target == v )
            return true;
        else if( target > v )
            row++;
        else
            col--;
    }
    
    return false;
}

void testSearchMatrix()
{
    vector<vector<int>> m =
    {
        {1,   4,  7, 11, 15},
        {2,   5,  8, 12, 19},
        {3,   6,  9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    cout << BoolToStr( searchMatrix(m, 5) == true ) << endl;
    cout << BoolToStr( searchMatrix(m, 20) == false ) << endl;
}
    
}   // namespace Level20Functions

#pragma mark - diffWaysToCompute
// Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.
//
//
//Example 1
//Input: "2-1-1".
//
//((2-1)-1) = 0
//(2-(1-1)) = 2
//Output: [0, 2]
//
//
//Example 2
//Input: "2*3-4*5"
//
//(2*(3-(4*5))) = -34
//((2*3)-(4*5)) = -14
//((2*(3-4))*5) = -10
//(2*((3-4)*5)) = -10
//(((2*3)-4)*5) = 10
//Output: [-34, -14, -10, -10, 10]
vector<int> _diffWayToCompute(vector<int>& numbers, vector<char>& ops, int start, int size )
{
    if( size == 1 )
        return {numbers[start]};
    
    vector<int> output;
    for( int i = 1; i < size; i++ )
    {
        vector<int> left = _diffWayToCompute(numbers, ops, start, i);
        vector<int> right = _diffWayToCompute(numbers, ops, start + i, size - i);
        char op = ops[start + i - 1];
        for( auto& l : left )
        {
            for( auto& r : right )
            {
                auto result = op == '+' ? l + r : ( op == '-' ? l - r : l * r );
                output.push_back( result );
            }
        }
    }
    return output;
}
    
vector<int> diffWaysToCompute(string input)
{
    vector<int> numbers;
    vector<char> ops;
    for( size_t i = 0; i < input.size(); )
    {
        char c = input[i];
        if( c == '+' || c == '-' || c == '*' )
        {
            ops.push_back(c);
            i++;
        }
        else
        {
            int n = 0;
            while( input[i] >= '0' && input[i] <= '9' )
            {
                n = n * 10;
                n += input[i] - '0';
                i++;
            }
            numbers.push_back(n);
        }
    }
    
    return _diffWayToCompute( numbers, ops, 0, (int)numbers.size() );
}

void testDiffWayToCompute()
{
    vector<string> tests = {
        "10+5",
        "",
        "2-1-1",
        "2*3-4*5"
    };
    for( auto& s : tests )
    {
        auto v = diffWaysToCompute(s);
        for( auto& i : v )
            cout << i << ", ";
        cout << endl;
    }
}

#pragma mark - binaryTreePaths
//Given a binary tree, return all root-to-leaf paths.
//
//For example, given the following binary tree:
//
//   1
// /   \
//2     3
// \
//  5
//All root-to-leaf paths are:
//
//["1->2->5", "1->3"]
void _binaryTreePaths(TreeNode* node, vector<int>& s, vector<string>& out )
{
    if( node == nullptr )    return;
    
    s.push_back( node->val );
    
    if( node->left == nullptr && node->right == nullptr )
    {
        stringstream ss;
        for( auto& i : s )
            ss << to_string(i) << "->";
        
        string s = ss.str();
        s.erase(s.size() - 2);
        out.push_back(s);
    }
    
    _binaryTreePaths(node->left, s, out );
    _binaryTreePaths(node->right, s, out );

    s.pop_back();
}

vector<string> binaryTreePaths(TreeNode* root)
{
    vector<int> s;
    vector<string> out;
    _binaryTreePaths(root, s, out);
    return out;
}

void testBinaryTreePaths()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->right = new TreeNode(5);
    root->right = new TreeNode(3);
    auto o = binaryTreePaths(root);
    for( auto& s : o )
    {
        cout << s << endl;
    }
}

#pragma mark - addDigits
//Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.
//
//For example:
//
//Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.
//
//Follow up:
//Could you do it without any loop/recursion in O(1) runtime?
//Hint:
//
//A naive implementation of the above process is trivial. Could you come up with other methods?
//What are all the possible results?
//How do they occur, periodically or randomly?
//You may find this Wikipedia article useful. https://en.wikipedia.org/wiki/Digital_root
int addDigits(int num)
{
    return num < 9 ? num : ( num % 9 == 0 ? 9 : num % 9 );
}

#pragma mark - singleNumber
//Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.
//
//For example:
//
//Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].
//
//Note:
//The order of the result is not important. So in the above example, [5, 3] is also correct.
//Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
vector<int> singleNumber(vector<int>& nums) {
    int mask = 0;
    for( const auto& i : nums )
        mask ^= i;
    
    mask &= ~( mask - 1 );
    vector<int> out(2, 0);
    for( const auto& i : nums )
    {
        if( ( i & mask ) == 0 )
            out[0] ^= i;
        else
            out[1] ^= i;
    }
    return out;
}

void testSingleNumber()
{
    vector<int> t = {1, 2, 1, 3, 2, 5};
    vector<int> o = singleNumber(t);
    cout << o[0] << " " << o[1] << endl;
}

#pragma mark - isUgly
//Write a program to check whether a given number is an ugly number.
//
//Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.
//
//Note that 1 is typically treated as an ugly number.
bool isUgly(int num)
{
    if( num <= 0 )
        return false;

    if( num % 2 == 0 && isUgly( num / 2) )
        return true;
    
    if( num % 3 == 0 && isUgly( num / 3 ) )
        return true;
    
    if( num % 5 == 0 && isUgly( num / 5 ) )
        return true;
    
    return num == 1;
}

void testIsUgly()
{
    vector<pair<int, bool>> tests =
    {
        { 0, false },
        { 1, true },
        { 2, true },
        { 3, true },
        { 4, true },
        { 5, true },
        { 6, true },
        { 7, false },
        { 8, true },
        { 14, false }
    };
    
    for( const auto& p : tests )
        cout << p.first << "->" << BoolToStr( isUgly( p.first) == p.second ) << endl;
}

#pragma mark - nthUglyNumber
//Write a program to find the n-th ugly number.
//
//Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
//
//Note that 1 is typically treated as an ugly number.
//
//Hint:
//
//The naive approach is to call isUgly for every number until you reach the nth one. Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.
//An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
//The key is how to maintain the order of the ugly numbers. Try a similar approach of merging from three sorted lists: L1, L2, and L3.
//Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).
int nthUglyNumber(int n)
{
    if( n <= 0 ) return 0;

    vector<int> out(1, 1);
    int twoIdx = 0, threeIdx = 0, fiveIdx = 0;
    while( out.size() < n )
    {
        int o2 = out[twoIdx] * 2;
        int o3 = out[threeIdx] * 3;
        int o5 = out[fiveIdx] * 5;
        int o = min( min( o2, o3 ), o5);
        out.push_back(o);
        if( o == o2 )   twoIdx++;
        if( o == o3 )   threeIdx++;
        if( o == o5 )   fiveIdx++;
    }
    
    return out.back();
}

void testNthUglyNumber()
{
    for( int i = 0; i < 20; i++ )
        cout << nthUglyNumber(i) << " ";
}

#pragma mark - run

void Level20::Run()
{
    using namespace Level20Functions;
    testNthUglyNumber();
}

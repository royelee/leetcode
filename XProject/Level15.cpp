//
//  Level15.cpp
//  XProject
//
//  Created by Roye Li on 8/15/16.
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

using namespace std;

#pragma mark - fractionToDecimal
//Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
//
//If the fractional part is repeating, enclose the repeating part in parentheses.
//
//For example,
//
//Given numerator = 1, denominator = 2, return "0.5".
//Given numerator = 2, denominator = 1, return "2".
//Given numerator = 2, denominator = 3, return "0.(6)".
//
// Hint:
//No scary math, just apply elementary math knowledge. Still remember how to perform a long division?
//Try a long division on 4/9, the repeating part is obvious. Now try 4/333. Do you see a pattern?
//Be wary of edge cases! List out as many test cases as you can think of and test your code thoroughly.
string fractionToDecimal(int numerator, int denominator)
{
    double f = numerator * 1.0 / denominator;
    
    long long num = numerator;
    long long denom = denominator;
    num = abs(num);
    denom = abs(denom);
    
    long long big = num / denom;
    long long remain = num % denom;
    if( remain == 0 )
    {
        string out = to_string(big);
        if( f < 0 )
            out.insert(out.begin(), '-');
        
        return out;
    }
    
    string out;
    stringstream ss;
    int i = 0;
    map< long long , int > map;
    while( remain != 0 )
    {
        if( map.find(remain) != map.end() )
        {
            // find repeat.
            out = ss.str();
            int repeatIndex = map[remain];
            out.insert(out.begin() + repeatIndex, '(' );
            out.insert(out.end(), ')');
            string before = to_string(big) + ".";
            out.insert(0, before );
            break;
        }
        
        map[remain] = i;
        remain = remain * 10;
        ss << to_string(remain / denom);
        remain = remain % denom;
        
        if( remain == 0 )
        {
            // No repeat done.
            out = ss.str();
            string before = to_string(big) + ".";
            out.insert(0, before );
        }

        i++;
    }
    
    if( f < 0 )
        out.insert(out.begin(), '-');

    return out;
}

void testFractionToDecimal()
{
    vector<int> tests = {
        -1, -2147483648,
        1,6,
        1,3,
        1,5,
        1,214748364,
        1, 333,
        2, 3,
        4, 15,
        1, 2,
        2, 1,
        4, 333,
    };
    for( int i = 0; i < tests.size() / 2; i++ )
    {
        int numerator = tests[ 2 * i ];
        int denominator = tests[ 2 * i + 1 ];
        string s = fractionToDecimal(numerator, denominator);
        cout << "Fraction=" << s << endl;
    }
    for( int i = 3; i < 100; i++ )
    {
        cout << "Testing 4/" << i << endl;
        string s = fractionToDecimal(4, i);
        if( s.size() > 50 )
            cout << "_--______----_____" << endl;
        cout << "Fraction=" << s << endl;
    }
}

//Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
//
//The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
//
//You may assume that each input would have exactly one solution.
//
//Input: numbers={2, 7, 11, 15}, target=9
//Output: index1=1, index2=2
#pragma mark - twoSum
vector<int> twoSum(vector<int>& numbers, int target) {
    vector<int> out;
    size_t begin = 0;
    size_t end = numbers.size() - 1;
    while( begin < end )
    {
        long long sum = numbers[begin] + numbers[end];
        if( sum < target )
            begin++;
        else if( sum > target )
            end--;
        else
        {
            out.push_back((int)begin + 1);
            out.push_back((int)end + 1);
            break;
        }
            
    }
    return out;
}

void testTwoSum()
{
    vector<int> t = {2,7,11,15};
    auto r = twoSum(t, 9);
    for( auto& i : r )
        cout << i << ", ";
}

#pragma mark - convertToTitle
//Given a positive integer, return its corresponding column title as appear in an Excel sheet.
//
//For example:
//
//    1 -> A
//    2 -> B
//    3 -> C
//    ...
//    26 -> Z
//    27 -> AA
//    28 -> AB 
//Credits:
//Special thanks to @ifanchu for adding this problem and creating all test cases.
string convertToTitle(int n)
{
    int r = n;
    string output;
    while( r > 0 )
    {
        int l = (r - 1 ) % 26;
        output.insert( output.begin(), 'A' + l );
        
        r = (r - 1) / 26;
    }

    return output;
}

void testConvertToTitle()
{
    for( int i = 1; i < 26 * 26 * 3 ; i++ )
    {
        cout << i << "  = " << convertToTitle(i) << endl;
    }
}

#pragma mark - majorityElement
//Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.
//
//You may assume that the array is non-empty and the majority element always exist in the array.
static int majorityElement(vector<int>& nums)
{
    map<int, int> countMap;
    for( size_t i = 0; i < nums.size(); i++ )
    {
        if( countMap.find(nums[i]) != countMap.end() )
        {
            countMap[nums[i]] = countMap[nums[i]] + 1;
        }
        else
        {
            countMap[nums[i]] = 1;
        }
        
        if( countMap[nums[i]] > nums.size() / 2 )
            return nums[i];
    }
    
    return 0;
}

#pragma mark - titleToNumber
//Given a column title as appear in an Excel sheet, return its corresponding column number.
//
//For example:
//
//    A -> 1
//    B -> 2
//    C -> 3
//    ...
//    Z -> 26
//    AA -> 27
//    AB -> 28
int titleToNumber(string s)
{
    int r = 0;
    while( s.size() > 0 )
    {
        int c = s[0];
        int num = c - 'A' + 1;
        r = r * 26 + num;
        
        s.erase(0, 1);
    }
    
    return r;
}

void testTitleToNumber()
{
    for( int i = 1; i < 26 * 26 * 3 ; i++ )
    {
        string s = convertToTitle(i);
        cout << i << "  = " << s << " reverse = " << titleToNumber(s) << endl;
    }
}

#pragma mark - trailingZeroes
//Given an integer n, return the number of trailing zeroes in n!.
//
//Note: Your solution should be in logarithmic time complexity.
//
int trailingZeroes(int n)
{
    long long i = 5;
    long long r = n / i;
    i *= 5;
    while( i <= n )
    {
        r += n / i;
        i *= 5;
    }
    
    return (int)r;
}

void testTrailingZeroes()
{
    for( int i = 1; i < 626; i++ )
        cout << i << " = " << trailingZeroes(i) << endl;
}

#pragma mark - BSTIterator
//Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
//
//Calling next() will return the next smallest number in the BST.
//
//Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
    stack<TreeNode*> m_stack;
public:
    void PushToStack( TreeNode *root )
    {
        TreeNode* it = root;
        while( it )
        {
            m_stack.push(it);
            it = it->left;
        }
    }

    BSTIterator(TreeNode *root) {
        PushToStack( root );
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !m_stack.empty();
    }
    
    /** @return the next smallest number */
    int next() {
        int out = -1;
        
        if(!m_stack.empty())
        {
            TreeNode* top = m_stack.top();
            if( top->left == nullptr && top->right == nullptr )
            {
                out = top->val;
                m_stack.pop();
            }
            else
            {
                out = top->val;
                m_stack.pop();
                PushToStack(top->right);
            }
        }
        
        return out;
    }
};


/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
void testBSTIterator()
{
    //     15
    //    /
    //   4
    //  /  \
    // 2    7
    //    /   \
    //   5     9
    //    \   /
    //     6 8
    TreeNode* root = new TreeNode(15);
    root->left = new TreeNode(4);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(7);
    root->left->right->left = new TreeNode(5);
    root->left->right->left->right = new TreeNode(6);
    root->left->right->right = new TreeNode(9);
    root->left->right->right->left = new TreeNode(8);
    BSTIterator i = BSTIterator(root);
    while (i.hasNext())
        cout << i.next() << " ";
}

#pragma mark - largestNumber
//Given a list of non negative integers, arrange them such that they form the largest number.
//
//For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.
//
//Note: The result may be very large, so you need to return a string instead of an integer.
string largestNumber(vector<int>& nums)
{
    if( nums.size() == 0 )
        return "0";
    
    vector<string> numStrs;
    for( auto i : nums )
        numStrs.push_back( to_string( i ) );
    
    // Sort the array
    sort( numStrs.begin(), numStrs.end(), []( string& l, string& r )
         {
             string lr = l + r;
             string rl = r + l;
             return lr > rl;
         });
    
    if( numStrs[0] == "0" )
        return "0";
    
    // Combine them
    stringstream ss;
    for( auto& i : numStrs )
        ss << i;
    
    return ss.str();
}

void testLargestNumber()
{
    vector<vector<int>> tests =
    {
        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        { 5, 0, 0, 4, 0 },
        { 9, 3, 1, 921 },// => 992131
        { 3, 30, 34 }, // => 34 3 30
        { 3, 30 }, // => 330
        { 9, 3, 5, 932, 934 }, //  => 9 934 932 5 3
        { 9, 9, 998 },  // => 9 9 998
        { 9, 998 }, // => 9 998
        { 91, 94 } // => 94 91
    };
    for( auto& t : tests )
        cout << largestNumber( t ) << endl;
}

#pragma mark - rotate
//Rotate an array of n elements to the right by k steps.
//
//For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].
//
//Note:
//Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
namespace L15 {
    
void reverse(vector<int>& nums, int begin, int end )
{
    while( begin < end )
    {
        swap( nums[begin], nums[end] );
        begin++;
        end--;
    }
}

void rotate(vector<int>& nums, int k)
{
    k = k % nums.size();
    reverse(nums, 0, (int)nums.size() - 1);
    reverse(nums, 0, k - 1 );
    reverse(nums, k, (int)nums.size() - 1);
}

void testRotate()
{
    for( int i = 0; i < 10; i++ )
    {
        cout << "Test case " << i << endl;
        vector<int> test = {1, 2, 3, 4, 5, 6};
        rotate( test, i );
        for( auto v : test )
            cout << v << " ";
        cout << endl;
    }
}
    
} // namespace L15

#pragma mark - reverseBits
//Reverse bits of a given 32 bits unsigned integer.
//
//For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).
//
//Follow up:
//If this function is called many times, how would you optimize it?
uint32_t reverseBits(uint32_t n)
{
    uint32_t out = 0;
    for( size_t i = 0; i < 32; i++ )
    {
        uint32_t mask1 = 1 << i;
        uint32_t mask2 = 1 << (31 - i);
        if( ( n & mask1 ) != 0 )
            out |= mask2;
    }
    
    return out;
}

void testReverseBits()
{
    uint32_t i = 43261596;
    cout << reverseBits( i ) << endl;
}

#pragma mark - findRepeatedDnaSequences
//All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
//
//Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.
//
//For example,
//
//Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",
//
//Return:
//["AAAAACCCCC", "CCCCCAAAAA"].
vector<string> findRepeatedDnaSequences(string s)
{
    int32_t mask = 0x000fffff;
    auto convertFn = []( char c )
    {
        switch(c)
        {
            case 'A': return 0;
            case 'C': return 1;
            case 'G': return 2;
            case 'T': return 3;
        }
        return 0;
    };
    set<int32_t> reorder;
    set<string> out;
    int32_t init = 0;
    if( s.length() >= 10 )
    {
        for( int j = 0; j < 10; j++ )
            init = (init << 2) + convertFn(s[j]);
        
        reorder.insert(init);
    }

    for( size_t i = 10; i < s.length(); i++ )
    {
        init = ( init << 2 ) & mask;
        init += convertFn(s[i]);
        
        if(reorder.find(init) != reorder.end() )
            out.insert(s.substr(i - 9, 10));
        else
            reorder.insert(init);
    }
    
    vector<string> output;
    for( const auto& v : out )
        output.push_back(v);
    
    return output;
}

void testFindRepeatedDnaSequences()
{
    vector<string> tests = {
        "AAAAAAAAAAAAAAAAAAAA",
        "AAAAAAAAAA",
        "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",
        "CCCCCCCCCCC"
    };
    for( auto s : tests )
    {
        vector<string> out = findRepeatedDnaSequences(s);
        for( auto& v : out )
            cout << v << " ";
        cout << endl;
    }
}

#pragma mark - run

void Level15::Run()
{
    testFindRepeatedDnaSequences();
}
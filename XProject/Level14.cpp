//
//  Level14.cpp
//  XProject
//
//  Created by Roye Li on 8/1/16.
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

#pragma mark - evalRPN
//Evaluate the value of an arithmetic expression in Reverse Polish Notation.
//
//Valid operators are +, -, *, /. Each operand may be an integer or another expression.
//
//Some examples:
//["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
//["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
int evalRPN(vector<string>& tokens)
{
    vector<int> values;
    values.reserve(tokens.size());
    for( const string& token : tokens )
    {
        if( token == "+" || token == "-" || token == "*" || token == "/" )
        {
            if( values.size() >= 2 )
            {
                int v1 = values.back();
                values.pop_back();
                int v2 = values.back();
                values.pop_back();

                int r = 0;
                if( token == "+" )
                    r = v1 + v2;
                else if( token == "-" )
                    r = v2 - v1;
                else if( token == "*" )
                    r = v1 * v2;
                else
                    r = v2 / v1;
                
                values.push_back(r);
            }
            else
            {
                // something wrong with input.
                return -1;
            }
        }
        else
        {
            values.push_back(stoi(token));
        }
    }
    
    return values.back();
}

void testEvalRPN()
{
    vector<vector<string>> tests = { {"2", "1", "+", "3", "*"}, {"4", "13", "5", "/", "+"}};
    for( auto& t : tests )
        cout << evalRPN(t) << endl;
    
    vector<string> t1 = ReadVectorFromFile<string>("evalRPN", [](string s) {
        s.erase(std::remove_if(s.begin(), s.end(), [](char c) ->bool { return c == '\"';}), s.end());
        return s;
    });
    cout << evalRPN(t1) << endl;
}

#pragma mark - reverseWords
//Given an input string, reverse the string word by word.
//
//For example,
//Given s = "the sky is blue",
//return "blue is sky the".
//
//Update (2015-02-12):
//For C programmers: Try to solve it in-place in O(1) space.
//Clarification:
//What constitutes a word?
//A sequence of non-space characters constitutes a word.
//Could the input string contain leading or trailing spaces?
//Yes. However, your reversed string should not contain leading or trailing spaces.
//How about multiple spaces between two words?
//Reduce them to a single space in the reversed string.
string getNextWord(string& s, int start, int& next )
{
    stringstream ss;
    bool begined = false;
    int i = start;
    for( ; i < s.length(); i++ )
    {
        if( s[i] == ' ' )
        {
            if( begined )
            {
                break;
            }
            else
                continue;
        }
        else
        {
            ss << s[i];
            begined = true;
        }
    }
    
    string rtn = ss.str();
    next = i;
    return rtn;
}

void reverseWords(string &s)
{
    int i = 0;
    vector<string> output;
    while( i < s.size() )
    {
        int next = i;
        string word = getNextWord(s, i, next);
        if( word.size() > 0 )
            output.push_back( word );
        i = next + 1;
    }
    
    stringstream ss;
    for( auto it = output.rbegin(); it != output.rend(); it++ )
    {
        ss << *it;
        if( it + 1 != output.rend() )
            ss << " ";
    };
    
    s = ss.str();
}

void testReverseWords()
{
    vector<string> tests =
    {
        "    a    ",
        "the sky is blue",
        "    ",
    };

    for( auto& s : tests )
    {
        string currentString = s;
        reverseWords( currentString );
        cout << currentString << endl;
    }
}

#pragma mark - maxProduct
//Find the contiguous subarray within an array (containing at least one number) which has the largest product.
//
//For example, given the array [2,3,-2,4],
//the contiguous subarray [2,3] has the largest product = 6.
int maxProduct(vector<int>& nums)
{
    vector<int> posNums( nums.size() );
    vector<int> negNums( nums.size() );
    int maxValue = numeric_limits<int>::min();
    for( size_t i = 0; i < nums.size(); i++ )
    {
        int v = nums[i];
        if( i == 0 )
        {
            if( v > 0 )
                posNums[i] = v;
            else
                negNums[i] = v;
        }
        else
        {
            if( v > 0 )
            {
                posNums[i] = max( posNums[i-1] * v, v );
                negNums[i] = min( negNums[i-1] * v, v );
            }
            else
            {
                negNums[i] = min( posNums[i-1] * v, v );
                posNums[i] = max( negNums[i-1] * v, v );
            }
        }
        
        if( posNums[i] != 0 )
            maxValue = max( maxValue, posNums[i] );
        else
            maxValue = max( maxValue, negNums[i] );
    }
    
    return maxValue;
}

void testMaxProduct()
{
    vector<vector<int>> tests = {
        { -1 },
        { 2,3,-2,4 },
        { 1,2,-1,3,4,-2 },
        { 2,-2, 3 },
        { 1, 2, -7, 4, 5 },
        { -2, -3},
        { 2, 3 },
        { 4, 2, -1, 2, -1, 2, -1, 10 },
    };
    for( auto& t : tests )
        cout << maxProduct(t) << endl;
}

#pragma mark - findMin
//Suppose a sorted array is rotated at some pivot unknown to you beforehand.
//
//(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
//
//Find the minimum element.
//
//You may assume no duplicate exists in the array.
int findMin(vector<int>& nums)
{
    if( nums.size() == 1 )
        return nums[0];

    // 3 possibles
    // 12345 << -- all sorted
    // 51234 << -- in first half
    // 45123 << -- in first half
    // 34512 << -- in second half
    // 23451 << -- in second half
    int begin = 0;
    int end = nums.size() - 1;
    while( end - begin != 1 )
    {
        int mid = ( begin + end ) / 2;
        if( nums[begin] < nums[mid] && nums[mid] < nums[end] )
            return nums[begin];
        else if( nums[begin] > nums[mid] && nums[mid] < nums[end] )
        {
            end = mid;
        }
        else if( nums[begin] < nums[mid] && nums[mid] > nums[end] )
        {
            begin = mid;
        }
    }

    return min( nums[begin], nums[end] );
}

void testFindMin()
{
    vector<vector<int>> tests = {
        { 4, 5, 6, 7, 0, 1, 2 },
        { 1, 2 },
        { 5, 1, 2, 3, 4 },
        { 2, 3, 4, 5, 1 }
    };
    
    for( auto& t : tests )
        cout << findMin(t) << endl;
}

#pragma mark - MinStack
//Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
//
//push(x) -- Push element x onto stack.
//pop() -- Removes the element on top of the stack.
//top() -- Get the top element.
//getMin() -- Retrieve the minimum element in the stack.
//Example:
//MinStack minStack = new MinStack();
//minStack.push(-2);
//minStack.push(0);
//minStack.push(-3);
//minStack.getMin();   --> Returns -3.
//minStack.pop();
//minStack.top();      --> Returns 0.
//minStack.getMin();   --> Returns -2.
class MinStack {
    vector<int> m_stack;
    int m_minValue { numeric_limits<int>::max() };

public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        m_stack.push_back(x);
        if( m_stack.size() == 1 )
            m_minValue = x;
        else
            m_minValue = min( m_minValue, x );
    }
    
    void pop() {
        m_stack.pop_back();
        m_minValue = m_stack.front();
        for( auto v : m_stack )
            m_minValue = min(v, m_minValue);
    }
    
    int top() {
        return m_stack.back();
    }
    
    int getMin() {
        return m_minValue;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
void testMinStack()
{
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << minStack.getMin() << endl;;//   --> Returns -3.
    minStack.pop();
    cout << minStack.top() << endl;//      --> Returns 0.
    cout << minStack.getMin() << endl;//   --> Returns -2.
    

    MinStack m1;
    m1.push(2147483646);
    m1.push(2147483646);
    m1.push(2147483647);
    cout << m1.top() << endl;
    m1.pop();
    cout << m1.getMin() << endl;
    m1.pop();
    cout << m1.getMin() << endl;
    m1.pop();
    m1.push(2147483647);
    cout << m1.top() << endl;
    cout << m1.getMin() << endl; // << --- Wrong here, need to consider it's empty case
    m1.push(-2147483648);
    cout << m1.top() << endl;
    cout << m1.getMin() << endl;
    m1.pop();
    cout << m1.getMin() << endl;
//    ["constructor","null","null","null","2147483647","null","2147483646","null","2147483646","null","null","2147483647","2147483646","null","-2147483648","-2147483648","null","2147483647"]
//Expected:
//    ["constructor","null","null","null","2147483647","null","2147483646","null","2147483646","null","null","2147483647","2147483647","null","-2147483648","-2147483648","null","2147483647"]
}

#pragma mark - getIntersectionNode
//Write a program to find the node at which the intersection of two singly linked lists begins.
//
//
//For example, the following two linked lists:
//
//A:          a1 → a2
//                   ↘
//                     c1 → c2 → c3
//                   ↗            
//B:     b1 → b2 → b3
//begin to intersect at node c1.
//
//
//Notes:
//
//If the two linked lists have no intersection at all, return null.
//The linked lists must retain their original structure after the function returns.
//You may assume there are no cycles anywhere in the entire linked structure.
//Your code should preferably run in O(n) time and use only O(1) memory.
//Credits:
//Special thanks to @stellari for adding this problem and creating all test cases.
static ListNode *detectCycle(ListNode *head)
{
    if( head == nullptr )
        return nullptr;
    
    //    Fast = 2 * slow
    //    Slow = X + Y ( X - node went before into the circle, Y node went in circle )
    //    Fast = X + circleNum + Y ( circleNum - node went loop inside of circle )
    //    2X + 2Y = X + circleNum + Y
    //    => X+Y = circle Num = slow
    //    => X = slow – Y = circleNum - Y
    
    ListNode* oneStepIter = head;
    ListNode* twoStepIter = head;
    while( twoStepIter != nullptr )
    {
        oneStepIter = oneStepIter->next;
        twoStepIter = twoStepIter->next;
        if( twoStepIter == nullptr )
            return nullptr;
        
        twoStepIter = twoStepIter->next;
        if( oneStepIter == twoStepIter )
            break;
    }
    
    if( twoStepIter == nullptr )
        return twoStepIter;
    
    oneStepIter = head;
    while( oneStepIter != twoStepIter )
    {
        oneStepIter = oneStepIter->next;
        twoStepIter = twoStepIter->next;
    }
    
    return oneStepIter;
}

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *cur1 = headA, *cur2 = headB;
    while(cur1 != cur2){
        cur1 = cur1?cur1->next:headB;
        cur2 = cur2?cur2->next:headA;
    }
    return cur1;
}

void testGetIntersectionNode()
{
//    No intersection: [1,3,5,7,9,11,13,15,17,19,21]
//    [2]
    int a[] = {1,3,5,7,9,11,13,15,17,19,21};
    int b[] = {2};
    ListNode* headA = new ListNode(-1);
    ListNode* it = headA;
    for( int v : a )
    {
        it->next = new ListNode(v);
        it = it->next;
    }
    ListNode* headB = new ListNode(-1);
    it = headB;
    for( int v : b )
    {
        it->next = new ListNode(v);
        it = it->next;
    }
    ListNode* node = getIntersectionNode(headA->next, headB->next);
    if( node )
        cout << node->next;
}

#pragma mark - run

void Level14::Run()
{
    testGetIntersectionNode();
}
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
    for( size_t i = 0; i < numbers.size(); i++ )
    {
        int lookingFor = target - numbers[i];
        auto it = lower_bound(numbers.begin() + i + 1, numbers.end(), lookingFor );
        if( it < numbers.end() && *it == lookingFor )
        {
            out.push_back(i + 1);
            out.push_back(it - numbers.begin() + 1);
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

#pragma mark - run

void Level15::Run()
{
    testTwoSum();
}
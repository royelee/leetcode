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
    
    numerator = abs(numerator);
    denominator = abs(denominator);

    stringstream ss;
    size_t i = 0;
    bool fDot = false;
    int dotPos = -1;
    while( i < 100 )
    {
        int remainder = numerator % denominator;
        int quotient = numerator / denominator;
        if( remainder == 0 )
        {
            ss << to_string(quotient);
            break;
        }
        else
        {
            string s = to_string(quotient);
            ss << s;
            if( !fDot )
            {
                dotPos = (int)s.size();
                ss << ".";
                fDot = true;
            }
            numerator = 10 * remainder;
        }
        
        i++;
    }
    
    string out = ss.str();
    if( dotPos == -1 )
    {
        if( f < 0 )
            out.insert(out.begin(), '-');
        return out;
    }
    
    cout << "original = " << out << endl;
    int startRepeat = -1;
    int endRepeat = -1;
    size_t pos = dotPos + 1;
    while( pos < out.size() )
    {
        size_t firstOccurOfCurrentChar = out.find(out[pos], pos + 1);
        if( firstOccurOfCurrentChar == string::npos )
        {
            pos++;
            continue;
        }
        
        size_t i = 0;
        for( ; i < firstOccurOfCurrentChar - pos; i++ )
        {
            if( firstOccurOfCurrentChar + i >= out.size() || out[pos + i] != out[firstOccurOfCurrentChar + i] )
                break;
        }
        
        if( pos + i == firstOccurOfCurrentChar )
        {
            startRepeat = (int)pos;
            endRepeat = (int)firstOccurOfCurrentChar;
            break;
        }
        pos++;
    }
    
    if( startRepeat != -1 && endRepeat != -1 )
    {
        out.erase( endRepeat );
        out.insert(out.begin() + startRepeat, '(' );
        out.insert(out.end(), ')');
    }
    
    if( f < 0 )
        out.insert(out.begin(), '-');
    
    return out;
}


#pragma mark - run

void Level15::Run()
{
    vector<int> tests = {
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
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

#pragma mark - run

void Level14::Run()
{
    testReverseWords();
}
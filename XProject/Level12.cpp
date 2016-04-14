//
//  Level12.cpp
//  XProject
//
//  Created by Roye Li on 3/30/16.
//  Copyright (c) 2016 Roye Li. All rights reserved.
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

using namespace std;

#pragma mark - isPalindrome
//Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
//
//For example,
//"A man, a plan, a canal: Panama" is a palindrome.
//"race a car" is not a palindrome.
//
//Note:
//Have you consider that the string might be empty? This is a good question to ask during an interview.
//
//For the purpose of this problem, we define empty string as valid palindrome.
bool IsAlpahNumber( char c )
{
    return ( c >= 'a' && c <='z' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= '0' && c <= '9' );
}

bool isPalindrome(string s)
{
    // remove non-alphanumer
    s.erase( remove_if(s.begin(), s.end(), [](char c) {
        return !IsAlpahNumber(c);
    } ), s.end() );
    
    // make lower case.
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    
    if( s.length() == 0 )
        return true;
    
    size_t begin = 0;
    size_t end = s.length() - 1;
    
    while( begin < end )
    {
        if( s[begin] != s[end] )
            return false;
        
        begin++;
        end--;
    }
    
    return true;
}

void testIsPalindrome()
{
    cout << isPalindrome("A man, a plan, a canal: Panama") << endl;
    cout << isPalindrome("race a car") << endl;
}

#pragma mark - ladderLength
//Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:
//
//Only one letter can be changed at a time
//Each intermediate word must exist in the word list
//For example,
//
//Given:
//beginWord = "hit"
//endWord = "cog"
//wordList = ["hot","dot","dog","lot","log"]
//As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
//return its length 5.
//
//Note:
//Return 0 if there is no such transformation sequence.
//All words have the same length.
//All words contain only lowercase alphabetic characters.
int ladderLength(string beginWord, string endWord, vector<string>& wordList)
{
    size_t count = wordList.size() + 2;
    vector<vector<int>> dp( wordList.size() + 2,  std::vector<int>( count, numeric_limits<int>::max() ) );
    vector<string> words( wordList.size() );
    copy(wordList.begin(), wordList.end(), words.begin());
    words.insert(words.begin(), beginWord);
    words.push_back(endWord);
    
    for( size_t i = 0; i < count; i++ )
    {
        for( size_t j = i; j < count; j++ )
        {
            if( i == j )
            {
                dp[i][j] = 0;
                continue;
            }

            string& from = words[i];
            string& to = words[j];
            
            int different = 0;
            for( size_t k = 0; k < from.size(); k++ )
            {
                if( from[k] != to[k] )
                    different++;
                
                if( different > 1 )
                    break;
            }
            
            if( different == 1 )
            {
                dp[i][j] = 1;
            }
            
            // Update DP table.
            for( size_t k = 0; k < j; k++ )
            {
                if( dp[j][k] < numeric_limits<int>::max() )
                    dp[k][j] = min( dp[k][j], dp[j][k] + 1);
            }
            
            for( size_t k = 0; k < i; k++ )
            {
                if( dp[k][i] < numeric_limits<int>::max() )
                    dp[k][j] = min( dp[k][j], dp[k][i] + 1);
            }
        }
    }
    
    for( size_t i = 0; i < count; i++ )
    {
        for( size_t j = 0; j < count; j++ )
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    
    return dp[0][count - 1];
}

void testLadderLength()
{
//    unordered_set<string> wordList( {"hot","dot","dog","lot","log"} );
//    vector<string> wordList = {"hot","dot","dog","lot","log"};
    vector<string> wordList = {"log","dog","lot","dot","hot"};
    cout << ladderLength("hit", "cog", wordList);
}

#pragma mark - run

void Level12::Run()
{
    testLadderLength();
}
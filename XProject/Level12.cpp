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
bool canChange( const string& a, const string& b )
{
    if( a.size() != b.size() )
        return false;
    
    unsigned int diff = 0;
    for( size_t i = 0; i < a.size(); i++ )
    {
        if( a[i] != b[i] )
            diff++;
        
        if( diff > 1 )
            break;
    }
    
    return diff == 1;
}

void _ladderLength(string beginWord, string endWord, unordered_set<string>& wordList, int level, int& maxLevel )
{
    unordered_set<string> connectedWordList;
    for( const auto& word : wordList )
    {
        if( canChange( beginWord, word ) )
        {
            connectedWordList.insert(word);
        }
    }
    
    for( const auto& word : connectedWordList )
    {
        if( endWord == word )
        {
            maxLevel = min( maxLevel, level + 1 );
        }
        else
        {
            wordList.erase(word);
            _ladderLength( word, endWord, wordList, level + 1, maxLevel );
            wordList.insert(word);
        }
    }
}

int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList)
{
    wordList.erase(beginWord);
    wordList.insert(endWord);
    int maxLevel = numeric_limits<int>::max();
    _ladderLength( beginWord, endWord, wordList, 1, maxLevel );
    return maxLevel == numeric_limits<int>::max() ? 0 : maxLevel;
}

void testLadderLength()
{
#if 0
    unordered_set<string> wordList( {"hot","dot","dog","lot","log" } );
//    vector<string> wordList = {"hot","dot","dog","lot","log"};
//    vector<string> wordList = {"log","dog","lot","dot","hot"};
    cout << ladderLength("hit", "cog", wordList);
#else
    unordered_set<string> wordList( {"si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"} );
    cout << ladderLength("qa", "sq", wordList);
#endif
}

#pragma mark - run

void Level12::Run()
{
    testLadderLength();
}
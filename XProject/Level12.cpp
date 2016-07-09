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
#include <queue>
#include <fstream>

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

unordered_set<string> ConnectWords( string startWord, const unordered_set<string>& wordList )
{
    unordered_set<string> connects;
    for( size_t i = 0; i < startWord.size(); i++ )
    {
        string newWord = startWord;
        for( size_t j = 0; j < 26; j++ )
        {
            newWord[i] = 'a' + j;
            if( wordList.find( newWord ) != wordList.end() )
                connects.insert( newWord );
        }
    }
    
    return connects;
}

int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList)
{
    int level = 1;
    int levelIndex = 0;
    size_t levelNodes = 1;
    vector<string> stack;
    stack.push_back( beginWord );
    
    unordered_set<string> connecttedEndWord = ConnectWords( endWord, wordList );

    while( !stack.empty() )
    {
        string current = stack.front();
        stack.erase(stack.begin());
        
        
        if( connecttedEndWord.find( current ) != connecttedEndWord.end() )
        {
            // Found
            return level + 1;
        }
        else
        {
            unordered_set<string> connects = ConnectWords( current, wordList );
            for( const auto& cWord : connects )
            {
                stack.push_back(cWord);
                wordList.erase( cWord );
            }
        }
        
        levelIndex++;
        if( levelIndex == levelNodes )
        {
            level++;
            levelIndex = 0;
            levelNodes = stack.size();
        }
    }
    
    return 0;
}

void testLadderLength()
{
#if 1
    unordered_set<string> wordList1( {"hot","dot","dog","lot","log" } );
//    vector<string> wordList = {"hot","dot","dog","lot","log"};
//    vector<string> wordList = {"log","dog","lot","dot","hot"};
    cout << ladderLength("hit", "cog", wordList1) << endl;
    
    unordered_set<string> wordList2( {"a", "b", "c" } );
    cout << ladderLength("a", "c", wordList2) << endl;
    
    unordered_set<string> wordList3( {"hot","dog","cog","pot","dot"} );
    cout << ladderLength("hot", "dog", wordList3) << endl;
#else
    unordered_set<string> wordList( {"si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"} );
    cout << ladderLength("qa", "sq", wordList);
#endif
}

#pragma mark - sumNumbers
//Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
//
//An example is the root-to-leaf path 1->2->3 which represents the number 123.
//
//Find the total sum of all root-to-leaf numbers.
//
//For example,
//
//    1
//   / \
//  2   3
//The root-to-leaf path 1->2 represents the number 12.
//The root-to-leaf path 1->3 represents the number 13.
//
//Return the sum = 12 + 13 = 25.
void _sumNumbers( TreeNode* node, vector<int>& current, int& sum )
{
    if( node != nullptr )
    {
        current.push_back( node->val );
        
        if( node->left == nullptr && node->right == nullptr )
        {
            int cSum = 0;
            for( auto it = current.begin(); it != current.end(); it++ )
            {
                cSum = cSum * 10 + *it;
            }
            sum += cSum;
        }
        else
        {
            _sumNumbers( node->left, current, sum );
            _sumNumbers( node->right, current, sum );
        }
        
        current.pop_back();
    }
}

int sumNumbers(TreeNode* root)
{
    vector<int> c;
    int sum = 0;
    _sumNumbers( root, c, sum );
    return sum;
}

void testSumNumbers()
{
    TreeNode* node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->right = new TreeNode(3);
    cout << sumNumbers(node) << endl;
}

#pragma mark - solve
//Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
//
//A region is captured by flipping all 'O's into 'X's in that surrounded region.
//
//For example,
//X X X X
//X O O X
//X X O X
//X O X X
//After running your function, the board should be:
//
//X X X X
//X X X X
//X X X X
//X O X X
void _markBoard( vector<vector<char>>& board, size_t width, size_t height, int i, int j )
{
    queue<pair<int, int>> queue;
    if( board[i][j] == 'O' )
        queue.push(make_pair(i, j));
    while( !queue.empty() )
    {
        auto p = queue.front();
        queue.pop();
        
        int x = p.first;
        int y = p.second;
        if( board[x][y] == 'O' )
        {
            board[x][y] = 'N';  // No revert
            
            if( x - 1 >= 0 )
                queue.push(make_pair(x - 1, y));
            if( y - 1 >= 0 )
                queue.push(make_pair(x, y - 1));
            if( x + 1 < height )
                queue.push(make_pair(x + 1, y));
            if( y + 1 < width )
                queue.push(make_pair(x, y + 1));
        }
    }
}

void solve(vector<vector<char>>& board)
{
    if( board.size() > 0 )
    {
        size_t width = board[0].size();
        size_t height = board.size();
        for( int x = 0; x < width; x++ )
        {
            _markBoard( board, width, height, 0, x );
            _markBoard( board, width, height, (int) height - 1, x );
        }
        
        for( int i = 0; i < height; i++ )
        {
            _markBoard( board, width, height, i, 0 );
            _markBoard( board, width, height, i, (int) width - 1 );
        }
    }

    for( size_t i = 0; i < board.size(); i++ )
    {
        for( size_t j = 0; j < board[i].size(); j++ )
        {
            if( board[i][j] == 'N' )
                board[i][j] = 'O';
            else if( board[i][j] == 'O' )
                board[i][j] = 'X';
        }
    }
}

void testSolve()
{
//    vector<string> b = {
//        "XXXX",
//        "XOOX",
//        "XXOX",
//        "XOXX"
//    };
//    vector<string> b = { "XOXOXO","OXOXOX","XOXOXO","OXOXOX"};
    vector<string> b = {"XOX","XOX","XOX"};
    vector<vector<char>> board;
    for( const auto& s : b )
    {
        vector<char> vc(s.begin(), s.end());
        
        board.push_back(vc);
    }
    
    cout << "BBBBB" << endl;
    for( size_t i = 0; i < board.size(); i++ )
    {
        for( size_t j = 0; j < board[i].size(); j++ )
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    
    solve(board);

    cout << "AAAAA" << endl;
//    ofstream file("board.txt");
    for( size_t i = 0; i < board.size(); i++ )
    {
        for( size_t j = 0; j < board[i].size(); j++ )
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
//    file.close();
}

#pragma mark - partition
//Given a string s, partition s such that every substring of the partition is a palindrome.
//
//Return all possible palindrome partitioning of s.
//
//For example, given s = "aab",
//Return
//
//[
//  ["aa","b"],
//  ["a","a","b"]
//]
bool isPalindome( const string& s )
{
    size_t length = s.size();
    if(length == 0)
        return false;

    for( size_t i = 0; i < length / 2; i++ )
    {
        if( s[i] != s[length - i -1] )
            return false;
    }
    
    return true;
}

vector<vector<string>> partition(string s)
{
    // TODO : Use longestPalindromeDP get s palindrome then we can query it faster.
    vector<vector<string>> r;
    for( size_t i = 0; i < s.size(); i++ )
    {
        string sub = s.substr(0, i + 1);
        if( isPalindrome(sub) )
        {
            vector<vector<string>> subR;
            if( i + 1 < s.size() )
            {
                string rest = s.substr( i + 1 );
                subR = partition( rest );
            }
            else
            {
                subR.push_back({});
            }
            
            for( auto& v : subR )
            {
                v.insert(v.begin(), sub);
                r.push_back( v );
            }
        }
    }
    
    return r;
}

static void testPartition()
{
    vector<string> tests =
    {
        "",
        "a",
        "aa",
        "aab",
        "aba",
        "aabbaa",
    };
    
    for( const auto& test : tests )
    {
        cout << "Testing " << test << endl;
        const auto& r = partition(test);
        for( const auto& v : r )
        {
            for( const auto& s : v )
                cout << s << ", ";
            cout << endl;
        }
    }
}

#pragma mark - run

void Level12::Run()
{
    testPartition();
}
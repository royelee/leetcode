//
//  Level21.cpp
//  XProject
//
//  Created by Roye Li on 1/12/17.
//  Copyright © 2017 Roye Li. All rights reserved.
//

#include <stdio.h>

#include "Level.h"

#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
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

#pragma mark - PeekingIterator
//Given an Iterator class interface with methods: next() and hasNext(), design and implement a PeekingIterator that support the peek() operation -- it essentially peek() at the element that will be returned by the next call to next().
//
//Here is an example. Assume that the iterator is initialized to the beginning of the list: [1, 2, 3].
//
//Call next() gets you 1, the first element in the list.
//
//Now you call peek() and it returns 2, the next element. Calling next() after that still return 2.
//
//You call next() the final time and it returns 3, the last element. Calling hasNext() after that should return false.
//
//Hint:
//
//Think of "looking ahead". You want to cache the next element.
//Is one variable sufficient? Why or why not?
//Test your design with call order of peek() before next() vs next() before peek().
//For a clean implementation, check out Google's guava library source code.
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
    Data* data;
    int i = 0;
    vector<int> m_data;
public:
    Iterator(const vector<int>& nums) : m_data( nums ) {};
    Iterator(const Iterator& iter) : m_data( iter.m_data ), i( iter.i ) {}
    virtual ~Iterator() {}
    // Returns the next element in the iteration.
    int next() { return m_data[i++]; }
    // Returns true if the iteration has more elements.
    bool hasNext() const { return i + 1 < m_data.size(); }
};

class PeekingIterator : public Iterator {
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
    }
    
    // Returns the next element in the iteration without advancing the iterator.
    int peek()
    {
        PeekingIterator bak( *this );
        return bak.next();
    }
    
    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        return Iterator::next();
    }
    
    bool hasNext() const {
        return Iterator::hasNext();
    }
};

void testPeekingIterator()
{
    vector<int> test = { 1, 2, 3 };
    PeekingIterator it1( test );
    cout << BoolToStr( it1.next() == 1 ) << endl;
    cout << BoolToStr( it1.peek() == 2 ) << endl;
    cout << BoolToStr( it1.next() == 2 ) << endl;
    cout << BoolToStr( it1.next() == 3 ) << endl;
    cout << BoolToStr( it1.hasNext() == false ) << endl;
    
    PeekingIterator it2( test );
    cout << BoolToStr( it2.peek() == 1 ) << endl;
    cout << BoolToStr( it2.peek() == 1 ) << endl;
    cout << BoolToStr( it2.next() == 1 ) << endl;
    cout << BoolToStr( it2.next() == 2 ) << endl;
    cout << BoolToStr( it2.peek() == 3 ) << endl;
}

#pragma mark - wordPattern
//Given a pattern and a string str, find if str follows the same pattern.
//
//Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.
//
//Examples:
//pattern = "abba", str = "dog cat cat dog" should return true.
//pattern = "abba", str = "dog cat cat fish" should return false.
//pattern = "aaaa", str = "dog cat cat dog" should return false.
//pattern = "abba", str = "dog dog dog dog" should return false.
//Notes:
//You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.
bool wordPattern(string pattern, string str)
{
    vector<string> tokens;
    istringstream iss(str);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
    
    if( tokens.size() != pattern.size() )
        return false;
    
    map<string, char> m;
    map<char, string> rm;
    for( size_t i = 0; i < pattern.size(); i++ )
    {
        char c = pattern[i];
        auto t = tokens[i];
        if( m.find( t ) == m.end() )
        {
            if( rm.find( c ) == rm.end() )
            {
                m[t] = c;
                rm[c] = t;
            }
            else
            {
                if( rm[c] != t )
                    return false;
            }
        }
        else
        {
            if( m[t] != c )
                return false;
        }
    }
    
    return true;
}

void testWordPattern()
{
    //pattern = "abba", str = "dog cat cat dog" should return true.
    //pattern = "abba", str = "dog cat cat fish" should return false.
    //pattern = "aaaa", str = "dog cat cat dog" should return false.
    //pattern = "abba", str = "dog dog dog dog" should return false.
    vector<pair< vector<string>, bool > > tests =
    {
        { { "abba", "dog cat cat dog" }, true },
        { { "abba", "dog cat cat fish" }, false },
        { { "aaaa", "dog cat cat dog" }, false },
        { { "abba", "dog dog dog dog" }, false }
    };
    for( auto& p : tests )
    {
        cout << p.first[0] << " " << p.first[1] << endl;
        cout << BoolToStr( wordPattern(p.first[0], p.first[1]) == p.second ) << endl;
    }
}

#pragma mark - gameOfLife
//According to the Wikipedia's article( https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) : "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."
//
//Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):
//
//Any live cell with fewer than two live neighbors dies, as if caused by under-population.
//Any live cell with two or three live neighbors lives on to the next generation.
//Any live cell with more than three live neighbors dies, as if by over-population..
//Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
//Write a function to compute the next state (after one update) of the board given its current state.
//
//Follow up: 
//Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
//In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?
void gameOfLife(vector<vector<int>>& board)
{
    if( board.size() == 0 )
        return;

    size_t rowCount = board.size();
    size_t colCount = board[0].size();
    vector<vector<int>> newBoard(rowCount, vector<int>(colCount));
    auto nlc = [rowCount, colCount](vector<vector<int>>& b, int row, int col) -> int{
        int c = 0;
        if( row - 1 >= 0 && col - 1 >= 0 && b[row-1][col-1] == 1 ) c++;
        if( row - 1 >= 0 && b[row-1][col] == 1 )    c++;
        if( row - 1 >= 0 && col + 1 < colCount && b[row-1][col+1] == 1 )    c++;
        if( col - 1 >= 0 && b[row][col-1] == 1 )    c++;
        if( col + 1 < colCount && b[row][col+1] == 1)   c++;
        if( row + 1 < rowCount && col - 1 >= 0 && b[row+1][col-1] == 1 )    c++;
        if( row + 1 < rowCount && b[row+1][col] == 1 )  c++;
        if( row + 1 < rowCount && col + 1 < colCount && b[row+1][col+1] == 1 )  c++;
        return c;
    };
    
    for( int row = 0; row < rowCount; row++ )
    {
        for( int col = 0; col < colCount; col++ )
        {
            int c = nlc( board, row, col );
            if( board[row][col] == 1 )
            {
                if( c <= 1 )
                    newBoard[row][col] = 0;
                else if( c <= 3 )
                    newBoard[row][col] = 1;
                else
                    newBoard[row][col] = 0;
            }
            else if( c == 3 )
                newBoard[row][col] = 1;
        }
    }
    
    board = newBoard;
}

void testGameOfLife()
{
    vector<vector<int>> board = {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,1,1,1,0},
        {0,1,1,1,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    };
    gameOfLife(board);
    size_t rowCount = board.size();
    size_t colCount = board[0].size();
    
    // Expect :
    //    [[0,0,0,0,0,0],
    //     [0,0,0,1,0,0],
    //     [0,1,0,0,1,0],
    //     [0,1,0,0,1,0],
    //     [0,0,1,0,0,0],
    //     [0,0,0,0,0,0]]
    for( int row = 0; row < rowCount; row++ )
    {
        for( int col = 0; col < colCount; col++ )
        {
            cout << board[row][col] << ", ";
        }
        cout << endl;
    }
}

#pragma mark - canWinNim
//You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.
//
//Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap.
//
//For example, if there are 4 stones in the heap, then you will never win the game: no matter 1, 2, or 3 stones you remove, the last stone will always be removed by your friend.
//
//Hint:
//
//If there are 5 stones in the heap, could you figure out a way to remove the stones such that you will always be the winner?
bool canWinNim(int n) {
    return n % 4 != 0;
}

#pragma mark - getHint
//You are playing the following Bulls and Cows game with your friend: You write down a number and ask your friend to guess what the number is. Each time your friend makes a guess, you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") and how many digits match the secret number but locate in the wrong position (called "cows"). Your friend will use successive guesses and hints to eventually derive the secret number.
//
//For example:
//
//Secret number:  "1807"
//Friend's guess: "7810"
//Hint: 1 bull and 3 cows. (The bull is 8, the cows are 0, 1 and 7.)
//Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows. In the above example, your function should return "1A3B".
//
//Please note that both secret number and friend's guess may contain duplicate digits, for example:
//
//Secret number:  "1123"
//Friend's guess: "0111"
//In this case, the 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow, and your function should return "1A1B".
//You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.
string getHint(string secret, string guess)
{
    vector<int> table( 10, 0 );
    for( const auto& c : secret )
        table[c-'0']++;
    
    int bulls = 0;
    int cows = 0;
    for( size_t i = 0; i < guess.size(); i++ )
    {
        int toIndex = guess[i]-'0';
        if( guess[i] == secret[i] )
        {
            bulls++;
            table[toIndex]--;
        }
    }

    for( size_t i = 0; i < guess.size(); i++ )
    {
        int toIndex = guess[i]-'0';
        if( guess[i] != secret[i] )
        {
            if( table[toIndex] > 0 )
            {
                cows++;
                table[toIndex]--;
            }
        }
    }
    
    return to_string(bulls) + "A" + to_string(cows) + "B";
}

void testGetHint()
{
    vector<pair<string, string>> tests = {
        {"1807","7810"},
        {"1123","0111"},
        {"1122","1222"},//"3A0B"
    };
    for( auto& p : tests )
    {
        cout << getHint(p.first, p.second) << endl;
    }
}

#pragma mark - lengthOfLIS
//Given an unsorted array of integers, find the length of longest increasing subsequence.
//
//For example,
//Given [10, 9, 2, 5, 3, 7, 101, 18],
//The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.
//
//Your algorithm should run in O(n2) complexity.
//
//Follow up: Could you improve it to O(n log n) time complexity?
int lengthOfLIS(vector<int>& nums) {
    if( nums.size() == 0 )  return 0;

    vector<int> dp(nums.size(), 0);
    dp[0] = 1;
    int m = 1;
    for( size_t i = 0; i < nums.size(); i++ )
    {
        int v = 1;
        for( size_t j = 0; j < i; j++ )
        {
            if( nums[j] < nums[i] )
                v = max( dp[j] + 1, v);
        }
        dp[i] = v;
        m = max(m, dp[i]);
    }
    return m;
}

void testLenghtOfLIS()
{
    vector<pair<vector<int>, int>> tests = {
        {{1,3,6,7,9,4,10,5,6}, 6},
        {{10, 9, 2, 5, 3, 7, 101, 18}, 4},
    };
    for( auto& p : tests )
        cout << BoolToStr( lengthOfLIS( p.first ) == p.second ) << endl;
}

#pragma mark - NumArray
//Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
//
//Example:
//Given nums = [-2, 0, 3, -5, 2, -1]
//
//sumRange(0, 2) -> 1
//sumRange(2, 5) -> -1
//sumRange(0, 5) -> -3
//Note:
//You may assume that the array does not change.
//There are many calls to sumRange function.
class NumArray {
    vector<int> m_nums;
    int m_rS { -1 };
    int m_rE { -1 };
    int m_total{ 0 };
    
public:
    NumArray(vector<int> nums)
        :m_nums( std::move( nums ) )
    {
    }
    
    int sumRange(int i, int j)
    {
        if( i > j || i < 0 || j >= m_nums.size() )
            return 0;
        
        if( j < m_rS || i > m_rE )
        {
            m_total = 0;
            for( int k = i; k <= j; k++ )
                m_total += m_nums[k];
        }
        else
        {
            if( i < m_rS )
            {
                for( int k = i; k < m_rS; k++ )
                    m_total += m_nums[k];
            }
            else
            {
                for( int k = m_rS; k < i; k++ )
                    m_total -= m_nums[k];
            }
            
            if( j < m_rE )
            {
                for( int k = j + 1; k <= m_rE; k++ )
                    m_total -= m_nums[k];
            }
            else
            {
                for( int k = m_rE + 1; k <= j; k++ )
                    m_total += m_nums[k];
            }
        }
        
        m_rS = i;
        m_rE = j;
        return m_total;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
void testNumArray()
{
    vector<int> t = {-2, 0, 3, -5, 2, -1};
    NumArray obj( t );
    //sumRange(0, 2) -> 1
    //sumRange(2, 5) -> -1
    //sumRange(0, 5) -> -3
    cout << BoolToStr( obj.sumRange(0, 2) == 1 ) << endl;
    cout << BoolToStr( obj.sumRange(2, 5) == -1 ) << endl;
    cout << BoolToStr( obj.sumRange(0, 5) == -3 ) << endl;
}

#pragma mark - run

void Level21::Run()
{
    testNumArray();
}

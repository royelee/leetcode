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

#pragma mark - run

void Level21::Run()
{
    testWordPattern();
}

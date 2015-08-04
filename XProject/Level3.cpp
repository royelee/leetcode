//
//  Level3.cpp
//  XProject
//
//  Created by Roye Li on 7/30/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Level3.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode* head = new ListNode(0);
    ListNode* headIter = head;
    ListNode* it1 = l1;
    ListNode* it2 = l2;
    
    while( it1 != nullptr || it2 != nullptr )
    {
        if( it1 != nullptr && it2 != nullptr )
        {
            if( it1->val < it2->val )
            {
                headIter->next = it1;
                it1 = it1->next;
            }
            else
            {
                headIter->next = it2;
                it2 = it2->next;
            }
            
            headIter = headIter->next;
        }
        else if( it1 != nullptr )
        {
            headIter->next = it1;
            break;
        }
        else if( it2 != nullptr )
        {
            headIter->next = it2;
            break;
        }
    }
    
    return head->next;
}

#pragma mark - generateParenthesis

vector< pair<string, int>> _generateParenthesis( int n, vector< pair<string, int>> v )
{
    // if leftBracket == 0
    //      can only add ), check the bracketInstack, add all.
    // else
    //      two ways,
    //      1) Add left bracket to already generated, bracketInstack++, left bracket--
    //          _generateParenthesis( left - 1, bracketInstack + 1, new alreadyGenerated )
    //      2) 2a. complete one bracket if possible.
    //          _generateParenthesis( left, bracketInstack - 1, new alreadyGenerated )
    //         2b. if not possible
    
    // vector< pair<string, bracketInStack > >
    // two ways,
    // 1. if n > 0, add left bracket to string, bracketInstack++
    //      _generateParenthesis( n - 1, v )
    // 2. consume the bracketInstack, add right bracket to string, bracketInstack--
    //      _generateParenthesis( n, v )
    //
    // return if bracketInsString is 0 and n is 0
    //
    // Combine the 1 & 2.
    if( n == 0 )
    {
        bool allDone =  true;
        for( auto& p : v )
        {
            if( p.second != 0 )
            {
                allDone = false;
            }
        }
        
        if( allDone )
            return v;
    }
    
    vector< pair<string, int > > v1 = v;
    vector< pair<string, int > > v2 = v;
    
    if( n > 0 )
    {
        for( auto& p : v1 )
        {
            p.first += "(";
            p.second++;
        }
        
        v1 = _generateParenthesis( n - 1, v1 );
    }
 
    {
        bool fixed = false;
        for( auto& p : v2 )
        {
            if( p.second > 0 )
            {
                p.first += ")";
                p.second--;
                fixed = true;
            }
        }
        
        if( fixed )
            v2 = _generateParenthesis( n, v2 );
    }
    
    vector< pair<string, int > > rtn;
    rtn.insert( rtn.begin(), v1.begin(), v1.end() );
    rtn.insert( rtn.begin(), v2.begin(), v2.end() );
    
    return rtn;
}

vector<string> generateParenthesis(int n)
{
    vector<string> g;
    
    vector< pair<string, int > > v;
    v.push_back( make_pair("", 0) );
     vector< pair<string, int > > rtn = _generateParenthesis( n, v);
    
    for( auto p : rtn )
    {
        g.push_back( p.first );
    }
    
    return g;
}

void testGenerateParenthesis()
{
    vector<string> v = generateParenthesis(2);
    for( auto& s : v )
    {
        cout << s << ", ";
    }
}

#pragma mark - run
void Level3::Run()
{
    testGenerateParenthesis();
}
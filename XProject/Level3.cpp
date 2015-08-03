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

vector<string> generateParenthesis(int n)
{
    vector<string> g;
    
    if( n <= 0 )
    {
    }
    else if( n == 1 )
    {
        g.push_back("()");
    }
    else
    {
        set<string> newG;
        vector<string> gLast = generateParenthesis( n - 1 );
        for( string p : gLast )
        {
            string a = "(" + p + ")";
            string b = "()" + p;
            string c = p + "()";
            
            newG.insert(a);
            newG.insert(b);
            newG.insert(c);
        }
        
        for( auto& t : newG )
        {
            g.push_back(t);
        }
    }
    
    return g;
}

void testGenerateParenthesis()
{
    vector<string> v = generateParenthesis(4);
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
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

struct ParenthesisStruct
{
public:
    string current; // Current string
    int left;   // Left (
    int used;   // Used (
    
    ParenthesisStruct( string c, int l, int u ) : current( c ), left( l ), used( u ) {}
};


vector<string> generateParenthesis(int n)
{
    vector<string> g;
    
    vector<ParenthesisStruct> stack;
    
    stack.push_back({"", n, 0 });
    
    while( stack.size() != 0 )
    {
        ParenthesisStruct p = stack.back();
        stack.pop_back();
        
        if( p.left > 0 )
        {
            stack.push_back( ParenthesisStruct( p.current + "(", p.left - 1, p.used + 1 ) );
        }

        if( p.used > 0 )
        {
            // we have something to complete
            p.current += ")";
            p.used--;
            
            if( p.left == 0 && p.used == 0 )
            {
                g.push_back( p.current );
            }
            else
            {
                stack.push_back( p );
            }
        }
    }
    
    return g;
}

void testGenerateParenthesis()
{
    vector<string> v = generateParenthesis(0);
    for( auto& s : v )
    {
        cout << s << ", ";
    }
}

#pragma mark - swapPairs

ListNode* swapPairs(ListNode* head)
{
    if( head == nullptr )
        return head;
    
    
    ListNode* c1 = head;
    ListNode* c2 = head->next;
    ListNode* previous = nullptr;

    ListNode* newHead = head->next == nullptr ? c1 : c2;
    
    while( c1 != nullptr && c2 != nullptr )
    {
        if( previous != nullptr )
            previous->next = c2;
        
        ListNode* tmp = c2->next;
        c2->next = c1;
        
        previous = c1;
        
        c1 = tmp;
        if( c1 != nullptr )
            c2 = c1->next;
        
    }
    
    if( previous != nullptr )
    {
        previous->next = c1;
    }
    
    return newHead;
}

void testSwapPairs()
{
    vector<int> v = { 1 };
    ListNode* head = new ListNode( 0 );
    ListNode* iter = head;
    for( auto i : v )
    {
        ListNode* listNode = new ListNode( i );
        iter->next = listNode;
        iter = iter->next;
    }
    
    iter = head->next;
    while( iter != nullptr )
    {
        cout << iter->val << endl;
        iter = iter->next;
    }
    
    cout << "new ===== " << endl;
    ListNode* newHead = swapPairs( head->next );
    while( newHead != nullptr )
    {
        cout << newHead->val << endl;
        newHead = newHead->next;
    }
}

#pragma mark - run
void Level3::Run()
{
    testSwapPairs();
}
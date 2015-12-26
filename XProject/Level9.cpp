//
//  Level9.cpp
//  XProject
//
//  Created by Roye Li on 12/22/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

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

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//Reverse a linked list from position m to n. Do it in-place and in one-pass.
//
//For example:
//Given 1->2->3->4->5->NULL, m = 2 and n = 4,
//
//return 1->4->3->2->5->NULL.
//
//Note:
//Given m, n satisfy the following condition:
//1 ≤ m ≤ n ≤ length of list.
ListNode* reverseBetween(ListNode* head, int m, int n)
{
    ListNode* newHead = new ListNode(-1);
    newHead->next = head;
    if( m >= 1 && m <= n )
    {
        ListNode* iterM = nullptr;
        ListNode* iter = head;
        ListNode* beforeM = newHead;
        int i = 1;
        while( i < m )
        {
            beforeM = iter;
            iter = iter->next;
            i++;
        }
        iterM = iter;
        
        ListNode* next = iter->next;
        while( i < n )
        {
            ListNode* cur = iter;
            iter = next;
            next = next->next;
            iter->next = cur;
            i++;
        }
        
        beforeM->next = iter;
        iterM->next = next;
    }
    
    return newHead->next;
}

void tesetReverseBetween()
{
    vector<int> v = { 1, 2, 3, 4, 5 };
    ListNode* head = new ListNode(-1);
    ListNode* it = head;
    for( int i = 0; i < v.size(); i++ )
    {
        it->next = new ListNode(v[i]);
        it = it->next;
    }
    
    cout << "before" << endl;
    it = head->next;
    while( it )
    {
        cout << it->val << " ";
        it = it->next;
    }
    cout << endl;
    
    it = reverseBetween( head->next, 2, 5 );
    
    cout << "after" << endl;
    while( it )
    {
        cout << it->val << " ";
        it = it->next;
    }
    cout << endl;
}


#pragma mark - restoreIpAddresses
//Given a string containing only digits, restore it by returning all possible valid IP address combinations.
//
//For example:
//Given "25525511135",
//
//return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
void _restoreIpAddresses( string s, vector<int> stored, int currentSlotIndex, vector<string>& out )
{
    if( currentSlotIndex >= 4 )
        return;

    for( int i = 1; i <= 3; i++ )
    {
        string newS = s;
        if( newS.size() >= i )
        {
            string sub = newS.substr(0, i);
            int newValue = stoi( sub );
            if( newValue <= 255 )
            {
                // Try to fill it
                stored[currentSlotIndex] = newValue;
                newS.erase(0, i);
                
                if( newS.size() == 0 )
                {
                    if( currentSlotIndex == 3 )
                    {
                        // Done
                        stringstream ss;
                        for( int i = 0; i < stored.size() - 1; i++ )
                        {
                            ss << to_string(stored[i]) << ".";
                        }
                        
                        ss << to_string(stored.back() );
                        
                        out.push_back(ss.str());
                    }
                    
                    return;
                }
                
                _restoreIpAddresses(newS, stored, currentSlotIndex + 1, out);
            }
        }
    }
}

vector<string> restoreIpAddresses(string s)
{
    vector<string> output;
    if( s.size() < 4 )
        return output;
    
    vector<int> store( 4 );
    _restoreIpAddresses( s, store, 0, output );
    return output;
}

void testRestoreIpAddresses()
{
    vector<string> out = restoreIpAddresses("010010");    //25525511135
    for( auto s : out )
        cout << s << endl;
}

#pragma mark - run

void Level9::Run()
{
    testRestoreIpAddresses();
}
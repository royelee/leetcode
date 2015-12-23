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


#pragma mark - run

void Level9::Run()
{
    tesetReverseBetween();
}
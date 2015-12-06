//
//  Level8.cpp
//  XProject
//
//  Created by Roye Li on 12/4/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Level8.h"

#include "Level7.h"
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

#pragma mark - deleteDuplicates
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//Given a sorted linked list, delete all duplicates such that each element appear only once.
//
//For example,
//Given 1->1->2, return 1->2.
//Given 1->1->2->3->3, return 1->2->3.
ListNode* deleteDuplicates(ListNode* head)
{
    ListNode* iter = head;
    while( iter )
    {
        ListNode* next = iter->next;
        while( next && iter->val == next->val )
        {
            iter->next = next->next;
            next = next->next;
        }
        
        iter = iter->next;
    }

    return head;
}

void testDeleteDuplicates()
{
    vector<int> v = {1, 1, 1};
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
        cout << it->val << endl;
        it = it->next;
    }
    
    it = deleteDuplicates( head->next );
    
    cout << "after" << endl;
    while( it )
    {
        cout << it->val << endl;
        it = it->next;
    }
}

//Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
//
//For example,
//Given 1->2->3->3->4->4->5, return 1->2->5.
//Given 1->1->1->2->3, return 2->3.
ListNode* deleteDuplicates2(ListNode* head)
{
    ListNode* cur = head;
    while( cur != nullptr )
    {
        ListNode* next = cur->next;
        while( next && next->val == cur->val )
        {
            next = next->next;
        }
        
        cur->next = next;
    }
    
    return nullptr;
}

#pragma mark - run

void Level8::Run()
{
    testDeleteDuplicates();
}
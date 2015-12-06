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

//Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
//
//For example,
//Given 1->2->3->3->4->4->5, return 1->2->5.
//Given 1->1->1->2->3, return 2->3.
ListNode* deleteDuplicates2(ListNode* head)
{
    ListNode* cur = head;
    ListNode* pre = new ListNode(-1);
    pre->next = head;
    ListNode* newHead = pre;
    while( cur != nullptr )
    {
        ListNode* next = cur->next;
        while( next && next->val == cur->val )
        {
            next = next->next;
        }
        
        if( next != cur->next )
        {
            // Found the duplicates, then we need to remove all the nodes duplicated.
            pre->next = next;
        }
        else
        {
            pre = cur;
        }

        cur = next;
    }
    
    return newHead->next;
}

void testDeleteDuplicates()
{
    vector<vector<int>> tests = {
        {},
        {1},
        {1,1},
        {1,1,1},
        {1,2,2,2},
        {1,2,2,2,3}
    };
    
    for( vector<int> v : tests )
    {
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
        
        it = deleteDuplicates2( head->next );
        
        cout << "after" << endl;
        while( it )
        {
            cout << it->val << " ";
            it = it->next;
        }
        cout << endl;
    }
}

#pragma mark - run

void Level8::Run()
{
    testDeleteDuplicates();
}
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

#pragma mark merge

//Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
//
//Note:
//You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;
    while( k >= 0 )
    {
        if( i >= 0 && j >= 0 )
        {
            if( nums1[i] < nums2[j] )
            {
                nums1[k] = nums2[j];
                j--;
            }
            else
            {
                nums1[k] = nums1[i];
                i--;
            }
        }
        else if( i < 0 )
        {
            nums1[k] = nums2[j];
            j--;
        }
        else
        {
            nums1[k] = nums1[i];
            i--;
        }

        k--;
    }
}

#pragma mark - partition
//Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
//
//You should preserve the original relative order of the nodes in each of the two partitions.
//
//For example,
//Given 1->4->3->2->5->2 and x = 3,
//return 1->2->2->4->3->5.
ListNode* partition(ListNode* head, int x)
{
    ListNode* bigHead = nullptr;
    ListNode* bigHeadIter = nullptr;
    ListNode* iter = head;
    ListNode* pre = nullptr;
    ListNode* newHead = nullptr;
    while( iter != nullptr )
    {
        ListNode* next = iter->next;

        if( iter->val >= x )
        {
            // Move to big head
            if( bigHead == nullptr )
            {
                bigHead = iter;
                bigHeadIter = bigHead;
            }
            else
            {
                bigHeadIter->next = iter;
                bigHeadIter = bigHeadIter->next;
            }
            
            if( pre )
                pre->next = iter->next;
            
            bigHeadIter->next = nullptr;
        }
        else
        {
            if( !pre )
                newHead = iter;
            pre = iter;
        }
        
        iter = next;
    }
    
    if( pre )
        pre->next = bigHead;

    return newHead ? newHead : bigHead;
}

void testPartition()
{
    vector<pair<vector<int>, int>> tests = {
        {{1,4,3,2,5,2}, 3},
        {{}, 0},
        {{1},1},
        {{1},2},
        {{1},0},
        {{1,1,1},1},
        {{2,2,1},2},
        {{2,2,2,2,1},1},
    };
    
    for( auto& t : tests )
    {
        vector<int>& v = t.first;
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
        
        it = partition( head->next, t.second );
        
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
    testPartition();
}
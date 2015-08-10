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

//Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
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

//Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
//
//For example, given n = 3, a solution set is:
//
//"((()))", "(()())", "(())()", "()(())", "()()()"
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

//Given a linked list, swap every two adjacent nodes and return its head.
//
//For example,
//Given 1->2->3->4, you should return the list as 2->1->4->3.
//
//Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
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

#pragma mark - removeDuplicates

//Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
//
//Do not allocate extra space for another array, you must do this in place with constant memory.
//
//For example,
//Given input array nums = [1,1,2],
//
//Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.
int removeDuplicates(vector<int>& nums)
{
    // Using the way O(N) implements it. http://blog.csdn.net/fightforyourdream/article/details/12719683
    
    // The idea is use i always point to unqiue index in the array, and let j to move from (1..n) in array V[N].
    // If V[i] == V[j] then, i don't move and j continue move, if not equal then i+1 is the duplicate one or maybe is V[j], so V[i+1] = V[j].
    // When it's end, then the index of i is last elements, the array size is i + 1.
    int i = 0;
    int j = 1;
    while( j < nums.size() )
    {
        if( nums[i] != nums[j] )
        {
            i++;
            nums[i] = nums[j];
        }

        j++;
    }
    
    return nums.size() - ( j - i ) + 1; // which is i + 1
}

void testRemoveDuplicates()
{
    vector<int> v = {1,2,3,};
    int r = removeDuplicates(v);
    for( int i = 0; i < r; i++ )
    {
        cout << v[i] << ", ";
    }
    cout << endl;
}

#pragma mark - removeElement
//Given an array and a value, remove all instances of that value in place and return the new length.
//
//The order of elements can be changed. It doesn't matter what you leave beyond the new length.
int removeElement(vector<int>& nums, int val)
{
    // similar to quick sort
    if( nums.size() == 0 )
        return 0;
    
    int i = 0;
    int j = nums.size() - 1;
    
    while( nums[j] == val && j >= 0 )
    {
        j--;
    }
    
    while( i <= j )
    {
        
        if( nums[i] != val )
        {
            i++;
        }
        else
        {
            swap( nums[i], nums[j] );
            j--;
            i++;
            
            while( nums[j] == val && j >= 0 )
            {
                j--;
            }
        }
    }
    
    return j + 1;
}

#pragma mark - run
void Level3::Run()
{
    testRemoveDuplicates();
}
//
//  Level12.cpp
//  XProject
//
//  Created by Roye Li on 3/30/16.
//  Copyright (c) 2016 Roye Li. All rights reserved.
//
#include <stdio.h>

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
#include <stack>
#include <unordered_set>
#include <queue>
#include <fstream>

using namespace std;

#pragma mark - cloneGraph
//Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.
//
//
//OJ's undirected graph serialization:
//Nodes are labeled uniquely.
//
//We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
//As an example, consider the serialized graph {0,1,2#1,2#2,2}.
//
//The graph has a total of three nodes, and therefore contains three parts as separated by #.
//
//First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
//Second node is labeled as 1. Connect node 1 to node 2.
//Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
//Visually, the graph looks like the following:
//
//       1
//      / \
//     /   \
//    0 --- 2
//         / \
//         \_/
UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
{
    if( node == nullptr )
        return nullptr;

    map< UndirectedGraphNode*, UndirectedGraphNode* > oldToNewMap;
    set< UndirectedGraphNode* > visitedNode;
    queue< UndirectedGraphNode* > queue;
    UndirectedGraphNode* newHead = new UndirectedGraphNode( node->label );
    oldToNewMap[node] = newHead;
    queue.push( node );
    while( !queue.empty() )
    {
        UndirectedGraphNode* current = queue.front();
        queue.pop();
        
        UndirectedGraphNode* newNode = oldToNewMap[current];
        
        for( UndirectedGraphNode* neighbor : current->neighbors )
        {
            if( oldToNewMap.find( neighbor ) != oldToNewMap.end() )
            {
                newNode->neighbors.push_back(oldToNewMap[ neighbor ]);
            }
            else
            {
                UndirectedGraphNode* newNeighbor = new UndirectedGraphNode( neighbor->label );
                newNode->neighbors.push_back(newNeighbor);
                oldToNewMap[neighbor] = newNeighbor;
                queue.push(neighbor);
            }

        }
    }
    
    return oldToNewMap[node];
}

void testCloneGraph()
{
    UndirectedGraphNode* node0 = new UndirectedGraphNode( 0 );
    UndirectedGraphNode* node1 = new UndirectedGraphNode( 1 );
    UndirectedGraphNode* node2 = new UndirectedGraphNode( 2 );
    node0->neighbors.push_back(node1);
    node1->neighbors.push_back(node2);
    node2->neighbors.push_back(node2);

    UndirectedGraphNode* newNode0 = cloneGraph( node0 );
    cout << newNode0->label << endl;
}

#pragma mark - canCompleteCircuit
//There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
//
//You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.
//
//Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.
//
//Note:
//The solution is guaranteed to be unique.
int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
{
    vector<int> relativeCost( gas.size() );
    int total = 0;
    size_t minIndex = 0;
    int minValue = numeric_limits<int>::max();
    for( size_t i = 0; i < gas.size(); i++ )
    {
        relativeCost[i] = gas[i] - cost[i];
        total += relativeCost[i];
        if( total < minValue )
        {
            minIndex = i;
            minValue = total;
        }
    }

    if( total < 0 )
        return -1;
    else
        return (int)( 1 + minIndex ) % relativeCost.size(); // +1 because at minIndex it still go down( cost is negtive ), we need to start from positive
}

#pragma mark - singleNumber
//Given an array of integers, every element appears twice except for one. Find that single one.
//

//Note:
//Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
int singleNumber(vector<int>& nums)
{
    int num = 0;
    for( size_t i = 0; i < nums.size(); i++ )
    {
        num ^= nums[i];
    }
    return num;
}

void testSingleNumber()
{
    vector<int> v = { 1, 2, 1 };
    cout << singleNumber(v) << endl;
}

#pragma mark - singleNumber2
//Given an array of integers, every element appears three times except for one. Find that single one.
//
//Note:
//Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
int singleNumber2(vector<int>& nums)
{
    int r = 0;
    for( size_t i = 0; i < sizeof( int ) * 8; i++ )
    {
        int bitMask = 1 << i;
        int count = 0;
        for( auto num : nums )
        {
            if( ( num & bitMask ) != 0 )
                count++;
        }
        if( count % 3 == 1 )
            r |= bitMask;
    }
    
    return r;
}

void testSingleNumber2()
{
//    vector<int> v = {3};
//    cout << singleNumber2(v) << endl;
//    
//    v = {3,3,3,4};
//    cout << singleNumber2(v) << endl;
    
    vector<int> v = {43,16,45,89,45,-2147483648,45,2147483646,-2147483647,-2147483648,43,2147483647,-2147483646,-2147483648,89,-2147483646,89,-2147483646,-2147483647,2147483646,-2147483647,16,16,2147483646,43};
    cout << singleNumber2(v) << endl;
}

#pragma mark - wordBreak
//Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
//
//For example, given
//s = "leetcode",
//dict = ["leet", "code"].
//
//Return true because "leetcode" can be segmented as "leet code".
bool wordBreak(string s, unordered_set<string>& wordDict)
{
    vector<bool> dp( s.size() + 1);
    dp[0] = true;
    for( size_t i = 0; i < s.size(); i++ )
    {
        for( int j = i; j >= 0; j-- )
        {
            string substring = s.substr(j, i - j + 1);
            if( dp[j] && wordDict.find(substring) != wordDict.end() )
            {
                dp[i + 1] = true;
                break;
            }
        }
    }
    return dp.back();
}

void testWordBreak()
{
    string s = "leetcode";
    unordered_set<string> dic = {"leet", "code"};
    cout << wordBreak(s, dic) << endl;
    
    s = "aaaab";
    dic = {"a", "aab"};
    cout << wordBreak(s, dic) << endl;
}

//Given a linked list, determine if it has a cycle in it.
//
//Follow up:
//Can you solve it without using extra space?
bool hasCycle(ListNode *head)
{
    ListNode* oneStepIter = head;
    ListNode* twoStepIter = head;
    while( twoStepIter != nullptr )
    {
        oneStepIter = oneStepIter->next;
        twoStepIter = twoStepIter->next;
        if( twoStepIter == nullptr )
            return false;
        
        twoStepIter = twoStepIter->next;
        if( oneStepIter == twoStepIter )
            return true;
    }
    
    return false;
}

#pragma mark - detectCycle
//Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
//
//Note: Do not modify the linked list.
//
//Follow up:
//Can you solve it without using extra space?
ListNode *detectCycle(ListNode *head)
{
    if( head == nullptr )
        return nullptr;

    //    Fast = 2 * slow
    //    Slow = X + Y ( X - node went before into the circle, Y node went in circle )
    //    Fast = X + circleNum + Y ( circleNum - node went loop inside of circle )
    //    2X + 2Y = X + circleNum + Y
    //    => X+Y = circle Num = slow
    //    => X = slow – Y = circleNum - Y
    
    ListNode* oneStepIter = head;
    ListNode* twoStepIter = head;
    while( twoStepIter != nullptr )
    {
        oneStepIter = oneStepIter->next;
        twoStepIter = twoStepIter->next;
        if( twoStepIter == nullptr )
            return nullptr;
        
        twoStepIter = twoStepIter->next;
        if( oneStepIter == twoStepIter )
            break;
    }
    
    if( twoStepIter == nullptr )
        return twoStepIter;
    
    oneStepIter = head;
    while( oneStepIter != twoStepIter )
    {
        oneStepIter = oneStepIter->next;
        twoStepIter = twoStepIter->next;
    }
    
    return oneStepIter;
}

void testDetectCycle()
{
    ListNode* node = new ListNode( 1 );
    detectCycle(node);
}

#pragma mark - reorderList
//Given a singly linked list L: L0→L1→…→Ln-1→Ln,
//reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
//
//You must do this in-place without altering the nodes' values.
//
//For example,
//Given {1,2,3,4}, reorder it to {1,4,2,3}.
void reorderList(ListNode* head)
{
    if( head == nullptr )
        return;

    size_t count = 0;
    ListNode* it = head;
    while( it )
    {
        count++;
        it = it->next;
    }
    
    it = head;
    ListNode* tail = nullptr;
    for( size_t i = 0; i < count; i++ )
    {
        ListNode* current = it;
        it = it->next;
        
        if( i >= count / 2 )
        {
            current->next = tail;
            tail = current;
        }
    }
    
    ListNode* headIt = head;
    ListNode* tailIt = tail;
    while(tailIt && tailIt->next) {
        ListNode *target = tailIt;
        tailIt = tailIt->next;
        target->next = headIt->next;
        headIt->next = target;
        headIt = headIt->next->next;
    }
}

void testReorderList()
{
    ListNode* node = new ListNode(1);
    reorderList(node);
    
    node = new ListNode(1);
    node->next = new ListNode(2);
    reorderList(node);
    
    node = new ListNode(1);
    node->next = new ListNode(2);
    node->next->next = new ListNode(3);
    reorderList(node);
    
    cout << node;
}

#pragma mark - preorderTraversal
//Given a binary tree, return the preorder traversal of its nodes' values.
//
//For example:
//Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
//return [1,2,3].
//
//Note: Recursive solution is trivial, could you do it iteratively?
vector<int> preorderTraversal(TreeNode* root)
{
    vector<int> output;
    if( root == nullptr )
        return output;
    
    stack<TreeNode*> s;
    s.push(root);
    while( s.size() != 0 )
    {
        TreeNode* top = s.top();
        s.pop();
        output.push_back(top->val);
        if( top->right )
            s.push(top->right);
        if( top->left )
            s.push(top->left);
    }
    
    return output;
}

void testPreorderTraversal()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(4);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(2);
    vector<int> v = preorderTraversal(root);
    for( const auto i : v )
        cout << i << ", ";
}

#pragma mark - run

void Level13::Run()
{
    testPreorderTraversal();
}
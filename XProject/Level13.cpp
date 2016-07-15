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

#pragma mark - run

void Level13::Run()
{
    testSingleNumber2();
}
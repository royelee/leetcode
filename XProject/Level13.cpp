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
    queue.push( node );
    while( !queue.empty() )
    {
        UndirectedGraphNode* current = queue.front();
        queue.pop();
        
        if( visitedNode.find( current ) != visitedNode.end() )
            continue;
        
        UndirectedGraphNode* newNode = nullptr;
        if( oldToNewMap.find( current ) != oldToNewMap.end() )
            newNode = oldToNewMap[current];
        else
            newNode = new UndirectedGraphNode( current->label );
        
        oldToNewMap[current] = newNode;
        
        for( UndirectedGraphNode* neighbor : current->neighbors )
        {
            UndirectedGraphNode* newNeighbor = nullptr;
            if( oldToNewMap.find( neighbor ) != oldToNewMap.end() )
            {
                newNeighbor = oldToNewMap[ neighbor ];
            }
            else
            {
                newNeighbor = new UndirectedGraphNode( neighbor->label );
                oldToNewMap[neighbor] = newNeighbor;
            }

            newNode->neighbors.push_back(newNeighbor);
            queue.push(neighbor);
        }
        
        visitedNode.insert(current);
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

#pragma mark - run

void Level13::Run()
{
    testCloneGraph();
}
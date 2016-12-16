//
//  Level20.cpp
//  XProject
//
//  Copyright © 2016 Roye Li. All rights reserved.
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
#include <unordered_map>

using namespace std;


#pragma mark - lowestCommonAncestor

//Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
//
//According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”
//
//        _______3______
//       /              \
//    ___5__          ___1__
//   /      \        /      \
//   6      _2       0       8
//         /  \
//         7   4
//For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
static TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
   if( root == nullptr || root == p || root == q ) return root;
   TreeNode* left = lowestCommonAncestor(root->left, p, q);
   TreeNode* right = lowestCommonAncestor(root->right, p, q);
   return left ? ( right ? root : left ) : right;
}

static void testLowestCommonAncestor()
{
   TreeNode* root = new TreeNode(6);
   root->left = new TreeNode(2);
   root->right = new TreeNode(8);
   root->left->left = new TreeNode(0);
   root->left->right = new TreeNode(4);
   root->left->right->left = new TreeNode(3);
   root->left->right->right = new TreeNode(5);
   root->right->left = new TreeNode(7);
   root->right->right = new TreeNode(9);

   cout << ( lowestCommonAncestor(root, root->left, root->right)->val == 6 ) << endl;
   cout << ( lowestCommonAncestor(root, root->left->right, root->left)->val == 2 ) << endl;
   cout << ( lowestCommonAncestor(root, root->left, root->left->right)->val == 2 ) << endl;
}

#pragma mark - deleteNode
//Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
//
//Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.
void deleteNode(ListNode* node)
{
    if( node == nullptr )
        return;
    
    ListNode* next = node->next;
    node->val = next->val;
    node->next = next->next;
}


#pragma mark - run

void Level20::Run()
{
   testLowestCommonAncestor();
}

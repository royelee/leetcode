//
//  Level.h
//  XProject
//
//  Created by Roye Li on 12/22/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#ifndef __XProject__Level__
#define __XProject__Level__
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

struct UndirectedGraphNode {
    int label;
    std::vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};


#define DECLARE_LEVEL(LEVELNAME) class Level##LEVELNAME\
{\
public:\
    void Run();\
};

void preOrderTrasveral( TreeNode* node );

DECLARE_LEVEL(1);
DECLARE_LEVEL(2);
DECLARE_LEVEL(3);
DECLARE_LEVEL(4);
DECLARE_LEVEL(5);
DECLARE_LEVEL(6);
DECLARE_LEVEL(7);
DECLARE_LEVEL(8);
DECLARE_LEVEL(9);
DECLARE_LEVEL(10);
DECLARE_LEVEL(11);
DECLARE_LEVEL(12);
DECLARE_LEVEL(13);
DECLARE_LEVEL(14);
DECLARE_LEVEL(15);

#endif /* defined(__XProject__Level__) */

//
//  Level.h
//  XProject
//
//  Created by Roye Li on 12/22/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#ifndef __XProject__Level__
#define __XProject__Level__

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


class ILevel
{
public:
    virtual void Run() = 0;
};

#define DECLARE_LEVEL(LEVELNAME) class Level##LEVELNAME : public ILevel\
{\
public:\
    void Run() override;\
}

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

#endif /* defined(__XProject__Level__) */

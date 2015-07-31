//
//  Level1.h
//  XProject
//
//  Created by Roye Li on 6/17/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#ifndef __XProject__Level1__
#define __XProject__Level1__

#include <stdio.h>
#include <vector>
#include "ILevel.h"

class Level1 : public ILevel
{
public:
    std::vector<int> twoSum_binarysearch(std::vector<int>& nums, int target);

    std::vector<int> twoSum(std::vector<int>& nums, int target);
    
    void Run() override;
    
private:
    void runTwoSum();
};

#endif /* defined(__XProject__Level1__) */

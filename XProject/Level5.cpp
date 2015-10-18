//
//  Level5.cpp
//  XProject
//
//  Created by Roye Li on 10/16/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Level5.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <set>
#include <cmath>

using namespace std;


#pragma mark - maxSubArray
//
//Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
//
//For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
//the contiguous subarray [4,−1,2,1] has the largest sum = 6.
int maxSubArray(vector<int>& nums)
{
    size_t size = nums.size();
    if( size == 1 )
        return nums[0];
    
    vector<int> dp( size );
    dp[size - 1] = nums[size - 1];
    
    int maxR = dp[size - 1];
    for( int i = size - 2; i >= 0; i-- )
    {
        dp[i] = max( nums[i] + dp[i + 1], nums[i] );
        maxR = max( dp[i], maxR );
    }
    
    return maxR;
}

void testMaxSubArray()
{
    vector<int> t {-2,1,-3,4,-1,2,1,-5,4};
    cout << maxSubArray(t) << endl;
}

#pragma mark - run

void Level5::Run()
{
    testMaxSubArray();
}
//
//  Level16.cpp
//  XProject
//
//  Created by Roye Li on 10/17/16.
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

using namespace std;

#pragma mark - hammingWeight
//Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).
//
//For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, so the function should return 3.
int hammingWeight(uint32_t n)
{
    int count = 0;
    while( n > 0 )
    {
        if( ( n & 1 ) == 1 )
            count++;
        
        n = n >> 1;
    }
    
    return count;
}

void testHammingWeight()
{
    uint32_t t = 0b1011;
    cout << hammingWeight(t);
}

#pragma mark - rob
//You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
//
//Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
int rob(vector<int>& nums)
{
    if( nums.size() == 0 )
        return 0;
    else if( nums.size() == 1 )
        return nums[0];

    vector<int> dp(nums.size());
    dp[0] = nums[0];
    dp[1] = max( dp[0], nums[1] );
    for( size_t i = 2; i < nums.size(); i++ )
    {
        dp[i] = max( dp[i-1], dp[i-2] + nums[i] );
    }
    
    return dp.back();
}

void testRob()
{
    vector<int> t = {183,219,57,193,94,233,202,154,65,240,97,234,100,249,186,66,90,238,168,128,177,235,50,81,185,165,217,207,88,80,112,78,135,62,228,247,211};
    cout << rob(t);
}


#pragma mark - run

void Level16::Run()
{
    testRob();
}

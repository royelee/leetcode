//
//  Level7.cpp
//  XProject
//
//  Created by Roye Li on 11/21/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Level7.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <set>
#include <cmath>

using namespace std;

//Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
//
//Integers in each row are sorted from left to right.
//The first integer of each row is greater than the last integer of the previous row.
//For example,
//
//Consider the following matrix:
//
//[
// [1,   3,  5,  7],
// [10, 11, 16, 20],
// [23, 30, 34, 50]
// ]
//Given target = 3, return true.
bool searchMatrix(vector<vector<int>>& matrix, int target)
{
    vector<int> thresholds(matrix.size() + 2);
    thresholds[0] = numeric_limits<int>::min();
    thresholds[thresholds.size() - 1] = numeric_limits<int>::max();
    for( int i = 0; i < matrix.size(); i++ )
        thresholds[i+1] = matrix[i][0];
    
    int t = -1;
    for( int i = 0; i < thresholds.size() - 1; i++ )
    {
        if( thresholds[i] <= target && thresholds[i+1] > target )
        {
            t = i;
            break;
        }
    }
    
    if( t > 0 )
        return binary_search(matrix[t-1].begin(), matrix[t-1].end(), target );
    else
        return false;
}

void testSearchMatrix()
{
//    vector<vector<int>> m =
//    {
//        {1,   3,  5,  7},
//        {10, 11, 16, 20},
//        {23, 30, 34, 50}
//    };
//    cout << searchMatrix(m, 10);
    
        vector<vector<int>> m =
        {
            {1,   3}
        };
        cout << searchMatrix(m, 0);

}

#pragma mark - sortColors

//Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
//
//Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
//
//Note:
//You are not suppose to use the library's sort function for this problem.
//
//click to show follow up.
//
//Follow up:
//A rather straight forward solution is a two-pass algorithm using counting sort.
//First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
//
//Could you come up with an one-pass algorithm using only constant space?
void sortColors(vector<int>& nums) {
    if( nums.size() <= 1 )
        return ;
    
    int fill0 = 0;
    int fill2 = nums.size() - 1;
    
    for( int i = fill0; i <= fill2; )
    {
        if( nums[i] == 0 )
        {
            swap(nums[fill0], nums[i]);
            fill0++;
            i++;
        }
        else if( nums[i] == 2 )
        {
            swap(nums[fill2], nums[i]);
            fill2--;
        }
        else
        {
            i++;
        }
    }
}

void testSortColors()
{
    vector<pair<vector<int>, vector<int>>> tests
    {
        // pair vector<int> -- input, vector<int> -- expect
        {
            { 0 }, { 0 }
        },
        {
            { 0, 1 }, { 0, 1 }
        },
        {
            { 1, 0 }, { 0, 1 }
        },
        {
            { 0, 2 }, { 0, 2 }
        },
        {
            { 2, 0 }, { 0, 2 }
        },
        {
            { 0, 1, 2 }, { 0, 1, 2 }
        },
        {
            { 1, 0, 2 }, { 0, 1, 2 }
        },
        {
            { 2, 0, 1 }, { 0, 1, 2 }
        },
        {
            { 1, 0, 1, 0 }, { 0, 0, 1, 1 }
        },
        {
            { 1, 0, 1, 0, 2, 0, 2, 0, 1, 1 }, { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2 }
        },
    };
    
    for( auto& p : tests )
    {
        vector<int> input = p.first;
        sortColors( p.first );
        for( int i = 0; i < p.first.size(); i++ )
        {
            if( p.first[i] != p.second[i] )
            {
                cout << " failed for cases: " << endl;;
                
                for_each(input.begin(), input.end(), [](int value )
                         {
                             cout << value << " ";
                         });
                cout << endl;
                
                break;
            }
        }
    }
}

#pragma mark - run

void Level7::Run()
{
    testSortColors();
}
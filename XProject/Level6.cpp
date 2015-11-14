//
//  Level6.cpp
//  XProject
//
//  Created by Roye Li on 11/13/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Level6.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <set>
#include <cmath>

using namespace std;

#pragma mark - minPathSum

//Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
//
//Note: You can only move either down or right at any point in time.
int minPathSum(vector<vector<int>>& grid)
{
    vector<vector<int>> dp( grid.size(), vector<int>( grid[0].size() ) );
    for( int i = dp.size() - 1; i >= 0; i-- )
    {
        for( int j = dp[i].size() - 1; j >= 0; j-- )
        {
            if( i == dp.size() - 1 )
            {
                if( j == dp[i].size() - 1 )
                    dp[i][j] = grid[i][j];
                else
                    dp[i][j] = dp[i][j+1] + grid[i][j];
            }
            else if( j == dp[i].size() - 1 )
            {
                dp[i][j] = dp[i+1][j] + grid[i][j];
            }
            else
            {
                dp[i][j] = min(dp[i+1][j], dp[i][j+1]) + grid[i][j];
            }
        }
    }
    
    return dp[0][0];
}

void testMinPathSum()
{
    vector<vector<vector<int>>> grids =
    {
//        {
//            {0}
//        },
//        {
//            {0, 0, 1}
//        },
//        {
//            {0},
//            {0},
//            {1}
//        },
//        {
//            {0, 1},
//            {1, 0}
//        },
//        {
//            {0, 0},
//            {1, 0}
//        },
//        {
//            {0, 1},
//            {0, 0}
//        },
//        {
//            {0, 0, 1},
//            {1, 0, 0},
//            {0, 1, 0}
//        },
//        {
//            {0, 1, 100},
//            {100, 100, 0},
//            {0, 0, 0}
//        }
        {
            {7,0,8,8,0,3,5,8,5,4},
            {4,1,2,9,9,6,0,8,6,9},
            {9,7,1,1,0,1,2,4,1,7}
        }
    };
    
    for( auto& grid : grids )
    {
        cout << minPathSum(grid) << endl;
    }
}

#pragma mark - run

void Level6::Run()
{
    testMinPathSum();
}
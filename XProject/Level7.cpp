//
//  Level7.cpp
//  XProject
//
//  Created by Roye Li on 11/21/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

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

#pragma mark - combine
//Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
//
//For example,
//If n = 4 and k = 2, a solution is:
//
//[
// [2,4],
// [3,4],
// [2,3],
// [1,2],
// [1,3],
// [1,4],
// ]
vector<vector<int>> combine(int n, int k)
{
    if( n < k || k < 0 )
    {
        return vector<vector<int>>();
    }
    
    
    vector<vector<int>> output;
    if( k == 1 )
    {
        for( int i = 1; i <= n; i ++ )
        {
            output.push_back( { i } );
        }
        
        return output;
    }
    
    for( int i = n; i >= 1; i-- )
    {
        vector<vector<int>> c = combine( i - 1, k - 1 );
        for( vector<int> v : c )
        {
            vector<int> t = v;
            t.push_back( i );
            
            output.push_back( t );
        }
    }
    
    return output;
}

void testCombine()
{
    int n = 10;
    int k = 7;
    auto r = combine(n, k);
    
    cout << "Size check " << (r.size() == factorial(n) / (factorial(k) * factorial(n - k) )? "Pass" : "Fail") << endl;
    cout << "Expect Size " << factorial(n) / (factorial(k) * factorial(n - k) ) << endl;
    cout << "Acutal Size " << r.size() << endl;
    
    for( auto& v : r )
    {
        cout << "{";
        for_each(v.begin(), v.end(), []( int i )
                 {
                     cout << i << " ";
                 });
        cout << "}" << endl;
    }
}

#pragma mark - subsets

//Given a set of distinct integers, nums, return all possible subsets.
//
//Note:
//Elements in a subset must be in non-descending order.
//The solution set must not contain duplicate subsets.
//For example,
//If nums = [1,2,3], a solution is:
//
//[
// [3],
// [1],
// [2],
// [1,2,3],
// [1,3],
// [2,3],
// [1,2],
// []
// ]
vector<vector<int>> subsets(vector<int>& nums)
{
    sort( nums.begin(), nums.end() );
    
    vector<vector<int>> output;
    output.push_back({});
    for( int i = 1; i <= nums.size(); i++ )
    {
        vector<vector<int>> c = combine(nums.size(), i);
        for( auto& v : c )
        {
            vector<int> tmp;
            for( auto& j : v )
                tmp.push_back(nums[j - 1]);
            
            output.push_back(tmp);
        }
    }
    
    return output;
}

void testSubsets()
{
    vector<int> v = {8, 4, 1};
    vector<vector<int>> o = subsets(v);
    
    for( auto & t : o )
    {
        for_each(t.begin(), t.end(), []( int number )
                 {
                     cout << number << " ";
                 });
        cout << endl;
    }
}

#pragma mark - exist

bool _exist(vector<vector<char>>& board, vector<vector<bool>>& visited, int x, int y, string word, int wordIndex )
{
    if( wordIndex >= 0 && wordIndex < word.size() )
    {
        if( board[x][y] != word[wordIndex] )
        {
            return false;
        }
        else
        {
            // last char, found it.
            if( wordIndex == word.size() - 1 )
                return true;
        }
    }
    
    // Go 4 directions and see if we can find the match.
    vector<pair<int, int>> dirs =
    {
        { 1, 0},
        { 0, 1 },
        { -1, 0},
        { 0, -1},
    };
    
    for( auto& dir : dirs )
    {
        int newX = x + dir.first;
        int newY = y + dir.second;
        
        if( newX >= 0 && newX < visited.size() &&
           newY >= 0 && newY < visited[x].size()
           && !visited[newX][newY] )
        {
            visited[newX][newY] = true;
            
            if(_exist(board, visited, newX, newY, word, wordIndex + 1) )
                return true;
            
            visited[newX][newY] = false;
        }
    }
    
    return false;
}

//Given a 2D board and a word, find if the word exists in the grid.
//
//The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.
//
//For example,
//Given board =
//
//[
// ['A','B','C','E'],
// ['S','F','C','S'],
// ['A','D','E','E']
// ]
//word = "ABCCED", -> returns true,
//word = "SEE", -> returns true,
//word = "ABCB", -> returns false.
bool exist(vector<vector<char>>& board, string word)
{
    vector<vector<bool>> visited( board.size(), vector<bool>( board[0].size() ) );
    
    for( int i = 0; i < board.size(); i++ )
    {
        for( int j = 0; j < board[i].size(); j++ )
        {
            visited[i][j] = true;

            if( _exist(board, visited, i, j, word, 0 ) )
                return true;
            
            visited[i][j] = false;
        }
    }
    
    return false;
}

void testExist()
{
    vector<vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    cout << exist(board, "ABCCED" );
    cout << exist(board, "SEE" );
    cout << exist(board, "ABCB" );
}

#pragma mark - removeDuplicates

//Remove Duplicates from Sorted Array II
//Follow up for "Remove Duplicates":
//What if duplicates are allowed at most twice?
//
//For example,
//Given sorted array nums = [1,1,1,2,2,3],
//
//Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.
//
static int removeDuplicates(vector<int>& nums)
{
    int i = 0;
    int j = 0;
    while( j < nums.size() )
    {
        int oldJ = j;
        while( j + 1 < nums.size() && nums[j] == nums[j+1] )
        {
            j++;
        }
        
        if( j - oldJ >= 1 )
        {
            nums[i++] = nums[j];
            nums[i++] = nums[j];
        }
        else
        {
            nums[i++] = nums[j];
        }
        j++;
    }
    
    return i;
}

static void testRemoveDuplicates()
{
    
    vector<vector<int>> tests = {
        {1,1,1,1,3,3},
        {1,1,1,2,2,3},
        {},
        {1},
        {1,1},
        {1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2}
    };
    for( auto& nums : tests )
        cout << removeDuplicates(nums) << endl;
}

#pragma mark - search
int binary_search(const vector<int>& sorted_vec, int begin, int end, int key) {
    size_t mid, left = begin ;
    size_t right = end;
    while (left < right) {
        mid = left + (right - left)/2;
        if (key > sorted_vec[mid]){
            left = mid+1;
        }
        else if (key < sorted_vec[mid]){
            right = mid;
        }
        else {
            return mid;
        }
    }
    
    return -1;
}

//Suppose a sorted array is rotated at some pivot unknown to you beforehand.
//
//(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
//
//You are given a target value to search. If found in the array return its index, otherwise return -1.
//
//You may assume no duplicate exists in the array.
//
static int search(vector<int>& nums, int target)
{
    // 0 1 2 4 5 6 7 -> 4 5 6 7 0 1 2
    // find the pivot.
    int begin = 0;
    int end = nums.size();
    while( begin < end )
    {
        int mid = ( begin + end ) / 2;
        if( nums[begin] < nums[mid] )
        {
            begin = mid;
        }
        else
        {
            end = mid;
        }
    }
    
    // Now binary search.
    int b = binary_search(nums, 0, begin + 1, target);
    if( b != -1 )
        return b;
    
    return binary_search(nums, begin + 1, nums.size(), target);
}

static void testSearch()
{
    vector<int> array = { 1, 2, 3, 4, 5 };
    for( int loop = 0; loop < 5; loop++ )
    {
        int first = array.front();
        for( int i = 0; i < array.size(); i++ )
        {
            array[i] = array[i+1];
        }
        array.back() = first;
        
        for_each(array.begin(), array.end(), [](int value )
                 {
                     cout << value << " ";
                 });
        cout << endl;
        
        cout << search(array, 1) << endl;
    }
    
    array = { 1 };
    cout << search(array, 0) << endl;
    
    array = { 1 };
    cout << search(array, 1) << endl;

}

#pragma mark - run

void Level7::Run()
{
    testSearch();
}
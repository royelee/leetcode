//
//  Level17.cpp
//  XProject
//
//  Created by Roye Li on 10/20/16.
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

//Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.
//
//For example, given the array [2,3,1,2,4,3] and s = 7,
//the subarray [4,3] has the minimal length under the problem constraint.
int minSubArrayLen(int s, vector<int>& nums)
{
    if( nums.size() == 0 )
        return 0;
    if( nums.size() == 1 )
        return nums[0] >= s ? 1 : 0;
    
    int left = 0;
    int right = 0;
    int sum = nums[0];
    int minLen = sum >= s ? 1 : 0;
    while( right < nums.size() && left < nums.size() )
    {
        if( sum  < s )
        {
            right++;
            sum += nums[right];
        }
        else
        {
            if( minLen == 0 )
                minLen = right - left + 1;
            else
                minLen = min( right - left + 1, minLen );
            sum -= nums[left];
            if( left == right )
            {
                right++;
                sum += nums[right];
            }
            left++;
        }
    }
    
    return minLen;
}

void testMinSubArrayLen()
{
    vector<int> tests = {2,3,1,2,4,3};
    cout << minSubArrayLen(7, tests);
}

#pragma mark - findOrder
//There are a total of n courses you have to take, labeled from 0 to n - 1.
//
//Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
//
//Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
//
//There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.
//
//For example:
//
//2, [[1,0]]
//There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]
//
//4, [[1,0],[2,0],[3,1],[3,2]]
//There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].
//
//Note:
//The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
//
//click to show more hints.
//
//Hints:
//This problem is equivalent to finding the topological order in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
//Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
//Topological sort could also be done via BFS.
bool _findOrder( vector<set<int>>& pre, size_t current, vector<bool>& visited, vector<bool>& visiting, vector<int>& out )
{
    if( visited[current] )
        return true;
    if( visiting[current] )
        return false;
    
    visiting[current] = true;
    
    for( auto& neighboor : pre[current] )
        if( !_findOrder(pre, neighboor, visited, visiting, out) )
            return false;
    
    visiting[current] = false;
    visited[current] = true;
    out.push_back(static_cast<int>(current));
    return true;
}

vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites)
{
    vector<set<int>> pre( numCourses );
    for( const auto& p : prerequisites )
    {
        pre[p.first].insert(p.second);
    }
    
    vector<bool> visited( numCourses, false );
    vector<bool> visiting( numCourses, false );
    vector<int> out;
    for( size_t i = 0; i < numCourses; i++ )
        if( !_findOrder(pre, i, visited, visiting, out) )
            return {};
    
    return out;
}

void testFindOrder()
{
    vector<pair<int, int>> prerequisities = {
        {1, 0}, {2, 0}, {3, 1}, {3, 2}
    };
    vector<int> o = findOrder(4, prerequisities);
    for( auto& i : o )
        cout << i << " ";
    cout << endl;
    
    vector<pair<int, int>> prerequisities1 = {{0,1}, {1,0}};
    vector<int> o1 = findOrder(2, prerequisities1);
    for( auto& i : o1 )
        cout << i << " ";
}

#pragma mark - WordDictionary
//Design a data structure that supports the following two operations:
//
//void addWord(word)
//bool search(word)
//search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.
//
//For example:
//
//addWord("bad")
//addWord("dad")
//addWord("mad")
//search("pad") -> false
//search("bad") -> true
//search(".ad") -> true
//search("b..") -> true
//Note:
//You may assume that all words are consist of lowercase letters a-z.
//
//click to show hint.
//
//You should be familiar with how a Trie works. If not, please work on this problem: Implement Trie (Prefix Tree) first.
struct WordDictionaryData
{
    vector<unique_ptr<WordDictionaryData>> childs{ 26 };
    int wordCount { 0 };
};

class WordDictionary {
public:
    WordDictionary() : root( new WordDictionaryData() )
    {
    }
    
    // Adds a word into the data structure.
    void addWord(string word)
    {
        WordDictionaryData* node = root.get();
        for( auto& c : word )
        {
            int index = c - 'a';
            if( node->childs[index] == nullptr )
                node->childs[index].reset( new WordDictionaryData );
            
            node = node->childs[index].get();
        }
        
        node->wordCount++;
    }
    
    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word)
    {
        return _search( word, root.get() );
    }
    
private:
    bool _search( string word, WordDictionaryData* node )
    {
        if( node == nullptr )
            return false;
        if( word.size() == 0 )
            return node->wordCount > 0;
        
        char c = word[0];
        word.erase(0, 1);
        
        if( c == '.' )
        {
            for( auto& child : node->childs )
            {
                if( child.get() && _search(word, child.get() ) )
                    return true;
            }
            
            return false;
        }
        else
        {
            int index = c - 'a';
            return _search(word, node->childs[index].get());
        }
    }
    
    unique_ptr<WordDictionaryData> root;
};

void testWordDictionary()
{
    // Your WordDictionary object will be instantiated and called as such:
    WordDictionary wordDictionary;
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    cout << wordDictionary.search("pad") << endl;// -> false
    cout << wordDictionary.search("bad") << endl;//-> true
    cout << wordDictionary.search(".ad") << endl;// -> true
    cout << wordDictionary.search("b..") << endl;// -> true
}

#pragma mark - rob
//After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.
//
//Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
static int _rob(vector<int>& nums)
{
    if( nums.size() == 0 )
        return 0;
    if( nums.size() == 1 )
        return nums.front();
    
    vector<int> dp( nums.size(), 0 );
    dp[0] = nums[0];
    dp[1] = nums[1] > dp[0] ? nums[1] : dp[0];
    for( size_t i = 2; i < nums.size(); i++ )
    {
        dp[i] = max( dp[i -1], dp[i-2] + nums[i]);
    }
    
    return dp.back();
}

static int rob(vector<int>& nums)
{
    if( nums.size() == 0 || nums.size() == 2 )
        return 0;
    if( nums.size() == 1 )
        return nums[0];
    
    int n1 = nums.front();
    
    nums.erase(nums.begin());
    int v1 = _rob(nums);
    nums.insert(nums.begin(), n1);
    nums.erase(nums.end() - 1);
    int v2 = _rob(nums);
    return max(v1, v2);
}

static void testRob()
{
    vector<int> tests = {0, 0, 0};
    cout << rob(tests) << endl;
    
    vector<int> t = {183,219,57,193,94,233,202,154,65,240,97,234,100,249,186,66,90,238,168,128,177,235,50,81,185,165,217,207,88,80,112,78,135,62,228,247,211};
    cout << rob(t) << endl;
    
    vector<int> t1 = {1,3,1,3,100};
    cout << rob(t1) << endl;
}

#pragma mark - findKthLargest
//Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.
//
//For example,
//Given [3,2,1,5,6,4] and k = 2, return 5.
//
//Note:
//You may assume k is always valid, 1 ≤ k ≤ array's length.
int _findKthLargest(vector<int>& nums, int start, int end, int k)
{
    int pivot = nums[end];
    int i = start;
    for( int j = start; j < end; j++ )
    {
        if( nums[j] <= pivot )
        {
            swap(nums[i], nums[j]);
            i++;
        }
    }
    
    swap(nums[i], nums[end]);
    
    // ( i - start ), i, ( i - end )
    int lessEqThanPivotCount = i - start + 1;
    if( k == lessEqThanPivotCount )
        return nums[i];
    else if( k < lessEqThanPivotCount )
        return _findKthLargest(nums, start, i - 1, k );
    else
        return _findKthLargest(nums, i + 1, end, k - lessEqThanPivotCount);
}

int findKthLargest(vector<int>& nums, int k)
{
    if( k >= 1 && k <= nums.size() )
        return _findKthLargest(nums, 0, (int)nums.size() - 1, (int)nums.size() - k + 1);
    
    return -1;
}

void testFindKthLargest()
{
    for( int k = 1; k <= 6; k++ )
    {
        vector<int> t1 = {3,2,1,5,6,4};
        cout << findKthLargest(t1, k) << endl;
    }
    
    for( int k = 1; k <= 2; k++ )
    {
        vector<int> t1 = {3};
        cout << findKthLargest(t1, k) << endl;
    }
}

#pragma mark - combinationSum3
//Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
//
//
//Example 1:
//
//Input: k = 3, n = 7
//
//Output:
//
//[[1,2,4]]
//
//Example 2:
//
//Input: k = 3, n = 9
//
//Output:
//
//[[1,2,6], [1,3,5], [2,3,4]]
void bfCombinationSum3( int start, int level, int askValue, vector<int>& curCom, vector<vector<int>>& out )
{
    if( level < 0 || askValue < 0 )
        return;
    
    if( askValue == 0 && level == 0 )
    {
        out.push_back(curCom);
        return;
    }
    
    for( int i = start; i <= 10 - level; i++ )
    {
        curCom.push_back(i);
        
        bfCombinationSum3(i + 1, level - 1, askValue - i, curCom, out);
        
        curCom.pop_back();
    }
}

vector<vector<int>> combinationSum3(int k, int n)
{
    vector<int> cur;
    vector<vector<int>> out;
    bfCombinationSum3(1, k, n, cur, out);
    
    return out;
}

void testCombinationSum3()
{
    vector<vector<int>> o = combinationSum3(3, 15);
    for( auto& v : o )
    {
        for( auto& i : v )
            cout << i << " ";
        
        cout << endl;
    }
}

#pragma mark - containsDuplicate
//Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.
bool containsDuplicate(vector<int>& nums)
{
    if( nums.size() == 0 )
        return false;

    sort(nums.begin(), nums.end());
    for( int i = 0; i < nums.size() - 1; i++ )
    {
        if( nums[i] == nums[i+1] )
            return true;
    }
    
    return false;
}

#pragma mark - containsNearbyDuplicate
//Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k.
bool containsNearbyDuplicate(vector<int>& nums, int k)
{
    if( k == 0 || nums.size() == 0 )
        return false;
    
    vector<pair<int, int>> numsP;
    for( size_t i = 0; i < nums.size(); i++ )
    {
        numsP.push_back(make_pair(nums[i], i));
    }
    
    sort(numsP.begin(), numsP.end(), [](pair<int, int> left, pair<int, int> right)
    {
        return left.first < right.first;
    });
    
    for( size_t i = 0; i < numsP.size() - 1; i++ )
    {
        const auto& p = numsP[i];
        const auto& pNext = numsP[i+1];
        if( p.first == pNext.first && abs(p.second - pNext.second) <= k )
            return true;
    }
    
    return false;
}

void testContainsNearbyDuplicate()
{
    vector<int> v = {-1, -1};
    cout << containsNearbyDuplicate(v, 1);
}

#pragma mark - containsNearbyAlmostDuplicate
//Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
{
    if( t < 0 || k < 1 )
        return false;
    
    // Use bucket.
    int minNum = *min_element(nums.begin(), nums.end());
    map<int64_t, int64_t> bucket;
    for( int i = 0; i < nums.size(); i++ )
    {
        int64_t n = (int64_t)nums[i] - minNum;
        int64_t idx = n / ( t + 1 );
        if( ( bucket.find(idx) != bucket.end() ) ||
            ( bucket.find(idx - 1) != bucket.end() && abs( bucket[idx-1] - n ) <= t ) ||
            ( bucket.find(idx + 1) != bucket.end() && abs( bucket[idx+1] - n ) <= t ) )
            return true;
        
        if( i >= k )
            bucket.erase(((int64_t)nums[i-k] - minNum) / ( t + 1 ) );
        
        bucket[idx] = n;
    }

    return false;
}

void testContainsNearbyAlmostDuplicate()
{
    vector<int> t = {-1,-1};
    cout << containsNearbyAlmostDuplicate(t,1, -1) << endl; // false
    
    cout << containsNearbyAlmostDuplicate(t,1, 0) << endl;  // true
    
    t = {1,3,1};
    cout << containsNearbyAlmostDuplicate(t,1, 1) << endl;  // false
    
    // Integer max test
    t = {-1,2147483647};
    cout << containsNearbyAlmostDuplicate(t,1, 2147483647) << endl; // false
    
    t = {7,1,3};
    cout << containsNearbyAlmostDuplicate(t,2, 3) << endl;  // true
    
    t = {7,2,8};
    cout << containsNearbyAlmostDuplicate(t,2, 1) << endl;  // true
    
    t = {3,6,0,4};
    cout << containsNearbyAlmostDuplicate(t,2, 2) << endl;  // true
    
    t = {-3,3};
    cout << containsNearbyAlmostDuplicate(t,2, 4) << endl;  // false
}

#pragma mark - computeArea
//Find the total area covered by two rectilinear rectangles in a 2D plane.
//
//Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
//                           (C, D)
//     +--------------------+
//     |                    |
//     |                    |
//     |                    |
//     |            +------------------------------+(G, H)
//     |            |       |                      |
//     |            |       |                      |
//     +--------------------+                      |
//(A, B)            |                              |
//                  |                              |
//   Y              |                              |
//   ^              |                              |
//   |              +------------------------------+
//   |            (E, F)
//  (0, 0) ---------> X
//Rectangle Area
//Assume that the total area is never beyond the maximum possible value of int.
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    int area = abs(C-A) * abs(D-B) + abs(G-E) * abs(H-F);
    if( !(E > C || G < A || H < B || F > D ) )  // intersection.
    {
        int leftX = E >= A && E <= C ? E : A;
        int rightX = G >= A && G <= C ? G : C;
        int topY = H >= B && H <= D ? H : D;
        int bottomY = F >= B && F <= D ? F : B;
        area -= abs(rightX - leftX) * abs(bottomY - topY);
    }
    
    return area;
}

void testComputeArea()
{
    cout << computeArea(-3, 0, 3, 4, 0, -1, 9, 2) << endl;  // 45
    cout << computeArea(0,0,0,0,-1,-1,1,1) << endl; //4
}

#pragma mark - run

void Level17::Run()
{
    testContainsNearbyAlmostDuplicate();
}
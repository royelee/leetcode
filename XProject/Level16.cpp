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
#include <unordered_map>

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

#pragma mark - rightSideView
//Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
//
//For example:
//Given the following binary tree,
//   1            <---
// /   \
//2     3         <---
// \     \
//  5     4       <---
//You should return [1, 3, 4].
vector<int> rightSideView(TreeNode* root)
{
    struct LevelTreeNode
    {
        TreeNode* node{ nullptr };
        int level{ -1 };
        LevelTreeNode( TreeNode* n, int l ) : node( n ), level( l ) {}
    };
    
    queue<LevelTreeNode> q;
    q.push( { root, 1 } );
    
    vector<int> out;
    TreeNode* lastVisited = nullptr;
    int currentLevel = 1;
    while( !q.empty() )
    {
        LevelTreeNode tmp = q.front();
        q.pop();
        if( tmp.node != nullptr )
        {
            if( tmp.node->left )
                q.push( { tmp.node->left, tmp.level + 1 } );
            
            if( tmp.node->right )
                q.push( { tmp.node->right, tmp.level + 1 } );
        }
        
        if( tmp.level != currentLevel )
        {
            // Go into next level, now last visit is most right node.
            currentLevel = tmp.level;
            out.push_back(lastVisited->val);
        }
        
        lastVisited = tmp.node;
    }
    
    if( lastVisited )
        out.push_back(lastVisited->val);

    return out;
}

void testRightSideView()
{
    TreeNode* n1 = new TreeNode(1);
    n1->left = new TreeNode(2);
    n1->right = new TreeNode(3);
    
    vector<int> v = rightSideView(n1);
    for( auto& i : v )
        cout << i << ", ";
}

#pragma mark - numIslands
//Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
//
//Example 1:
//
//11110
//11010
//11000
//00000
//Answer: 1
//
//Example 2:
//
//11000
//11000
//00100
//00011
//Answer: 3
int numIslands(vector<vector<char>>& grid)
{
    int founded = 0;
    for( int i = 0; i < grid.size(); i++ )
    {
        for( int j = 0; j < grid[i].size(); j++ )
        {
            if( grid[i][j] == '1' )
            {
                founded++;
                grid[i][j] = 'X';
                
                // Dig the island.
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                while( !q.empty() )
                {
                    auto currentPos = q.front();
                    q.pop();
                    // Go four directions
                    if( currentPos.first - 1 >= 0 && grid[currentPos.first-1][currentPos.second] == '1' )
                    {
                        q.push(make_pair(currentPos.first-1, currentPos.second));
                        grid[currentPos.first-1][currentPos.second] = 'X';
                    }
                    if( currentPos.first + 1 < grid.size() && grid[currentPos.first+1][currentPos.second] == '1' )
                    {
                        q.push(make_pair(currentPos.first+1, currentPos.second));
                        grid[currentPos.first+1][currentPos.second] = 'X';
                    }
                    if( currentPos.second - 1 >= 0 && grid[currentPos.first][currentPos.second-1] == '1' )
                    {
                        q.push(make_pair(currentPos.first, currentPos.second-1));
                        grid[currentPos.first][currentPos.second-1] = 'X';
                    }
                    if( currentPos.second + 1 < grid[0].size() && grid[currentPos.first][currentPos.second+1] == '1' )
                    {
                        q.push(make_pair(currentPos.first, currentPos.second+1));
                        grid[currentPos.first][currentPos.second+1] = 'X';
                    }
                }
            }
        }
    }
    
    return founded;
}

void testNumIslands()
{
    vector<vector<char>> t = {
        { '1','1','0','0','0' },
        { '1','1','0','0','0' },
        { '0','0','1','0','0' },
        { '0','0','0','1','1' }
    };
    vector<vector<char>> t1 = {{'1','0','1','1','0','1','1'}};
    vector<vector<char>> t2 =
    {
        {'1','1','1'},
        {'0','1','0'},
        {'1','1','1'}
    };
    vector<string> t3s = {
        "11111011111111101011",
        "01111111111110111110",
        "10111001101111111111",
        "11110111111111111111",
        "10011111111111111111",
        "10111111011101110111",
        "01111111111101101111",
        "11111111111101111011",
        "11111111110111111111",
        "11111111111111111111",
        "01111111011111111111",
        "11111111111111111111",
        "11111111111111111111",
        "11111011111110111111",
        "10111110111011110111",
        "11111111111101111110",
        "11111111111110111100",
        "11111111111111111111",
        "11111111111111111111",
        "11111111111111111111"
    };
    vector<vector<char>> t3;
    for( auto& s : t3s )
    {
        vector<char> cs;
        for( auto& c : s )
            cs.push_back(c);
        t3.push_back(cs);
    }
    
    cout << numIslands(t3);
}

#pragma mark - rangeBitwiseAnd
//Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
//
//For example, given the range [5, 7], you should return 4.
int rangeBitwiseAnd(int m, int n)
{
    uint32_t um = static_cast<uint32_t>(m);
    uint32_t un = static_cast<uint32_t>(n);
    uint32_t count = n - m;
    uint32_t rtn = 0;
    uint32_t c = 1;
    uint32_t um1 = um | un;
    uint32_t all1 = 1;
    while( um1 > 0 )
    {
        uint32_t countToAll1 = all1 - ( all1 & um );
        uint32_t t = um & c;
        if( t != 0 &&  count <= countToAll1 )
            rtn |= t;
        c = c << 1;
        um1 >>= 1;
        all1 <<= 1;
        all1 |= 1;
    }
    
    return rtn;
}

int btRangeBitwiseAnd(int m, int n)
{
    int rtn = m;
    for( int i = m; i <= n; i++ )
        rtn &= i;
    
    return rtn;
}

void testRangeBitwiseAnd()
{
    rangeBitwiseAnd(8, 16);
    
    for( int j = 0; j < 1000; j++ )
    {
        for( int i = 1; i < 1000; i++ )
        {
            int m = j;
            int n = j+i;
            if( rangeBitwiseAnd(m,n) != btRangeBitwiseAnd(m, n) )
            {
                cout << "m = " << m << " n = " << n << " ";
                cout << rangeBitwiseAnd(m, n) << " , " << btRangeBitwiseAnd(m, n) << endl;
            }
        }
    }
}

#pragma mark - isHappy
//Write an algorithm to determine if a number is "happy".
//
//A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.
//
//Example: 19 is a happy number
//
//1^2 + 9^2 = 82
//8^2 + 2^2 = 68
//6^2 + 8^2 = 100
//1^2 + 0^2 + 0^2 = 1
bool isHappy(int n) {
    if( n <= 0 )
        return false;
    
    set<int> repeated;
    int c = n;
    while(true)
    {
        int next = 0;
        while( c > 0 )
        {
            next += (c % 10) * (c % 10);
            c = c / 10;
        }
        
        if( repeated.find(next) == repeated.end() )
            repeated.insert(next);
        else
            return false;

        c = next;
        if( c == 1 )
            return true;
    }
    
    return false;
}

void testIsHappy()
{
    for( int i = 1; i < 100; i++ )
        cout << "i = " << i << isHappy(i) << endl;
}

#pragma mark - removeElements
//Remove all elements from a linked list of integers that have value val.
//
//Example
//Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
//Return: 1 --> 2 --> 3 --> 4 --> 5
ListNode* removeElements(ListNode* head, int val)
{
    unique_ptr<ListNode> newHead( new ListNode(-1) );
    newHead->next = head;
    
    ListNode* it = newHead.get();
    while(it->next)
    {
        ListNode* next = it->next;
        if( next->val == val )
        {
            it->next = next->next;
        }
        else
            it = it->next;
    }
    
    return newHead->next;
}

void testRemoveElements()
{
    auto PrintList = [](ListNode* head)
    {
        ListNode* it = head;
        while(it)
        {
            cout << it->val << ", ";
            it = it->next;
        }
        cout << endl;
    };
    
    ListNode* head = new ListNode(6);
    PrintList(removeElements(head, 6));
    
    head = new ListNode(6);
    head->next = new ListNode(2);
    head->next->next = new ListNode(6);
    PrintList(removeElements(head, 6));
    
    head = new ListNode(4);
    head->next = new ListNode(2);
    PrintList(removeElements(head, 6));
}

#pragma mark - countPrimes
//Count the number of prime numbers less than a non-negative number, n.
int countPrimes(int n)
{
    vector<bool> primes(n, true);
    primes[0] = false;
    primes[1] = false;
    
    for( int i = 2; i * i < n; i++)
    {
        if( !primes[i] ) continue;
        for( int j = i * i; j < n; j = j + i )
            primes[j] = false;
    }
    
    int count = 0;
    for( const auto& b : primes )
        if( b ) count++;
    
    return count;
}

#pragma mark - isIsomorphic
//Given two strings s and t, determine if they are isomorphic.
//
//Two strings are isomorphic if the characters in s can be replaced to get t.
//
//All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.
//
//For example,
//Given "egg", "add", return true.
//
//Given "foo", "bar", return false.
//
//Given "paper", "title", return true.
//
//Note:
//You may assume both s and t have the same length.
bool isIsomorphic(string s, string t)
{
    unordered_map<char, char> froms;
    unordered_map<char, char> tos;
    for( size_t i = 0; i < s.length(); i++ )
    {
        char from = s[i];
        char to = t[i];
        // from -> to
        
        if( froms.find(from) == froms.end() )
        {
            if( tos.find(to) == tos.end() )
            {
                froms[from] = to;
                tos[to] = from;
            }
        }
        
        if( froms.find( from ) != froms.end() && froms[from] == to )
            continue;
        else
            return false;
    }
    
    return true;
}

void testIsIsomorphic()
{
    vector<string> tests = {
        "aba", "baa",//false
        "ab", "aa",//false
        "egg", "add",//true
        "foo", "bar",//false
        "paper", "title"//true
    };

    for( size_t i = 0; i < tests.size(); i = i + 2)
    {
        cout << tests[i] << " " << tests[i+1] << " = " << isIsomorphic(tests[i], tests[i+1]) << endl;
    }
}

#pragma mark - reverseList
//Reverse a singly linked list.
ListNode* reverseList(ListNode* head)
{
    ListNode* it = head;
    ListNode* pre = nullptr;
    while( it )
    {
        ListNode* cur = it;
        it = cur->next;
        cur->next = pre;
        pre = cur;
    }
    
    return pre;
}

#pragma mark - canFinish
//There are a total of n courses you have to take, labeled from 0 to n - 1.
//
//Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
//
//Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?
//
//For example:
//
//2, [[1,0]]
//There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
//
//2, [[1,0],[0,1]]
//There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
//
//Note:
//The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
//
//click to show more hints.
//
//Hints:
//This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
//Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
//Topological sort could also be done via BFS.
bool detectCycle( vector<bool>& visiting, vector<bool>& visited, int current, vector<pair<int, int>>& prerequisities )
{
    if( visiting[current] )
        return true;
    
    if( visited[current] )
        return false;
    
    visiting[current] = true;
    
    for( auto& p : prerequisities )
    {
        if( p.first == current && detectCycle(visiting, visited, p.second, prerequisities) )
            return true;
    }
    
    visited[current] = true;
    visiting[current] = false;
    return false;
}

bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites)
{
    vector<bool> visiting( numCourses, false );
    vector<bool> visited( numCourses, false );
    
    for( int i = 0; i < numCourses; i++ )
    {
        if( detectCycle( visiting, visited, i, prerequisites ) )
            return false;
    }
    
    return true;
}

void testCanFinish()
{
    vector<pair<int,int>> t = { make_pair(1, 0), make_pair(0,1)};
    cout << canFinish(2,t) << endl;
    
    vector<pair<int,int>> t1 = { make_pair(0, 1), make_pair(0,2), make_pair(0, 3), make_pair(3, 4), make_pair(4, 5)};
    cout << canFinish(6,t1) << endl;
    
    t1.push_back(make_pair(5, 3));
    cout << canFinish(6, t1) << endl;
}

#pragma mark - Trie
//Implement a trie with insert, search, and startsWith methods.
//
//Note:
//You may assume that all inputs are consist of lowercase letters a-z.
// https://www.topcoder.com/community/data-science/data-science-tutorials/using-tries/
class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode()
    {
    }

    vector<unique_ptr<TrieNode>> childs{ 26 };
    int words { 0 };    // The number of words in the node.
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    
    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode* current = root;
        for( auto c : word )
        {
            int index = c - 'a';
            if( current->childs[index] == nullptr )
            {
                current->childs[index].reset(new TrieNode);
            }
            
            current = current->childs[index].get();
        }
        
        if( current )
            current->words++;
    }
    
    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode* current = root;
        for( auto c : word )
        {
            int index = c - 'a';
            if( current->childs[index] == nullptr )
                return false;
            
            current = current->childs[index].get();
        }
        
        return current != nullptr && current->words > 0;
    }
    
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix)
    {
        TrieNode* current = root;
        for( auto c : prefix )
        {
            int index = c - 'a';
            if( current->childs[index] == nullptr )
                return false;
            
            current = current->childs[index].get();
        }
        
        return current != nullptr;
    }
    
private:
    TrieNode* root;
};

void testTried()
{
    // Your Trie object will be instantiated and called as such:
    Trie trie;
    trie.insert("abc");
    trie.insert("abcd");
    trie.insert("bc");

    cout << trie.search("abc") << endl;
    cout << trie.startsWith("ab") << endl;
    cout << trie.startsWith("ae") << endl;
    cout << trie.startsWith("") << endl;
    cout << trie.search("bce") << endl;
    cout << trie.search("b") << endl;
    
    cout << "TEST 2" << endl;
    Trie trie1;
    trie1.insert("abc");
    cout << trie1.search("abc") << endl;//true
    cout << trie1.search("ab") << endl;//false
    trie1.insert("ab");
    cout << trie1.search("ab") << endl;//true
}

#pragma mark - run

void Level16::Run()
{
    testTried();
}

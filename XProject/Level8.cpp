//
//  Level8.cpp
//  XProject
//
//  Created by Roye Li on 12/4/15.
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

#pragma mark - deleteDuplicates
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//Given a sorted linked list, delete all duplicates such that each element appear only once.
//
//For example,
//Given 1->1->2, return 1->2.
//Given 1->1->2->3->3, return 1->2->3.
ListNode* deleteDuplicates(ListNode* head)
{
    ListNode* iter = head;
    while( iter )
    {
        ListNode* next = iter->next;
        while( next && iter->val == next->val )
        {
            iter->next = next->next;
            next = next->next;
        }
        
        iter = iter->next;
    }

    return head;
}

//Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
//
//For example,
//Given 1->2->3->3->4->4->5, return 1->2->5.
//Given 1->1->1->2->3, return 2->3.
ListNode* deleteDuplicates2(ListNode* head)
{
    ListNode* cur = head;
    ListNode* pre = new ListNode(-1);
    pre->next = head;
    ListNode* newHead = pre;
    while( cur != nullptr )
    {
        ListNode* next = cur->next;
        while( next && next->val == cur->val )
        {
            next = next->next;
        }
        
        if( next != cur->next )
        {
            // Found the duplicates, then we need to remove all the nodes duplicated.
            pre->next = next;
        }
        else
        {
            pre = cur;
        }

        cur = next;
    }
    
    return newHead->next;
}

void testDeleteDuplicates()
{
    vector<vector<int>> tests = {
        {},
        {1},
        {1,1},
        {1,1,1},
        {1,2,2,2},
        {1,2,2,2,3}
    };
    
    for( vector<int> v : tests )
    {
        ListNode* head = new ListNode(-1);
        ListNode* it = head;
        for( int i = 0; i < v.size(); i++ )
        {
            it->next = new ListNode(v[i]);
            it = it->next;
        }
        
        cout << "before" << endl;
        it = head->next;
        while( it )
        {
            cout << it->val << " ";
            it = it->next;
        }
        cout << endl;
        
        it = deleteDuplicates2( head->next );
        
        cout << "after" << endl;
        while( it )
        {
            cout << it->val << " ";
            it = it->next;
        }
        cout << endl;
    }
}

#pragma mark merge

//Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
//
//Note:
//You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;
    while( k >= 0 )
    {
        if( i >= 0 && j >= 0 )
        {
            if( nums1[i] < nums2[j] )
            {
                nums1[k] = nums2[j];
                j--;
            }
            else
            {
                nums1[k] = nums1[i];
                i--;
            }
        }
        else if( i < 0 )
        {
            nums1[k] = nums2[j];
            j--;
        }
        else
        {
            nums1[k] = nums1[i];
            i--;
        }

        k--;
    }
}

#pragma mark - partition
//Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
//
//You should preserve the original relative order of the nodes in each of the two partitions.
//
//For example,
//Given 1->4->3->2->5->2 and x = 3,
//return 1->2->2->4->3->5.
ListNode* partition(ListNode* head, int x)
{
    ListNode* bigHead = nullptr;
    ListNode* bigHeadIter = nullptr;
    ListNode* iter = head;
    ListNode* pre = nullptr;
    ListNode* newHead = nullptr;
    while( iter != nullptr )
    {
        ListNode* next = iter->next;

        if( iter->val >= x )
        {
            // Move to big head
            if( bigHead == nullptr )
            {
                bigHead = iter;
                bigHeadIter = bigHead;
            }
            else
            {
                bigHeadIter->next = iter;
                bigHeadIter = bigHeadIter->next;
            }
            
            if( pre )
                pre->next = iter->next;
            
            bigHeadIter->next = nullptr;
        }
        else
        {
            if( !pre )
                newHead = iter;
            pre = iter;
        }
        
        iter = next;
    }
    
    if( pre )
        pre->next = bigHead;

    return newHead ? newHead : bigHead;
}

void testPartition()
{
    vector<pair<vector<int>, int>> tests = {
        {{1,4,3,2,5,2}, 3},
        {{}, 0},
        {{1},1},
        {{1},2},
        {{1},0},
        {{1,1,1},1},
        {{2,2,1},2},
        {{2,2,2,2,1},1},
    };
    
    for( auto& t : tests )
    {
        vector<int>& v = t.first;
        ListNode* head = new ListNode(-1);
        ListNode* it = head;
        for( int i = 0; i < v.size(); i++ )
        {
            it->next = new ListNode(v[i]);
            it = it->next;
        }
        
        cout << "before" << endl;
        it = head->next;
        while( it )
        {
            cout << it->val << " ";
            it = it->next;
        }
        cout << endl;
        
        it = partition( head->next, t.second );
        
        cout << "after" << endl;
        while( it )
        {
            cout << it->val << " ";
            it = it->next;
        }
        cout << endl;
    }
}

#pragma mark - grayCode
//The gray code is a binary numeral system where two successive values differ in only one bit.
//
//Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
//
//For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
//
//00 - 0
//01 - 1
//11 - 3
//10 - 2
//Note:
//For a given n, a gray code sequence is not uniquely defined.
//
//For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.
//
//For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
vector<int> grayCode1(int n)
{
    int size = 1 << n;
    vector<int> binary( n );
    set<int> inserted;
    vector<int> output;
    
    output.push_back( 0 );
    inserted.insert( 0 );
    
    for( int i = 0; i < size - 1; i++ )
    {
        bool found = false;
        while (!found )
        {
            for( int k = n - 1; k >= 0; k-- )
            {
                int old = binary[k];

                binary[k] = ( binary[k] + 1 ) % 2;
                
                int binaryRep = 0;
                for( int j = n - 1; j >= 0 ; j-- )
                {
                    binaryRep += binary[j] << ( n - 1 - j );
                }
                // can't find it
                if( inserted.find( binaryRep ) == inserted.end() )
                {
                    output.push_back( binaryRep );
                    inserted.insert( binaryRep );
                    
                    found = true;
                    break;
                }
                else
                {
                    binary[k] = old;
                }
            }
        }
    }
    
    return output;
}

vector<int> grayCode(int n)
{
    vector<int> output;
    int size = 1 << n;
    output.push_back(0);
    for( int i = 1; i < size; i++ )
    {
        // bigest bit
        int t = i;
        int b = -1;
        while( t != 0 )
        {
            t = t >> 1;
            b++;
        }
        
        int base = 1 << b;
        int index = base - 1 - i % base;
        output.push_back(base + output[ index ]);
    }
    return output;
}

void testGrayCode()
{
    auto v = grayCode( 7 );
    for( auto& i : v )
    {
        cout << i << " ";
    }
    
    cout << endl;
    
    v = grayCode1( 7 );
    for( auto& i : v )
    {
        cout << i << " ";
    }
}

#pragma mark - subsetsWithDup
//Given a collection of integers that might contain duplicates, nums, return all possible subsets.
//
//Note:
//Elements in a subset must be in non-descending order.
//The solution set must not contain duplicate subsets.
//For example,
//If nums = [1,2,2], a solution is:
//
//[
// [2],
// [1],
// [1,2,2],
// [2,2],
// [1,2],
// []
//]
vector<vector<int>> subsetsWithDup(vector<int>& nums)
{
    //    添加数字构建subset
    //    
    //    起始subset集为：[]
    //    添加S0后为：[], [S0]
    //    添加S1后为：[], [S0], [S1], [S0, S1]
    //    添加S2后为：[], [S0], [S1], [S0, S1], [S2], [S0, S2], [S1, S2], [S0, S1, S2]
    //    红色subset为每次新增的。显然规律为添加Si后，新增的subset为克隆现有的所有subset，并在它们后面都加上Si。
    sort(nums.begin(), nums.end());
    
    vector<vector<int>> output;
    
    output.push_back({});
    for( int i = 0; i < nums.size(); i++ )
    {
        // Adding subset { nums[i] }
        // If it's duplicate, then the array is { nums[i] }, { nums[i], nums[i]} ... { nums[i]... }
        int d = i;
        while( d + 1 < nums.size() && nums[i] == nums[d+1] )
            d++;
        
        vector<vector<int>> adding;
        for( int j = 0; j < d - i + 1; j++ )
        {
            vector<int> c;
            for( int k = 0; k < j + 1; k++ )
                c.push_back(nums[i]);
            
            adding.push_back(c);
        }
        
        i = d;
        
        vector<vector<int>> backup = output;
        for( vector<int>& existed : backup )
        {
            for( vector<int>& newV : adding )
            {
                vector<int> old = existed;
                old.insert(old.end(), newV.begin(), newV.end() );
                output.push_back(old);
            }
        }
    }
    
    return output;
}

void testSubsetsWithDup()
{
    vector<int> tests = { 1, 2, 2, 3 };
    vector<vector<int>> r = subsetsWithDup( tests );
    for( auto& v : r )
    {
        cout << "[";
        for( auto& num : v )
        {
            cout << num << " ";
        }
        cout << "]" << endl;
    }
}

#pragma mark - numDecodings
void _numDecodings1( string s, string decoded, set<string>& decodedSet )
{
    if( s.size() == 0 )
    {
        decodedSet.insert(decoded);
        return;
    }
    
    char c = ( s[0] - '1' ) + 'A';
    if( s.size() == 1 )
    {
        decodedSet.insert(decoded + c);
        return ;
    }
    
    if( c > 'B' )
    {
        s.erase(0, 1);
        _numDecodings1(s, decoded + c, decodedSet);
    }
    else
    {
        int c1 = ( s[0] - '0' );
        int c2 = ( s[1] - '0' );
        
        {
            string s1 = s;
            s1.erase(0, 1);
            _numDecodings1(s1, decoded + c, decodedSet);
        }
        
        {
            string s2 = s;
            s2.erase(0, 2);
            _numDecodings1(s2, decoded + (char)('A' + c2 * 10 + c1 - 1), decodedSet);
        }
    }
}


//A message containing letters from A-Z is being encoded to numbers using the following mapping:
//
//'A' -> 1
//'B' -> 2
//...
//'Z' -> 26
//Given an encoded message containing digits, determine the total number of ways to decode it.
//
//For example,
//Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
//
//The number of ways decoding "12" is 2.
int numDecodings1(string s)
{
    set<string> decodedSet;
    _numDecodings1( s, "", decodedSet );
    for( auto& s : decodedSet )
        cout << s << " ";
    cout << endl << "======" << endl;
    return decodedSet.size();
}

int _decode(string s)
{
    if( s.size() == 0 )
        return 0;
    
    if( s.size() == 1 )
        return 1;
    
    if( s.size() == 2 )
    {
        if( s[0] > '2' )
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    
    if( s[0] > '2' )
    {
        return _decode(s.substr(1, s.size()));
    }
    else
    {
        return _decode(s.substr(1, s.size())) + _decode(s.substr(2, s.size()));
    }
}

int numDecodings(string s)
{
    // Using DP
    // For a array 1..n
    // Given index i, so the DP[i] =
    // 1) if s[1] + s[i-1] < 26, then DP[i] = DP[i-1] + DP[i-2] because
    
    //This is a really interesting problem. First, I will show how I would solve this problem. We will see that it is not that complicated when using recursion, and that the problem can be solved using dynamic programming. We will produce a general solution that does not hardcode an upper limit of 26 for each code point.
    //
    //A note on terminology: I will use the term code point (CP) not in the Unicode sense, but to refer to one of the code numbers 1 though 26. Each code point is represented as a variable number of characters. I will also use the terms encoded text (ET) and clear text (CT) in their obvious meanings. When talking about a sequence or array, the first element is called the head. The remaining elements are the tail.
    //
    //Theoretical Prelude
    //The EC "" has one decoding: the CT "".
    //The EC "3" can be destructured into '3' + "", and has one decoding.
    //The EC "23" can be destructured as '2' + "3" or '23' + "". Each of the tails has one decoding, so the whole EC has two decodings.
    //The EC "123" can be destructured as '1' + "23" or '12' + "3". The tails have two and one decodings respectively. The whole EC has three decodings. The destructuring '123' + "" is not valid, because 123 > 26, our upper limit.
    //… and so on for ECs of any length.
    if( s.size() == 0 )
        return 0;
    
    if( s[0] == '0' )
        return 0;
    
    vector<int> dp(s.size() + 1);
    dp[0] = 1;
    dp[1] = ( s[0] >='1' && s[0] <= '9' ) ? 1 : 0;
    for( int i = 1; i < s.size(); i++ )
    {
        if( s[i] != '0' )
            dp[i+1] += dp[i];
        int d = ( s[i-1] - '0' ) * 10 +  s[i] - '0';
        if( s[i-1] >= '1' && s[i-1] <= '2' && d <= 26 )
            dp[i+1] += dp[i-1];
        if( dp[i+1] == 0 )
            return 0;
    }
    
    return dp[s.size()];
}

void testNumDecodings()
{
    cout << numDecodings("10") << endl;
    cout << numDecodings("11") << endl;
    cout << numDecodings("27") << endl;
    cout << numDecodings("17") << endl;

    
    cout << numDecodings("4757562545844617494555774581341211511296816786586787755257741178599337186486723247528324612117156948") << endl;
    cout << _decode("4757562545844617494555774581341211511296816786586787755257741178599337186486723247528324612117156948") << endl;
    
//    cout << numDecodings("1223") << endl;
//    cout << _decode("1223") << endl;
//    cout << numDecodings1("1223") << endl;


//    cout << numDecodings("11") << endl;
    // 1 -> 1
    // 11 -> 2
    // 111 ->
    // 12121 -> 1 + 4 + ( 2 + 1 ) = 8
    // 111111 -> 1 + 5 + ( 3 + 2 + 1 ) + 1  = 13
    // 1111111 -> 1 + 6 + ( 4 + 3 + 2 + 1 ) + ( 2 ) = 21
//    cout << numDecodings("1111111") << endl;
//    cout << numDecodings1("111111") << endl;
//    cout << numDecodings("12") << endl;
//    cout << numDecodings("") << endl;
//    cout << numDecodings("7") << endl;
//    cout << numDecodings("71") << endl;
//    cout << numDecodings("712") << endl;
//    cout << numDecodings("7222") << endl;
}

#pragma mark - run

void Level8::Run()
{
    testNumDecodings();
}
//
//  Level3.cpp
//  XProject
//
//  Created by Roye Li on 7/30/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Level3.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode* head = new ListNode(0);
    ListNode* headIter = head;
    ListNode* it1 = l1;
    ListNode* it2 = l2;
    
    while( it1 != nullptr || it2 != nullptr )
    {
        if( it1 != nullptr && it2 != nullptr )
        {
            if( it1->val < it2->val )
            {
                headIter->next = it1;
                it1 = it1->next;
            }
            else
            {
                headIter->next = it2;
                it2 = it2->next;
            }
            
            headIter = headIter->next;
        }
        else if( it1 != nullptr )
        {
            headIter->next = it1;
            break;
        }
        else if( it2 != nullptr )
        {
            headIter->next = it2;
            break;
        }
    }
    
    return head->next;
}

#pragma mark - generateParenthesis

struct ParenthesisStruct
{
public:
    string current; // Current string
    int left;   // Left (
    int used;   // Used (
    
    ParenthesisStruct( string c, int l, int u ) : current( c ), left( l ), used( u ) {}
};

//Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
//
//For example, given n = 3, a solution set is:
//
//"((()))", "(()())", "(())()", "()(())", "()()()"
vector<string> generateParenthesis(int n)
{
    vector<string> g;
    
    vector<ParenthesisStruct> stack;
    
    stack.push_back({"", n, 0 });
    
    while( stack.size() != 0 )
    {
        ParenthesisStruct p = stack.back();
        stack.pop_back();
        
        if( p.left > 0 )
        {
            stack.push_back( ParenthesisStruct( p.current + "(", p.left - 1, p.used + 1 ) );
        }

        if( p.used > 0 )
        {
            // we have something to complete
            p.current += ")";
            p.used--;
            
            if( p.left == 0 && p.used == 0 )
            {
                g.push_back( p.current );
            }
            else
            {
                stack.push_back( p );
            }
        }
    }
    
    return g;
}

void testGenerateParenthesis()
{
    vector<string> v = generateParenthesis(0);
    for( auto& s : v )
    {
        cout << s << ", ";
    }
}

#pragma mark - swapPairs

//Given a linked list, swap every two adjacent nodes and return its head.
//
//For example,
//Given 1->2->3->4, you should return the list as 2->1->4->3.
//
//Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
ListNode* swapPairs(ListNode* head)
{
    if( head == nullptr )
        return head;
    
    
    ListNode* c1 = head;
    ListNode* c2 = head->next;
    ListNode* previous = nullptr;

    ListNode* newHead = head->next == nullptr ? c1 : c2;
    
    while( c1 != nullptr && c2 != nullptr )
    {
        if( previous != nullptr )
            previous->next = c2;
        
        ListNode* tmp = c2->next;
        c2->next = c1;
        
        previous = c1;
        
        c1 = tmp;
        if( c1 != nullptr )
            c2 = c1->next;
        
    }
    
    if( previous != nullptr )
    {
        previous->next = c1;
    }
    
    return newHead;
}

void testSwapPairs()
{
    vector<int> v = { 1 };
    ListNode* head = new ListNode( 0 );
    ListNode* iter = head;
    for( auto i : v )
    {
        ListNode* listNode = new ListNode( i );
        iter->next = listNode;
        iter = iter->next;
    }
    
    iter = head->next;
    while( iter != nullptr )
    {
        cout << iter->val << endl;
        iter = iter->next;
    }
    
    cout << "new ===== " << endl;
    ListNode* newHead = swapPairs( head->next );
    while( newHead != nullptr )
    {
        cout << newHead->val << endl;
        newHead = newHead->next;
    }
}

#pragma mark - removeDuplicates

//Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
//
//Do not allocate extra space for another array, you must do this in place with constant memory.
//
//For example,
//Given input array nums = [1,1,2],
//
//Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.
int removeDuplicates(vector<int>& nums)
{
    // Using the way O(N) implements it. http://blog.csdn.net/fightforyourdream/article/details/12719683
    
    // The idea is use i always point to unqiue index in the array, and let j to move from (1..n) in array V[N].
    // If V[i] == V[j] then, i don't move and j continue move, if not equal then i+1 is the duplicate one or maybe is V[j], so V[i+1] = V[j].
    // When it's end, then the index of i is last elements, the array size is i + 1.
    int i = 0;
    int j = 1;
    while( j < nums.size() )
    {
        if( nums[i] != nums[j] )
        {
            i++;
            nums[i] = nums[j];
        }

        j++;
    }
    
    return nums.size() - ( j - i ) + 1; // which is i + 1
}

void testRemoveDuplicates()
{
    vector<int> v = {1,2,3,};
    int r = removeDuplicates(v);
    for( int i = 0; i < r; i++ )
    {
        cout << v[i] << ", ";
    }
    cout << endl;
}

#pragma mark - removeElement
//Given an array and a value, remove all instances of that value in place and return the new length.
//
//The order of elements can be changed. It doesn't matter what you leave beyond the new length.
int removeElement(vector<int>& nums, int val)
{
    // similar to quick sort
    if( nums.size() == 0 )
        return 0;
    
    int i = 0;
    int j = nums.size() - 1;
    
    while( nums[j] == val && j >= 0 )
    {
        j--;
    }
    
    while( i <= j )
    {
        
        if( nums[i] != val )
        {
            i++;
        }
        else
        {
            swap( nums[i], nums[j] );
            j--;
            i++;
            
            while( nums[j] == val && j >= 0 )
            {
                j--;
            }
        }
    }
    
    return j + 1;
}

#pragma mark - strStr
//Implement strStr().
//
//Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
int strStr(string haystack, string needle)
{
    if( needle.size() == 0 )
        return 0;
    
    int i = 0;
    int j = 0;
    for( ; i < haystack.size(); i++ )
    {
        if( j < needle.size() )
        {
            if( haystack[i] == needle[j] )
            {
                j++;
            }
            else
            {
                if( j > 0 )
                    i = i - j;
                j = 0;
            }
        }
        else
        {
            break;
        }
    }
    
    return j == needle.size() ? i - needle.size() : -1;
    
    // TODO : Use KMP implements it
    // http://blog.csdn.net/v_july_v/article/details/7041827
    // http://www.matrix67.com/blog/archives/115
}

void testStrStr()
{
    cout << strStr("aaa", "aa") << endl;
    cout << strStr("mississippi", "pi") << endl;
    cout << strStr("mississippi", "issip") << endl; // The case where at index 4, we should rescan.
    cout << strStr("", "") << endl;
    cout <<  strStr("a", "a") << endl;
}

#pragma mark - divide

int GetBitAtFromLeft( int input, int index )
{
    unsigned int shift = 0;
    int tmp = input;
    while( tmp != 0 )
    {
        tmp = tmp >> 1;
        shift++;
    }

    return ( (1 << (shift - index - 1) & input ) ) > 0 ? 1 : 0;
}

void TestGetBitAt()
{
    for( int i = 0; i < 5; i++ )
    {
        cout << GetBitAtFromLeft( 15, i ) << endl;
    }
}

//Divide two integers without using multiplication, division and mod operator.
//
//If it is overflow, return MAX_INT.
int divide(int dividend, int divisor)
{
    if( divisor == 0 || ( dividend == numeric_limits<int>::min() && divisor == -1 ) )
        return numeric_limits<int>::max();

    bool sign = ( dividend < 0 ) ^ ( divisor < 0 );
    
    // 们知道任何一个整数可以表示成以2的幂为底的一组基的线性组合，
    // 即num=a_0*2^0+a_1*2^1+a_2*2^2+...+a_n*2^n。基于以上这个公式以及左移一位相当于乘以2，我们先让除数左移直到大于被除数之前得到一个最大的基
    
    unsigned int divisorU = abs( divisor );
    unsigned int dividendU = abs( dividend );
    
    int digits = 0;
    while( divisorU < dividendU )
    {
        divisorU = divisorU << 1;
        digits++;
    }
    
    unsigned int result = 0;
    while ( digits >= 0 )
    {
        if( dividendU >= divisorU )
        {
            result |= 1 << digits;
            dividendU = dividendU - divisorU;
        }
        
        divisorU = divisorU >> 1;
        digits--;
    }
    
    return sign ? -result : result;
}

void testDivide()
{
    cout << divide(0, 1) << endl;

//    cout << divide(2147483647, 1) << endl;
//    cout << divide(-2147483648, -1) << endl;

    for( int i = 100; i > -100; i-- )
    {
        for( int j = 1; j < 10; j++ )
        {
            if( divide( i, j ) != i / j )
            {
                cout << divide(i, j) << "= " << i / j << endl;
            }
        }
    }
}

#pragma mark - nextPermutation
//Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
//
//If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
//
//The replacement must be in-place, do not allocate extra memory.
//
//Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
//1,2,3 → 1,3,2
//3,2,1 → 1,2,3
//1,1,5 → 1,5,1
void nextPermutation(vector<int>& nums)
{
    //    Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
    //    Find the largest index l greater than k such that a[k] < a[l].
    //    Swap the value of a[k] with that of a[l].
    //    Reverse the sequence from a[k + 1] up to and including the final element a[n].
    if( nums.size() < 2 )
        return;
    
    // Step 1
    int k = -1;
    for( int i = 0; i < nums.size() - 1; i++ )
    {
        if( nums[i] < nums[i+1] )
        {
            k = i;
        }
    }
    
    if( k == -1 )
    {
        // Couldn't find it.
        sort( nums.begin(), nums.end() );
        return ;
    }
    
    // Step 2
    int l = -1;
    for( int i = k + 1; i < nums.size(); i++ )
    {
        if( nums[k] < nums[i] )
        {
            l = i;
        }
    }

    if( l == -1 )
    {
        cout << "Wrong !!!" << endl;
        return ;
    }
    
    // Step 3
    swap( nums[k], nums[l] );
    
    // Step 4
    sort( nums.begin() + k + 1, nums.end() );
}

void testNextPermutation()
{
    vector<vector<int>> allTestCases =
    {
        {3, 2, 1},
        {1, 2, 3, 4},
        {1},
        {1, 2},
        {1, 1, 5}
    };
    
    for( auto& nums : allTestCases )
    {
        nextPermutation( nums );
        
        for( auto i : nums )
        {
            cout << i << " ";
        }
        cout << endl;
    }
}

#pragma mark - 
//Given a sorted array of integers, find the starting and ending position of a given target value.
//
//Your algorithm's runtime complexity must be in the order of O(log n).
//
//If the target is not found in the array, return [-1, -1].
//
//For example,
//Given [5, 7, 7, 8, 8, 10] and target value 8,
//return [3, 4].
vector<int> _searchRange(vector<int>& nums, int start, int end, int target);

vector<int> searchRange(vector<int>& nums, int target)
{
    if( nums.size() == 0 )
        return {-1, -1 };
    
    return _searchRange(nums, 0, nums.size() - 1, target);
}

// [Start, end]
vector<int> _searchRange(vector<int>& nums, int start, int end, int target)
{
    if( start > end )
    {
        return {-1, -1};
    }
    
    if( start == end )
    {
        if( nums[start] == target )
            return {start, start};
        else
            return {-1, -1};
    }
    
    int mid = ( end - start ) / 2 + start;
    if( nums[mid] < target )
    {
        return _searchRange(nums, mid+1, end, target);
    }
    else if( nums[mid] > target )
    {
        return _searchRange(nums, start, mid-1, target);
    }
    else
    {
        // Equal, need to merge.
        vector<int> range1 = _searchRange(nums, start, mid, target);
        vector<int> range2 = _searchRange(nums, mid + 1, end, target);
        
        if( range2[0] == -1 )
        {
            return range1;
        }
        else
        {
            return {range1.front(), range2.back()};
        }
    }
}

void testSearchRange()
{
    vector<vector<int>> num2s =
    {
        {5, 7, 7, 8, 8, 10},
        {},
        {8},
        {8, 8},
        {1, 8, 8},
        {1, 8, 8, 9 },
        {1, 8, 8, 8 },
        {1, 8, 8, 8, 8},
        {1, 8, 8, 8, 8, 9}
    };
    
    for( auto& nums : num2s )
    {
        auto range = searchRange(nums, 8);
        cout << "{ ";
        for( auto& val : range )
        {
            cout << val << ", ";
        }
        cout << " }" << endl;
    }
}

#pragma mark - searchInsert

//Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
//
//You may assume no duplicates in the array.
//
//Here are few examples.
//[1,3,5,6], 5 → 2
//[1,3,5,6], 2 → 1
//[1,3,5,6], 7 → 4
//[1,3,5,6], 0 → 0
int searchInsert(vector<int>& nums, int target)
{
    if( nums.size() == 0 )
        return 0;

    int start = 0;
    int end = nums.size() - 1;
    
    while( end - start > 1 )
    {
        int mid = start + ( end - start ) / 2;
        int c = nums[mid];
        if( c == target )
        {
            return mid;
        }
        else if( c < target )
        {
            start = mid;
        }
        else
        {
            end = mid;
        }
    }
    
    vector<int> v;
    if( end - start == 0 )
    {
        v = {nums[start], target };
    }
    else
    {
        v = {nums[start], nums[end], target};
    }
    
    sort( v.begin(), v.end() );
    for( int i = 0; i < v.size(); i++ )
    {
        if( v[i] == target )
            return i + start;
    }
    
    return -1;
}

void testSearchInsert()
{
    vector<pair<vector<int>, int>> num2s =
    {
        {{1,3,5,6}, 7},// → 4
        {{1,3,5,6}, 2},// → 1
        {{1,3,5,6}, 5},// → 2
        {{1,3,5,6}, 0}// → 0
    };
    
    for( auto& p : num2s )
    {
        auto pos = searchInsert(p.first, p.second);
        cout << pos << endl;
    }
}

#pragma mark - isValidSudoku

//Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
//
//The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
//
//
//A partially filled sudoku which is valid.
//
//Note:
//A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.
bool isValidSudoku(vector<vector<char>>& board)
{
    if( board.size() != 9 && board[0].size() != 9 )
        return false;
    
    vector<set<char>> row(9);
    vector<set<char>> col(9);
    vector<set<char>> cub(9);
    
    for( int i = 0; i < 9; i++ )
    {
        for( int j = 0; j < 9; j++ )
        {
            char c = board[i][j];
            if( c != '.' )
            {
                // check row
                if( row[i].find( c ) == row[i].end() )
                {
                    row[i].insert(c);
                }
                else
                {
                    return false;
                }
                
                // check row
                if( col[j].find( c ) == col[j].end() )
                {
                    col[j].insert(c);
                }
                else
                {
                    return false;
                }
                
                // check cub
                int cubIdx = ( i / 3 ) * 3 + j / 3;
                if( cub[cubIdx].find( c ) == cub[cubIdx].end() )
                {
                    cub[cubIdx].insert(c);
                }
                else
                {
                    return false;
                }
            }
        }
    }

    return true;
}

void testVerifySudoku()
{
    vector<string> t = {".87654321","2........","3........","4........","5........","6........","7........","8........","9........"};
    vector<vector<char>> board(9, vector<char>(9) );
    for( int i = 0; i < t.size(); i++ )
    {
        for( int j = 0; j < t[i].length(); j++ )
        {
            board[i][j] = t[i][j];
        }
    }
    
    for( int i = 0; i < 9; i++ )
    {
        for( int j = 0; j < 9; j++ )
        {
            cout << board[i][j] << " ";
        }
        
        cout << endl;
    }
    
    cout << ( isValidSudoku( board ) ? "true" : "false" ) << endl;
}

#pragma mark - countAndSay

//The count-and-say sequence is the sequence of integers beginning as follows:
//1, 11, 21, 1211, 111221, ...
//
//1 is read off as "one 1" or 11.
//11 is read off as "two 1s" or 21.
//21 is read off as "one 2, then one 1" or 1211.
//Given an integer n, generate the nth sequence.
//
//Note: The sequence of integers will be represented as a string.
string countAndSay(int n)
{
    if( n <= 0 )
        return "";
    
    string previous = "1";
    if( n == 1 )
        return previous;
    
    string current;
    while( n-- > 1 )
    {
        for( int i = 0; i < previous.length(); i++ )
        {
            int repeat = 1;
            while( i + 1 < previous.length() && previous[i] == previous[i+1] )
            {
                i++;
                repeat++;
            }
            
            current += to_string( repeat );
            current += previous[i];
        }
        
        previous = current;
        current = "";
    }
    
    return previous;
}

void testCountAndSay()
{
    for( int i = 0; i < 10; i++ )
    {
        cout << countAndSay(i) << endl;
    }
}

#pragma mark - run
void Level3::Run()
{
    testCountAndSay();
}
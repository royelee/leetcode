//
//  Level4.cpp
//  XProject
//
//  Created by Roye Li on 8/30/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Level4.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <set>

using namespace std;

#pragma mark - multiply

string multiplySingle( string num, int d )
{
    if( d < 0 || d >= 10 )
        return "error";
    
    if( d == 0 )
        return "0";
    
    string s;
    
    int passDig = 0;
    for( int i = num.size() - 1; i >= 0; i-- )
    {
        int c = num[i] - '0';
        int sum = d * c + passDig;
        passDig = sum / 10;
        char g = '0' + sum % 10;
        
        s.insert(s.begin(), g);
    }
    
    if( passDig != 0 )
    {
        s.insert(s.begin(), '0' + passDig );
    }
    
    return s;
}

string strAdd( string num1, string num2 )
{
    if( num1.size() < num2.size() )
    {
        swap( num1 , num2 );
    }
    
    string output;
    
    int addOn = 0;
    
    int i1 = num1.size() - 1;
    int i2 = num2.size() - 1;
    while( i1 >= 0 && i2 >= 0 )
    {
        int n1 = num1[i1] - '0';
        int n2 = num2[i2] - '0';
        
        int sum = n1 + n2 + addOn;
        addOn = sum / 10;
        output.insert( output.begin(), '0' + sum % 10 );
        
        i1--;
        i2--;
    }
    
    while( i1 >= 0 )
    {
        int n1 = num1[i1] - '0';
        int sum = n1 + addOn;
        addOn = sum / 10;
        output.insert( output.begin(), '0' + sum % 10 );
        
        i1--;
    }
    
    if( addOn > 0 )
    {
        output.insert( output.begin(), '0' + addOn );
    }
    
    return output;
}

//Given two numbers represented as strings, return multiplication of the numbers as a string.
//
//Note: The numbers can be arbitrarily large and are non-negative.
string multiply(string num1, string num2)
{
    int neg = 1;
    if( num1.size() > 0 && num1.front() == '-' )
    {
        num1.erase(num1.begin());
        neg *= -1;
    }
    
    if( num2.size() > 0 && num2.front() == '-' )
    {
        num2.erase(num2.begin());
        neg *= -1;
    }
    
    if( num1.size() < num2.size() )
        swap( num1, num2 );
    
    string output;
    if( num1.size() == 0 && num2.size() == 0 )
        return output;
    
    int shift = 0;
    for( int i = num2.size() -1; i >= 0; i--, shift++ )
    {
        int d = (int)(num2[i] - '0');
        string m = multiplySingle( num1, d );
        
        for( int j = 0; j < shift; j++ )
            m.push_back('0');
        
        output = strAdd( output, m );
    }
    
    if( neg < 0 )
        output.insert( output.begin(), '-' );
    
    return output;
}

void testMultiplySingle()
{
    cout << multiplySingle("100", 0) << endl;
    cout << multiplySingle("1", 1) << endl;
    cout << multiplySingle("10", 1) << endl;
    cout << multiplySingle("20", 2) << endl;
    cout << multiplySingle("50", 2) << endl;
    cout << multiplySingle("49", 2) << endl;
    cout << multiplySingle("32", 9) << endl;
    cout << multiplySingle("11", 9) << endl;
}

void testStrAdd()
{
    cout << strAdd("", "") << endl;
    cout << strAdd("0", "") << endl;
    cout << strAdd("1", "") << endl;
    cout << strAdd("1", "0") << endl;
    cout << strAdd("1", "1") << endl;
    cout << strAdd("5", "5") << endl;
    cout << strAdd("11", "5") << endl;
    cout << strAdd("11", "11") << endl;
    cout << strAdd("99", "11") << endl;
    cout << strAdd("99", "0") << endl;
}

void testMultiply()
{
    cout << multiply("-", "-") << endl;
    cout << multiply("-", "") << endl;
    cout << multiply("", "") << endl;
    cout << multiply("0", "0") << endl;
    cout << multiply("0", "1") << endl;
    cout << multiply("1", "1") << endl;
    cout << multiply("2", "2") << endl;
    cout << multiply("2", "8") << endl;
    cout << multiply("2", "16") << endl;
    cout << multiply("12", "12") << endl;
    cout << multiply("12", "-12") << endl;
    cout << multiply("-12", "-12") << endl;

}

#pragma mark - Permutations

//Given a collection of numbers, return all possible permutations.
//
//For example,
//[1,2,3] have the following permutations:
//[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
bool nextP( vector<int>& v )
{
    // 1. find in biggest a[i] < a[i+1], if can't then it's done.
    // 2. find bigest j from i+1 which a[j] > a[i].
    // 3. swap a[j], a[i]
    // 4. reverse i + 1..N in a[N].

    int k = -1;
    for( int i = 0; i < v.size() - 1; i++ )
    {
        if( v[i] < v[i + 1] )
        {
            k = i;
        }
    }
    
    if( k == -1 )
        return false;
    
    int l = k + 1;
    for( int i = l; i < v.size(); i++ )
    {
        if( v[i] > v[k] )
        {
            l = i;
        }
    }
    
    swap( v[k], v[l] );
    
    // reverse k + 1 ... v.size()
    int i = k + 1;
    int j = v.size() - 1;
    while( i < j )
    {
        swap( v[i], v[j] );
        i++;
        j--;
    }
    
    return true;
}

vector<vector<int>> permute(vector<int>& nums)
{
    vector<vector<int>> rtn;
    
    while( true )
    {
        vector<int> tmp;
        for( auto& i : nums )
        {
            tmp.push_back( i );
        }
        
        rtn.push_back( tmp );
        
        if( !nextP( nums ) )
            break;
    }
    
    return rtn;
}

void permuteGenerating(vector<vector<int>>& result, vector<int>& nums, int i ) {
    
    if (i == nums.size()-1) {
        result.push_back(nums);
    } else {
        for (int j = i; j < nums.size(); j++) {
            // swap i and j
            swap(nums[i], nums[j]);
            
            permuteGenerating(result, nums, i + 1 );
            
            // swap i and j back
            swap(nums[i], nums[j]);
        }
    }
}

vector<vector<int>> permute1(vector<int>& nums)
{
    vector<vector<int>> result;
    permuteGenerating(result, nums, 0);
    return result;
}

void testPermute()
{
    vector<int> v = { 1, 2, 3 };
    auto r = permute1( v );
    
    for( const auto& array : r )
    {
        for( auto value : array )
        {
            cout << value << " ";
        }
        
        cout << endl;
    }
}

#pragma mark - permuteUnique
//Given a collection of numbers that might contain duplicates, return all possible unique permutations.
//
//For example,
//[1,1,2] have the following unique permutations:
//[1,1,2], [1,2,1], and [2,1,1].
vector<vector<int>> permuteUnique(vector<int>& nums)
{
    vector<vector<int>> rtn;
    
    sort( nums.begin(), nums.end() );
    
    while( true )
    {
        vector<int> tmp;
        for( auto& i : nums )
        {
            tmp.push_back( i );
        }
        
        rtn.push_back( tmp );
        
        if( !nextP( nums ) )
            break;
    }
    
    return rtn;
}

void permuteUnique()
{
    vector<int> v = { 0, 0, 1 };
    auto r = permuteUnique( v );
    
    for( const auto& array : r )
    {
        for( auto value : array )
        {
            cout << value << " ";
        }
        
        cout << endl;
    }
}

#pragma mark - run
void Level4::Run()
{
    testPermute();
}
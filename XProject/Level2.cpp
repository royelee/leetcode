//
//  Level2.cpp
//  XProject
//
//  Created by Roye Li on 7/6/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Level2.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

#pragma mark - intToRoman

string intToRoman(int num)
{
    if( num >= 1 && num <= 3999 )
    {
        pair<string, int> buckets[] =
        {
            {"I", 1},
            {"IV", 4},
            {"V", 5},
            {"IX", 9},
            {"X", 10},
            {"XL", 40},
            {"L", 50},
            {"XC", 90},
            {"C", 100},
            {"CD", 400},
            {"D", 500},
            {"CM", 900},
            {"M", 1000},
            {"", numeric_limits<int>::max()}
        };
        
        stringstream buf;
        while( num > 0 )
        {
            for( int i = 0; i < sizeof(buckets) / sizeof(buckets[0]); i++ )
            {
                if( num >= buckets[i].second &&  num < buckets[i+1].second )
                {
                    buf << buckets[i].first;
                    num -= buckets[i].second;
                    
                    
                    break;
                }
            }
        }
        
        return buf.str();
    }
    else
    {
        return "";
    }
}

void TestIntToRoman()
{
    pair<int, string> tests[] = {
        {40, "XL"}, // failed
        {1, "I"},
        {2, "II"},
        {3, "III"},
        {4, "IV"},
        {6, "VI"},
        {9, "IX"},
        {11, "XI"},
        {80, "LXXX"},
        {84, "LXXXIV"},
        {1800, "MDCCC"}
    };
    
    for( auto p : tests )
    {
        cout << p.first << "= " << intToRoman(p.first) << " " << " result = " << (intToRoman(p.first)  == p.second ) << endl;
    }

}

#pragma mark - run

void Level2::Run()
{
    TestIntToRoman();
}
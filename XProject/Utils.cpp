//
//  Utils.cpp
//  XProject
//
//  Created by Roye Li on 11/28/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include "Utils.h"

unsigned int factorial(unsigned int n)
{
    unsigned int ret = 1;
    for(unsigned int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}
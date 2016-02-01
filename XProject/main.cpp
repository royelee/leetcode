//
//  main.cpp
//  XProject
//
//  Created by Roye Li on 6/17/15.
//  Copyright (c) 2015 Roye Li. All rights reserved.
//

#include <iostream>
#include "Level.h"

template <typename T>
void runLevel() {
    std::unique_ptr<ILevel> level( new T );
    level->Run();
}

int main(int argc, const char * argv[]) {
    runLevel<Level11>();
    return 0;
}


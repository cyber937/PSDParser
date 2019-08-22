//
//  PSDColorMode.hpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/17/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#ifndef PSDColorMode_hpp
#define PSDColorMode_hpp

#include <stdio.h>
#include "Utilities.hpp"

class PSDColorMode {
    char length[4];
    
public:
    
    int getLength();
    
    void printData();
};

#endif /* PSDColorMode_hpp */

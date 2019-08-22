//
//  Utilities.cpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/17/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include "Utilities.hpp"

int IntFromBytes(const char *bytes, int len) {
    
    int intValue = 0;
    unsigned u[len];
    
    for (int i = 0; i < len; i++) {
        u[i] = (unsigned char)bytes[i];
        intValue |= u[i] << ((len - 1) -i) * 8;
    }
    
    return intValue;
}

int SignedIntFromBytes(const char *bytes, int len) {
    
    int intValue = 0;
    unsigned u[len];
    
    for (int i = 0; i < len; i++) {
        u[i] = (signed char)bytes[i];
        intValue |= u[i] << ((len - 1) -i) * 8;
    }
    
    return intValue;
}

//
//  PSDColorMode.cpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/17/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include "PSDColorMode.hpp"


int PSDColorMode::getLength(void) {
    return IntFromBytes(length, 4);
}

void PSDColorMode::printData(void) {
    printf("\n--- Color Mode Data Section  ---\n");
    printf("Data Length ... %i\n", getLength());
    }

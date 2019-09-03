//
//  PSDColorMode.hpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/17/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#ifndef PSDColorMode_hpp
#define PSDColorMode_hpp

#include <fstream>
#include <stdio.h>

using namespace std;

class PSDColorMode {
    
private:
    int _length;
    
public:
    int length();
    
    void load(ifstream& inf);
    
    void printData();
};

#endif /* PSDColorMode_hpp */

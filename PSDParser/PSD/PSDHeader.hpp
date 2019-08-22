//
//  PDSHeader.hpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/16/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#ifndef PDSHeader_hpp
#define PDSHeader_hpp

#include <stdio.h>
#include <string>
#include "Utilities.hpp"

using namespace std;

class PSDHeader {
    char sign[4];
    char version[2];
    char reserved[6];
    char channel[2];
    char height[4];
    char width[4];
    char depth[2];
    char colorMode[2];
    
public:
    
    std::string getSign();
    
    int getVersion();
    
    int getChannel();
    
    int getHeight();
    
    int getWidth();
    
    int getDepth();
    
    int getColorMode();
    
    void printData();
};

#endif /* PDSHeader_hpp */

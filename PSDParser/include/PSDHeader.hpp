//
//  PDSHeader.hpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/16/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#ifndef PDSHeader_hpp
#define PDSHeader_hpp

#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

class PSDHeader {
    
private:
    
    string _sign;
    int _version;
    int _reserved;
    int _channel;
    int _height;
    int _width;
    int _depth;
    int _colorMode;
    
public:
    
    string sign();
    
    int version();
    
    int channel();
    
    int height();
    
    int width();
    
    int depth();
    
    int colorMode();
    
    void load(ifstream& inf, int& hight, int& width);
    
    void printData();
};

#endif /* PDSHeader_hpp */

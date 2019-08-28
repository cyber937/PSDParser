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
    
    string _sign; //4
    int _version; //2
    int _reserved; //6
    int _channel; //2
    int _height; //4
    int _width;  //4
    int _depth; //2
    int _colorMode; //2
    
public:
    
    string sign();
    
    int version();
    
    int channel();
    
    int height();
    
    int width();
    
    int depth();
    
    int colorMode();
    
    void load(ifstream& inf);
    
    void printData();
};

#endif /* PDSHeader_hpp */

//
//  PDSHeader.cpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/16/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include "PSDHeader.hpp"
#include "Utilities.hpp"


string PSDHeader::sign() {
    return _sign;
}

int PSDHeader::version() {
    return _version;
}

int PSDHeader::channel() {
    return _channel;
}

int PSDHeader::height() {
    return _height;
}

int PSDHeader::width() {
    return _width;
}

int PSDHeader::depth() {
    return _depth;
}

int PSDHeader::colorMode() {
    return _colorMode;
}

void PSDHeader::load(ifstream& inf) {
    
    inf.read(&_sign[0], 4);
    
    _version = IntFromBinary(inf, 2);

    _reserved = IntFromBinary(inf, 6);
    
    _channel = IntFromBinary(inf, 2);
    
    _height =IntFromBinary(inf, 4);
    
    _width = IntFromBinary(inf, 4);
    
    _depth = IntFromBinary(inf, 2);
    
    _colorMode = IntFromBinary(inf, 2);
    
}

void PSDHeader::printData() {
    printf("\n--- File Header Section  ---\n");
    printf("Signature ... %s\n", sign().c_str());
    printf("Version ... %i\n", version());
    printf("Number of Channel ... %i\n", channel());
    printf("Height ... %i\n", height());
    printf("Width ... %i\n", width());
    printf("Depth ... %i\n", depth());
    printf("Color Mode ... %i\n", colorMode());
}

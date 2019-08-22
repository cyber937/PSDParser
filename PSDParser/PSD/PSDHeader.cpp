//
//  PDSHeader.cpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/16/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include "PSDHeader.hpp"

string PSDHeader::getSign() {
    return PSDHeader::sign;
}

int PSDHeader::getVersion() {
    return IntFromBytes(version, 2);
}

int PSDHeader::getChannel() {
    return IntFromBytes(channel, 2);
}

int PSDHeader::getHeight() {
    return IntFromBytes(height, 4);
}

int PSDHeader::getWidth() {
    return IntFromBytes(width, 4);
}

int PSDHeader::getDepth() {
    return IntFromBytes(depth, 2);
}

int PSDHeader::getColorMode() {
    return IntFromBytes(colorMode, 2);
}

void PSDHeader::printData() {
    printf("\n--- File Header Section  ---\n");
    printf("Signature ... %s\n", getSign().c_str());
    printf("Version ... %i\n", getVersion());
    printf("Number of Channel ... %i\n", getChannel());
    printf("Height ... %i\n", getHeight());
    printf("Width ... %i\n", getWidth());
    printf("Depth ... %i\n", getDepth());
    printf("Color Mode ... %i\n", getColorMode());
}

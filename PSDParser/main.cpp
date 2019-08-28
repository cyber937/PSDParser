//
//  main.cpp
//  PSDParser
//
//  Created by Kiyoshi Nagahama on 8/13/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "Utilities.hpp"
#include "PSDHeader.hpp"
#include "PSDColorMode.hpp"
#include "PSDImgRes.hpp"
#include "PSLayer.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    ifstream file;
    PSDHeader psdHeader;
    PSDColorMode psdColorMode;
    
    //file.open("/Users/kiyoshi/Desktop/PSVR_IMMERSED_FNAF_KEYART_sRGB_COMP_LAYERED_004.psb", ios::binary | ios::in);
    
    //file.open("/Users/kiyoshi/Desktop/test.psd", ios::binary | ios::in);
    
    file.open("/Users/kiyoshi/Desktop/Untitled-1.psd", ios::binary | ios::in);
    
    // Header
    psdHeader.load(file);
    psdHeader.printData();

    // Color Mode
    psdColorMode.load(file);
    psdColorMode.printData();
    
    printf("Current Position ... %i", int(file.tellg()));
    
    PSDImgResPerser psdImgResPerser;
    psdImgResPerser.startParse(file);
    
    printf("\nCurrent Positiong ... %i\n\n", int(file.tellg()));
    
    PSDLayerParser psdLayerPasrse;
    psdLayerPasrse.startParse(file, psdHeader.version());
}

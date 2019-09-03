//
//  PSDParser.cpp
//  PSDParser
//
//  Created by Kiyoshi Nagahama on 8/30/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include "PSDParser.hpp"

#include "Utilities.hpp"
#include "PSDHeader.hpp"
#include "PSDColorMode.hpp"
#include "PSDImgRes.hpp"
#include "PSLayer.hpp"

string PSDParser::getJSONString(const char * filename) {
    
    ifstream file;
    file.open(filename, ios::binary | ios::in);
    
    // Header
    PSDHeader psdHeader;
    psdHeader.load(file);
    
    // Color Mode
    PSDColorMode psdColorMode;
    psdColorMode.load(file);
    
    // ImageRes
    PSDImgResPerser psdImgResPerser;
    psdImgResPerser.startParse(file);
    
    // Layers
    PSDLayerParser psdLayerPasrse;
    return psdLayerPasrse.getLayerJSON(file, psdHeader.version());
}

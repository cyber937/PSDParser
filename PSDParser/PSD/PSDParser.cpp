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
    
    string jsonStr;
    
    int height, width;
    string ICC_Profile, DPI;
    
    // Header
    PSDHeader psdHeader;
    psdHeader.load(file, height, width);
    
    // Color Mode
    PSDColorMode psdColorMode;
    psdColorMode.load(file);
    
    // ImageRes
    PSDImgResPerser psdImgResPerser;
    psdImgResPerser.startParse(file, ICC_Profile, DPI);
    
    printf("%s", jsonStr.c_str());
    
    // Layers
    PSDLayerParser psdLayerPasrse;
    psdLayerPasrse.getLayerJSON(file, psdHeader.version(), jsonStr);
    
    string result;
    
    result = "{\"height\":" + to_string(height) + ",\n";
    result = result + "\"width\":" + to_string(width) + ",\n";
    result = result + "\"DPI\":" + DPI + ",\n";
    if (!ICC_Profile.empty()) {
        result = result + "\"ICC Profile\": \"" + ICC_Profile + "\",\n";
    }
    result = result + jsonStr;
    
    return result;
}

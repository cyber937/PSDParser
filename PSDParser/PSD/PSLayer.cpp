//
//  PSLayer.cpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/22/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include "PSLayer.hpp"
#include "Utilities.hpp"

void LayerRect::load(ifstream& inf) {
    _top = IntFromBinary(inf, 4);
    _left = IntFromBinary(inf, 4);
    _bottom = IntFromBinary(inf, 4);
    _right = IntFromBinary(inf, 4);
}

int LayerRect::top() {
    return _top;
}

int LayerRect::left() {
    return _left;
}

int LayerRect::bottom() {
    return _bottom;
}

int LayerRect::right() {
    return _right;
}


int PSDLayer::process(vector<PSDLayer> layerList, int count, int level) {
    
    int positionOfList = count;
    
    while (positionOfList != layerList.size()) {
        PSDLayer childLayer = layerList[positionOfList];
        positionOfList ++;
        
        if (childLayer.type == 0) {
            this->children.insert(this->children.begin(), childLayer);
        } else if (childLayer.type == 1 || childLayer.type == 2) {
            this->name = childLayer.name;
            break;
        } else if (childLayer.type == 3) {
            positionOfList = childLayer.process(layerList, positionOfList, level + 1);
            this->children.insert(this->children.begin(), childLayer);
        }
    }
    
    return positionOfList;
    
}


void PSDLayerParser::startParse(ifstream& inf, int version) {
    
//// Layer Section
    
    int sizeOfBuffer = 4 * version;
    lengthSec = IntFromBinary(inf, sizeOfBuffer);

    printf("Section Length ... %i\n\n", lengthSec);
    
    //// Layer info

    lengthInfo = IntFromBinary(inf, sizeOfBuffer);
    
    printf("Info Length ... %i\n\n", lengthInfo);
    
    //// # of Layers
    
    numLayer = SignedIntFromBinary(inf, 2);
    
    if (numLayer < 0)
        numLayer = (numLayer * -1);

    printf("# Layer ... %i\n\n", numLayer);

    //// Layer Record;
    
    int folderSection = 0;
    int hiddenSection = 0;
    
    PSDLayer pasLayer;
    
    vector<PSDLayer> layers;
    
    for (int i = 1; i <= numLayer; i++) {
        
        PSDLayer psdLayer;
        
        // Rectangle
        
        LayerRect layerRect;
        layerRect.load(inf);
        
        // Number of Channel
        int bufNumberChannel_int = IntFromBinary(inf, 2);
        int channelInfoLen = (2 + 4 * version) * bufNumberChannel_int;
        int blendInfoLen = 4 + 4;
        int opaClipFlagFillerInfoLen = 1+1+1+1;
        inf.seekg(channelInfoLen + blendInfoLen + opaClipFlagFillerInfoLen, inf.cur);
        
        // Length Of Extra Data
        int bufLenExtraData_int = IntFromBinary(inf, 4);
        
        //// EndPointOfLayerRecord
        int endPointOfLayerRecord = bufLenExtraData_int + int(inf.tellg());
        
        //// Layer mask/adjustment layer data
        
        // Langth of Data
        int bufLenMask_int = IntFromBinary(inf, 4);
        inf.seekg(bufLenMask_int, inf.cur);
        
        //// Layer blending range data
        
        // Length of Data
        int bufLenBlen_int = IntFromBinary(inf, 4);
        inf.seekg(bufLenBlen_int, inf.cur);
        
        streampos curPos = inf.tellg();
        
        while (endPointOfLayerRecord != curPos) {
            
            // Name --- Pascal string
            int bufStr_int = IntFromBinary(inf, 1);
            bufStr_int ++;
            
            int bufStr_int_checker = bufStr_int / 4;
            
            if ((bufStr_int_checker * 4) < bufStr_int)
                bufStr_int = (bufStr_int_checker + 1) * 4;
            
            bufStr_int --;
            
            
            char * buffName = (char*) malloc(bufStr_int);
            inf.read(buffName, bufStr_int);
            printf("%i, Name ... %s\n", i, buffName);
            
            psdLayer.name = buffName;
            
            curPos = int(inf.tellg());
            
            while (endPointOfLayerRecord != curPos) {
                char * bufAddLayerSign = (char*) malloc(4);
                inf.read(bufAddLayerSign, 4);
                
                char * bufAddLayerKey = (char*) malloc(4);
                inf.read(bufAddLayerKey, 4);
                
                int addLayerDataLen = 4;
                
                
                
                if (strncmp(bufAddLayerKey, "LMsk", 4) == 0 ||
                    strncmp(bufAddLayerKey, "Lr16", 4) == 0 ||
                    strncmp(bufAddLayerKey, "Lr32", 4) == 0 ||
                    strncmp(bufAddLayerKey, "Layr", 4) == 0 ||
                    strncmp(bufAddLayerKey, "Mt16", 4) == 0 ||
                    strncmp(bufAddLayerKey, "Mt32", 4) == 0 ||
                    strncmp(bufAddLayerKey, "Mtrn", 4) == 0 ||
                    strncmp(bufAddLayerKey, "Alph", 4) == 0 ||
                    strncmp(bufAddLayerKey, "FMsk", 4) == 0 ||
                    strncmp(bufAddLayerKey, "lnk2", 4) == 0 ||
                    strncmp(bufAddLayerKey, "FEid", 4) == 0 ||
                    strncmp(bufAddLayerKey, "FXid", 4) == 0 ||
                    strncmp(bufAddLayerKey, "PxSD", 4) == 0) {
                    
                    addLayerDataLen += 4;
                }
                
                int addLayerData_int = IntFromBinary(inf, addLayerDataLen);
                
                if (strncmp(bufAddLayerKey, "lsct", 4) == 0) {
                    int sectionDividerSetting_int = IntFromBinary(inf, 4);
                    
                    psdLayer.type = sectionDividerSetting_int;
                    
                    if (sectionDividerSetting_int == 1 || sectionDividerSetting_int == 2) {
                        folderSection++;
                        printf("%i - Folder\n\n", folderSection);
                    } else if (sectionDividerSetting_int == 3) {
                        hiddenSection++;
                        printf("%i - Hidden\n\n", hiddenSection);
                    }
                    
                    curPos = (addLayerData_int - 4) + int(inf.tellg());
                    inf.seekg(curPos);
                } else {
                    curPos = addLayerData_int + int(inf.tellg());
                    inf.seekg(curPos);
                }
            }
            
            layers.push_back(psdLayer);
        }
    }
    
    PSDLayer root;
    
    root.process(layers, 0, 0);
    
    printf("Hidden Section%i\n", hiddenSection);
    
}

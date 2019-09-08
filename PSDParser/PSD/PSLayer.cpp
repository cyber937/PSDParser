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


void PSDLayer::makeJSON(string& jsonString, int level) {
    
    if (level == 0) {
        jsonString = jsonString + "{\"name\": \"root\",\n \"children\":\n";
        jsonString = jsonString + "[\n";
    }
    
    string pad1 = "";
    string pad2 = "     ";
    
    for (int p = 0; p < level; p++) {
        pad1 = pad1 + "     ";
        pad2 = pad2 + "     ";
    }
    
    for (int i = 0; i < this->children.size(); i++) {
        
        jsonString = jsonString + pad2 + "{\"name\" : " + "\"" + this->children[i].name.c_str() + "\",\n" ;
        
        if (this->children[i].children.size() == 0) {
            jsonString = jsonString + pad2 + "\"children\" : []\n";
        } else {
            jsonString = jsonString + pad2 + "\"children\" :[\n";
            int nextLevel = level + 1;
            this->children[i].makeJSON(jsonString, nextLevel);
            jsonString = jsonString + pad2 +"]\n";
        }
        
        if (i == this->children.size() - 1) {
            jsonString = jsonString + pad1 + "}\n";
        } else {
            jsonString = jsonString + pad1 + "},\n";
        }
        
    }
    
    if (level == 0) {
        jsonString = jsonString + "]}";
    }
    
}


string PSDLayerParser::getLayerJSON(ifstream& inf, int version) {
    
//// Layer Section
    
    int sizeOfBuffer = 4 * version;
    lengthSec = IntFromBinary(inf, sizeOfBuffer);

    //printf("Section Length ... %i\n\n", lengthSec);
    
    //// Layer info

    lengthInfo = IntFromBinary(inf, sizeOfBuffer);
    
    //printf("Info Length ... %i\n\n", lengthInfo);
    
    //// # of Layers
    
    numLayer = SignedIntFromBinary(inf, 2);
    
    if (numLayer < 0)
        numLayer = (numLayer * -1);

    //printf("# Layer ... %i\n\n", numLayer);

    //// Layer Record;
    
    int folderSection = 0;
    int hiddenSection = 0;
    
    PSDLayer pasLayer;
    
    vector<PSDLayer> layers;
    vector<string> fonts;
    
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

        while (endPointOfLayerRecord != inf.tellg()) {
            
            // Name --- Pascal string
            int bufStr_int = IntFromBinary(inf, 1);
            bufStr_int ++;
            
            int bufStr_int_checker = bufStr_int / 4;
            
            if ((bufStr_int_checker * 4) < bufStr_int)
                bufStr_int = (bufStr_int_checker + 1) * 4;
            
            bufStr_int --;
            
            string layerName(bufStr_int, ' ');
            inf.read(&layerName[0], bufStr_int);
            //printf("%i, Name ... %s\n", i, layerName.c_str());
            
            psdLayer.name = layerName;

            while (endPointOfLayerRecord != inf.tellg()) {
                
                string layerSign(4, ' ');
                inf.read(&layerSign[0], 4);
                
                string layerKey(4, ' ');
                inf.read(&layerKey[0], 4);
                
                int addLayerDataLen = 4;
                
                if (!layerKey.compare("LMsk") ||
                    !layerKey.compare("Lr16") ||
                    !layerKey.compare("Lr32") ||
                    !layerKey.compare("Layr") ||
                    !layerKey.compare("Mt16") ||
                    !layerKey.compare("Mt32") ||
                    !layerKey.compare("Mtrn") ||
                    !layerKey.compare("Alph") ||
                    !layerKey.compare("FMsk") ||
                    !layerKey.compare("lnk2") ||
                    !layerKey.compare("FEid") ||
                    !layerKey.compare("FXid") ||
                    !layerKey.compare("PxSD")) {
                    
                    addLayerDataLen += 4;
                }
                
                int addLayerData_int = IntFromBinary(inf, addLayerDataLen);
                
                // Layer Group Information
                
                if (!layerKey.compare("lsct")) {
                    int sectionDividerSetting_int = IntFromBinary(inf, 4);
                    
                    psdLayer.type = sectionDividerSetting_int;
                    
                    if (sectionDividerSetting_int == 1 || sectionDividerSetting_int == 2) {
                        folderSection++;
                        //printf("%i - Folder\n\n", folderSection);
                    } else if (sectionDividerSetting_int == 3) {
                        hiddenSection++;
                        //printf("%i - Hidden\n\n", hiddenSection);
                    }
                    inf.seekg(addLayerData_int - 4, inf.cur);
                } else if (!layerKey.compare("TySh")) {
                    
                    int lastPositionOfTysh = addLayerData_int + int(inf.tellg());
                    
                    char c;
                    while (inf.get(c)) {
                        
                        if (inf.tellg() == lastPositionOfTysh) {
                            break;
                        }
                        
                        if (c == 'F') {
                            string fontSet(6, ' ');
                            inf.read(&fontSet[0], 6);
                            if (!fontSet.compare("ontSet")) {
                                
                                inf.seekg(20, inf.cur);
                                
                                int fontSetStartPosition = int(inf.tellg());
                                int fontSetEndPosition = 0;
                                
                                while (inf.get(c)) {
                                    if (c == ')') {
                                        fontSetEndPosition = int(inf.tellg()) - 1;
                                        break;
                                    }
                                }
                                
                                int lengthOfFontSet = (fontSetEndPosition - fontSetStartPosition) / 2;
                                
                                inf.seekg(fontSetStartPosition);
                                
                                string fontStyle;
                                
                                for (int i = 0; i < lengthOfFontSet; i++) {
                                    char buffer[2];
                                    inf.read(buffer, 2);
                                    unsigned char result = buffer[0] << 4 | buffer[1];
                                    UnicodeString uni_str((UChar32)result);
                                    string str;
                                    uni_str.toUTF8String(str);
                                    fontStyle = fontStyle + str;
                                }
                                
                                bool hasFontStyle = false;
                                
                                for (int i = 0; i < fonts.size(); i++) {
                                    if (!fontStyle.compare(fonts[i])) {
                                        hasFontStyle = true;
                                    }
                                }
                                
                                if (!hasFontStyle) {
                                    fonts.push_back(fontStyle);
                                }
                            }
                        }
                    }
                } else {
                    inf.seekg(addLayerData_int, inf.cur);
                }
                

            }
            
            layers.push_back(psdLayer);
        }
    }
    
    PSDLayer root;
    root.name = "root";
    root.type = 3;
    
    root.process(layers, 0, 0);

    string jsonString;
    
    root.makeJSON(jsonString);
    
    jsonString = "{ \"layers\": \n" + jsonString;
    
    if (fonts.size() > 0) {
        jsonString = jsonString + ",\n\"fonts\" : [ ";
        for (int i = 0; i < fonts.size(); i++) {
            jsonString = jsonString + "\"" + fonts[i].c_str() + "\"";
            if (i < fonts.size() - 1) {
                jsonString = jsonString + ",";
            }
        }
        
        jsonString = jsonString + "]";
    }
    
    jsonString = jsonString + "}";
    
    return jsonString;
    
}

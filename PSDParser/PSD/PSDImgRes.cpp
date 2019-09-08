//
//  PSDImgRes.cpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/17/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include "PSDImgRes.hpp"
#include "Utilities.hpp"

string PSDImgResBlockHeder::sign() {
    return _sign;
}

int PSDImgResBlockHeder::ui() {
    
    return _ui;
}

void PSDImgResBlockHeder::load(ifstream& inf) {
    
    inf.read(&_sign[0], 4);
    
    _ui = IntFromBinary(inf, 2);
}

void PSDImgResPerser::startParse(ifstream& inf, string& ICC_Profile, string& DPI) {
    
    length = IntFromBinary(inf, 4);
    
    //printf("\n--- Image Resourses Section  ---\n");
    //printf("Data Length ... %i\n\n", length);
    
    int lastPosition = length + int(inf.tellg());
    
    //streampos pos = inf.tellg();
    
    while (lastPosition !=  inf.tellg()) {
        
        PSDImgResBlockHeder imgResBlockHeader;
        imgResBlockHeader.load(inf);

        //printf("UI ... %i\n", imgResBlockHeader.ui());
        
        int bufStr_int = IntFromBinary(inf, 1);
        
        if (bufStr_int != 0) {
            if (bufStr_int % 2 == 0)
                bufStr_int ++;
            
            char name[bufStr_int];
            inf.read(name, bufStr_int);
            //printf("Name ... %s\n", name);
            
        } else {
            inf.seekg(1, inf.cur);
        }
        
        int bufDataSize_int = IntFromBinary(inf, 4);
        if (bufDataSize_int % 2 != 0)
            bufDataSize_int ++;
        
        if (imgResBlockHeader.ui() == 1005) {
            streampos startPositionOfResourseBlock = inf.tellg();
            streampos lastPotisionOfResourseBlock = bufDataSize_int + startPositionOfResourseBlock;
            
            DPI = to_string(IntFromBinary(inf, 2));
            //jsonStr = jsonStr + "\"dpi\":" + "\"" + to_string(dpi) + "\",\n";
            
            //printf("DPI ... %i\n", dpi);
            
            inf.seekg(lastPotisionOfResourseBlock, inf.beg);
            
        } else if (imgResBlockHeader.ui() == 1039) {
            streampos startPositionOfResourseBlock = inf.tellg();
            streampos lastPotisionOfResourseBlock = bufDataSize_int + startPositionOfResourseBlock;
            
            char c;
            
            string profile;
            
            while (inf.get(c)) {
                if (c == 'd') {
                    string sign(3, ' ');
                    inf.read(&sign[0], 3);
                    if (!sign.compare("esc")) {
                        
                        int tagOffset = IntFromBinary(inf, 4);
                        
                        inf.seekg(int(startPositionOfResourseBlock) + tagOffset, inf.beg);
                        
                        int identifier = 4;
                        int reserved = 4;
                        
                        inf.seekg(identifier + reserved, inf.cur);
                        
                        int profileDescriptionCount = IntFromBinary(inf, 4);
                        
                        string profileDescription(profileDescriptionCount - 1, ' ');
                        inf.read(&profileDescription[0], profileDescriptionCount - 1);
                        
                        if (!profileDescription.empty()) {
                            ICC_Profile = profileDescription;
                            //jsonStr = jsonStr + "\"ICCProfile\" : " + "\"" + profileDescription + "\",\n";
                        }
                        
                        
                        
                        break;
                    }
                }
            }
            
            inf.seekg(lastPotisionOfResourseBlock, inf.beg);
            
        } else {
            
            inf.seekg(bufDataSize_int, inf.cur);
            
        }
    }
}

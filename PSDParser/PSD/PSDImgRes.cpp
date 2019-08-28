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

void PSDImgResPerser::startParse(ifstream &inf) {
    
    length = IntFromBinary(inf, 4);
    
    printf("\n--- Image Resourses Section  ---\n");
    printf("Data Length ... %i\n\n", length);
    
    int lastPosition = length + int(inf.tellg());
    
    streampos pos = inf.tellg();
    
    while (lastPosition !=  pos) {
        
        PSDImgResBlockHeder imgResBlockHeader;
        imgResBlockHeader.load(inf);

        printf("UI ... %i\n", imgResBlockHeader.ui());
        
        int bufStr_int = IntFromBinary(inf, 1);
        
        if (bufStr_int != 0) {
            if (bufStr_int % 2 == 0)
                bufStr_int ++;
            
            char name[bufStr_int];
            inf.read(name, bufStr_int);
            printf("Name ... %s\n", name);
            
        } else {
            inf.seekg(1, inf.cur);
        }
        
        int bufDataSize_int = IntFromBinary(inf, 4);
        if (bufDataSize_int % 2 != 0)
            bufDataSize_int ++;
        
        inf.seekg(bufDataSize_int, inf.cur);
        
        pos = inf.tellg();
    }
}

//
//  PSDImgRes.cpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/17/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include "PSDImgRes.hpp"

std::string PSDImgResBlockHeder::getSign() {
    return sign;
}

int PSDImgResBlockHeder::getUI() {
    return IntFromBytes(ui, 2);
}


void PSDImgResPerser::startParse(ifstream *file) {
    
    char buffer[4];
    
    file->read(buffer, 4);
    length = IntFromBytes(buffer, 4);
    
    printf("\n--- Image Resourses Section  ---\n");
    printf("Data Length ... %i\n\n", length);
    
    int lastPosition = length + int(file->tellg());
    
    int pos = int(file->tellg());
    
    while (lastPosition !=  pos) {
        
        char * buffSign = (char *)malloc(4);
        file->read(buffSign, 4);
        
        char * buffUI = (char *)malloc(2);
        file->read(buffUI, 2);
        int buffUI_int = IntFromBytes(buffUI, 2);

        //PSDImgResBlockHeder psdImgResBlockHeder;
        //file->read((char*)&psdImgResBlockHeder, sizeof(PSDImgResBlockHeder));
        printf("UI ... %i\n", buffUI_int);
        
        char bufStr;
        file->get(bufStr);
        int bufStr_int = int(bufStr);
        
        if (bufStr_int != 0) {
            if (bufStr_int % 2 == 0)
                bufStr_int ++;
            
            char name[bufStr_int];
            file->read(name, bufStr_int);
            printf("Name ... %s\n", name);
            
        } else {
            file->seekg(int(file->tellg()) + 1);
        }
        
        char bufDataSize[4];
        file->read(bufDataSize, 4);
        
        int bufDataSize_int = IntFromBytes(bufDataSize, 4);
        if (bufDataSize_int % 2 != 0)
            bufDataSize_int ++;
        
        file->seekg(int(file->tellg()) + bufDataSize_int);
        
        pos = int(file->tellg());
    }
}

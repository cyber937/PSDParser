//
//  PSDImgRes.hpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/17/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#ifndef PSDImgRes_hpp
#define PSDImgRes_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include "Utilities.hpp"

using namespace std;

class PSDImgResBlockHeder {
    char sign[4];
    char ui[2];
    
public:
    
    std::string getSign();
    
    int getUI();
};


class PSDImgResPerser {
    int length;
    
public:
    
    void startParse(ifstream *file);
    
};

#endif /* PSDImgRes_hpp */

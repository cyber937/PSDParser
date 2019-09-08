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

using namespace std;

class PSDImgResBlockHeder {
    
private:
    
    string _sign;
    int _ui;
    
public:
    
    void load(ifstream& inf);
    
    string sign();
    
    int ui();
};


class PSDImgResPerser {
    
    int length;
    
public:
    
    void startParse(ifstream& inf, string& ICC_Profile, string& DPI);
    
};

#endif /* PSDImgRes_hpp */

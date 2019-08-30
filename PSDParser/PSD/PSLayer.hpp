//
//  PSLayer.hpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/22/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#ifndef PSLayer_hpp
#define PSLayer_hpp

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

class LayerRect {
    int _top, _left, _bottom, _right;
    
public:
    
    void load(ifstream& inf);
    
    int top();
    
    int left();
    
    int bottom();
    
    int right();
};

enum PSDLayerType {
    
};

class PSDLayer {
    
public:
    string name;
    int type = 0;
    vector<PSDLayer> children;
    
    int process(vector<PSDLayer> layerList, int count, int level);
    
    //void makeJSON(string& jsonString);
    
    void makeJSON(string& jsonString, int level = 0);
};

class PSDLayerParser {
    
    int lengthSec, lengthInfo, numLayer;
    
public:
    
    void startParse(ifstream& file, int version);
    
};


#endif /* PSLayer_hpp */

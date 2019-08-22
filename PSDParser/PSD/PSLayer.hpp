//
//  PSLayer.hpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/22/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#ifndef PSLayer_hpp
#define PSLayer_hpp

#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "Utilities.hpp"

using namespace std;

class LayerRect {
    char _top[4];
    char _left[4];
    char _bottom[4];
    char _right[4];
    
public:
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
};

class PSDLayerParser {
    
    int lengthSec;
    int lengthInfo;
    int numLayer;
    
public:
    
    void startParse(ifstream *file, int version);
};


#endif /* PSLayer_hpp */

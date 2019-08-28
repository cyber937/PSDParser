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

using namespace std;

class LayerRect {
    int _top; //4
    int _left; //4
    int _bottom; //4
    int _right;  //4
    
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
};

class PSDLayerParser {
    
    int lengthSec;
    int lengthInfo;
    int numLayer;
    
public:
    
    void startParse(ifstream& file, int version);
};


#endif /* PSLayer_hpp */

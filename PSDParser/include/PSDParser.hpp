//
//  PSDParser.hpp
//  PSDParser
//
//  Created by Kiyoshi Nagahama on 8/30/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#ifndef PSDParser_hpp
#define PSDParser_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class PSDParser {
  
public:
    
    string getJSONString(const char * filename);
    
};

#endif /* PSDParser_hpp */

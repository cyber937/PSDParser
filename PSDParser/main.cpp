//
//  main.cpp
//  PSDParser
//
//  Created by Kiyoshi Nagahama on 8/13/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "PSDParser.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    PSDParser psdParser;
    
    cout << psdParser.getJSONString(argv[1]) << endl;
    
}

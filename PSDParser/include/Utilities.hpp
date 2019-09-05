//
//  Utilities.hpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/17/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#ifndef Utilities_hpp
#define Utilities_hpp

#include <fstream>
#include <stdio.h>
#include <string>

#include <unicode/unistr.h>

using namespace std;
using namespace icu;

int IntFromBytes(const char *bytes, int len);

int SignedIntFromBytes(const char *bytes, int len);

int IntFromBinary(ifstream& inf, int len);

int SignedIntFromBinary(ifstream& inf, int len);

string stringFromUnicode(ifstream& inf, int len);

#endif /* Utilities_hpp */

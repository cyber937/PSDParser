//
//  Utilities.cpp
//  DataParse_Practice
//
//  Created by Kiyoshi Nagahama on 8/17/19.
//  Copyright © 2019 Kiyoshi Nagahama. All rights reserved.
//

#include "Utilities.hpp"

int IntFromBytes(const char *bytes, int len) {
    
    int intValue = 0;
    unsigned u[len];
    
    for (int i = 0; i < len; i++) {
        u[i] = (unsigned char)bytes[i];
        intValue |= u[i] << ((len - 1) -i) * 8;
    }
    
    return intValue;
}

int SignedIntFromBytes(const char *bytes, int len) {
    
    int intValue = 0;
    unsigned u[len];
    
    for (int i = 0; i < len; i++) {
        u[i] = (signed char)bytes[i];
        intValue |= u[i] << ((len - 1) -i) * 8;
    }
    
    return intValue;
}

int IntFromBinary(ifstream& inf, int len) {
    char buffer[100];
    inf.read(buffer, len);
    return IntFromBytes(buffer, len);
}

int SignedIntFromBinary(ifstream& inf, int len) {
    char buffer[100];
    inf.read(buffer, len);
    return SignedIntFromBytes(buffer, len);
}

string stringFromUnicode(ifstream& inf, int len) {
    
    string uniString;
    
    for (int i = 0; i < len; i++) {
        char buffer[2];
        inf.read(buffer, 2);
        unsigned char result = buffer[0] << 4 | buffer[1];
        UnicodeString uni_str((UChar32)result);
        string str;
        uni_str.toUTF8String(str);
        uniString = uniString + str;
    }
    
    return uniString;
}

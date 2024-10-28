//
// Created by biscu on 23-10-2024.
//

#include "FileUtil.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <filesystem>
#include <fstream>

FileUtil::FileUtil() {}
FileUtil::~FileUtil() {}



void FileUtil::readFile(const std::string& file) {
    if (!std::filesystem::exists(file)) {
        std::cerr << "File not found!" << std::endl;
        return;
    }

    std::ifstream inFile(file);

    std::stringstream buffer;
    std::string line;

    while(std::getline(inFile, line)) {
        
    }

    inFile.close();
}

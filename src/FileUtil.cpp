//
// Created by biscu on 23-10-2024.
//

#include "FileUtil.h"

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
    }

    std::ifstream inFile(file);

    std::string text;
    while (getline (inFile, text)) {
        std::cout << text << "\n";
    }

    inFile.close();
}

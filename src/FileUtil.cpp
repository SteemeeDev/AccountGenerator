#include "FileUtil.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <filesystem>
#include <fstream>

void FileUtil::ReadFile(const std::string& path){
    std::ifstream iFile(path);
    if(!iFile.is_open()){
        std::cerr << "Could not open file: " << path << '\n';
        return;
    }

    std::stringstream linestream;
    std::string key, value, line;

    while(std::getline(iFile, line)){
        if(line.empty()) continue;

        linestream.clear();
        linestream << line;

        if(!std::getline(linestream, key, ':')){
            std::cerr << "Could not seperate key and value!\n";
            continue;
        }

        std::cout << "KEY: " << key;

        if(std::getline(linestream, value)){
            value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
        }

        std::cout << " | VALUE: " << value << '\n';

        m_unames[key] = value;
    }
}

void FileUtil::SaveUsername(const std::string& path, const char* uname){

}
void FileUtil::SavePassword(const std::string& path, const char* pword){

}

std::string FileUtil::GetUname(const std::string& origin){
    if(const auto it = m_unames.find(origin); it != m_unames.end()){
        return it->second;
    }

    std::cerr << "Could not find username at: " << origin << ". Returning empty string\n";
    return "";
}

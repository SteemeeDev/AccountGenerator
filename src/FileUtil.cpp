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
    std::string key, uname, pword, line;

    while(std::getline(iFile, line)){
        if(line.empty()) continue;

        linestream.clear();
        linestream.str(line);

        if(!std::getline(linestream, key, ':')){
            std::cerr << "Could not seperate key and value!\n";
            continue;
        }

        if(std::getline(linestream, uname, ':')){
            uname.erase(std::remove_if(uname.begin(), uname.end(), ::isspace), uname.end());
        }

        if(std::getline(linestream, pword)){
            pword.erase(std::remove_if(pword.begin(), pword.end(), ::isspace), pword.end());
        }

        m_sources[key] = {uname, pword};
    }
}

void FileUtil::SaveUsername(const std::string& path, const char* uname){

}
void FileUtil::SavePassword(const std::string& path, const char* pword){

}

std::string FileUtil::ShowUname(const std::string& source){
    if(const auto& it = m_sources.find(source); it != m_sources.end()){
        return it->second.first;
    }

    return "";
}

std::string FileUtil::ShowPasswd(const std::string& source){
    if(const auto& it = m_sources.find(source); it != m_sources.end()){
        return it->second.second;
    }

    return "";
}


std::vector<std::string> FileUtil::GetAccounts(){
    std::vector<std::string> accounts;
    for (const auto& i : m_sources){
        accounts.push_back(i.first);
    }

    return accounts;
}


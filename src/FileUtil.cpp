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

    m_path = path;

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

        for(char& i : key){
            i -= 1;
        }

        m_sources[key] = {uname, pword};
    }
}

void FileUtil::NewEntry(const std::string& source, const std::string& uname, std::string pword){
    std::ofstream oFile(m_path, std::ios::app);
    if(!oFile.is_open()){
        std::cerr << "Could not open output file: " << m_path << '\n';
        return;
    }

    std::string encryptedPword;
    std::string finalOutput(source + ":" + uname + ":");

    for(char& c : pword){
        encryptedPword += c += 1;
    }

    finalOutput += encryptedPword;

    std::cout << finalOutput;

    oFile << finalOutput;

    oFile.close();
}

std::string FileUtil::ShowUname(const std::string& source){
    if(const auto& it = m_sources.find(source); it != m_sources.end()){
        return it->second.first;
    }

    return "";
}

std::string FileUtil::ShowPasswd(const std::string& source){
    std::string original;

    if(const auto& it = m_sources.find(source); it != m_sources.end()){
        for(char& c : it->second.second){
            original += c -= 1;
        }

        return original;
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

std::string FileUtil::genRandomString(int length) {
    std::string final;
    srand(time(nullptr));
    for(int i = 0; i < length; i++) {
        char c = rand() % 255;
        final += c;
    }
    final.erase(std::remove_if(final.begin(), final.end(), ::isspace), final.end());
    return final;
}
#include "FileUtil.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <filesystem>
#include <fstream>

void FileUtil::ReadFile(){
    std::fstream File("Database");

    m_path = "Database";

    std::stringstream linestream;
    std::string key, uname, pword, line;

    while(std::getline(File, line)){
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

void FileUtil::NewEntry(const std::string& source, const std::string& uname, std::string pword){
    std::ofstream oFile(m_path, std::ios::app);
    if(!oFile.is_open()){
        std::cerr << "Could not open output file: " << m_path << '\n';
        return;
    }

    std::string encryptedPword;
    std::string finalOutput("\n" + source + ":" + uname + ":");

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

std::string FileUtil::ShowPasswd(const std::string& source, bool doDecrypt){
    std::string original;

    if(const auto& it = m_sources.find(source); it != m_sources.end()){
        if (doDecrypt) {
            for(char c : it->second.second){

                original += c -= 1;

            }

            return original;
        }else {
            std::cout << "Gaming";
            return it->second.second;
        }
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
        int temp = (rand() % 57)+33;
        if (temp == 58) {continue;}
        final += static_cast<char>(temp);
    }
    final.erase(std::remove_if(final.begin(), final.end(), ::isspace), final.end());
    return final;
}
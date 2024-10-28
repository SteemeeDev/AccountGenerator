//
// Created by biscu on 23-10-2024.
//

#ifndef FILEUTIL_H
#define FILEUTIL_H
#include <string>
#include <unordered_map>


class FileUtil {
public:
    FileUtil();
    ~FileUtil();

    void readFile(const std::string& file);
private:
    std::unordered_map<std::string, std::string> m_configs;
};



#endif //FILEUTIL_H

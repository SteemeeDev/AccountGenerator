//
// Created by biscu on 23-10-2024.
//

#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <string>
#include <unordered_map>
#include <vector>


class FileUtil {
public:
    FileUtil() = default;
    ~FileUtil() = default;

    void ReadFile();

    void NewEntry(const std::string& source, const std::string& uname, std::string pword);

    std::string ShowUname(const std::string& source);
    std::string ShowPasswd(const std::string& source, bool doDecrypt);

    std::vector<std::string> GetAccounts();

    std::string genRandomString(int length);
private:
    std::string m_path;

    std::unordered_map<std::string, std::pair<std::string, std::string>> m_sources;
};

#endif //FILEUTIL_H
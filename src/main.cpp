#include "Application.h"

#include "FileUtil.h"

#include <iostream>

// Main is the entry point and has to be an int. Return 0 of no error and usually -1 if an error
int main(){
    App::AppSpecs specs;
    specs.title = "Account Generator";
    specs.width = 400;
    specs.height = 400;

    FileUtil fu;
    fu.ReadFile(R"(C:\dev\cpp\AccountGenerator\src\Passwords.txt)");

    auto a = fu.GetAccounts();
    for(const auto & i : a){
        std::cout << "ACCOUNT DEST: " << i << '\n';
        std::cout << "ACCOUNT UNAME: " << fu.ShowUname(i) << '\n';
    }

    auto app = App::Application(specs);
    app.Loop();

    return 0;
}
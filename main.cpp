// weird linux shell ahh program lol :skull:

#include <iostream>
#include <list>
#include <string>
#include <windows.h>
#include <Lmcons.h>
#include <vector>
#include <filesystem>
#include <direct.h>
#include "commands.h"
#include <map>
#include <functional>

int main() {


    std::map<std::string, std::function<void(std::string)>> commands;

    commands["help"] = [](std::string args){ showHelp(); };
    commands["whoami"] = [](std::string args){ whoami(); };
    commands["ls"] = [](std::string args){ ls(args); };
    commands["exit"] = [](std::string args){ exit(0); };


    std::cout << "Welcome to Wsh 0.1!\nThis project is still an early prototype so report any bugs on my Github\nhttps://github.com/craft2guardian/Wsh\nEnjoy!\n";
    std::string input;

    while (true) {

        std::cout << getUsername() << "@" << getSanitizedHostname() << ":";
        std::getline(std::cin, input);
        if (input.empty()) {
            continue;
        }
        
        std::istringstream iss(input);
        std::string cmd;
        iss >> cmd;
        std::string args;
        std::getline(iss, args);
        if (!args.empty() && args[0] == ' ') args = args.substr(1);
        if (commands.find(cmd) != commands.end()) {
            commands[cmd](args);
        } else {
            std::cout << "wsh: " << cmd << ": command not found\n";
        }   
    }
}

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

int main() {
    std::string input;

    while (true) {

        std::cout << getUsername() << "@" << getOEMInfo() << ":";

        std::getline(std::cin, input);

        if (input == "help") showHelp();
        else if (input == "whoami") whoami();
        else if (input.substr(0, 2) == "ls") ls(input.length() > 3 ? input.substr(3) : "");
        else if (input == "exit") break;
        else std::cout << "wsh: " << input << ": " << "command not found\n";

    }
}
#include <iostream>
#include <filesystem>
#include "commands.h"
#include <windows.h>

namespace fs = std::filesystem;

std::string getSanitizedHostname() {
    char hostname[256];
    DWORD size = sizeof(hostname);
    if (!GetComputerNameA(hostname, &size)) return "UnknownHost";

    std::string host(hostname);

    // Cut after first hyphen to remove random gibberish
    size_t pos = host.find('-');
    if (pos != std::string::npos) host = host.substr(0, pos);


    return host;
}

void showHelp() {
    std::cout << "help, ls, whoami, cd, exit\n";
}



void whoami() {
    std::cout << getUsername() << std::endl;
}

void ls(const std::string& dir_path) {
    // Use current directory if nothing is passed
    std::string path = dir_path.empty() ? fs::current_path().string() : dir_path;

    // Check if path exists and is a directory BEFORE iterating
    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cout << "wsh: ls: Cannot access '" << path << "': No such directory\n";
        return;
    }

    // Iterate through directory safely
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << entry.path().filename().string() << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "wsh: ls: " << e.what() << std::endl;
    }
}

std::string getUsername() {
    char username[256];
    DWORD username_len = 256;
    if (GetUserNameA(username, &username_len)) return std::string(username);
    return "Unknown user";
}

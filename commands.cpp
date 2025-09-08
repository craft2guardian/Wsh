//commands.cpp

#include <iostream>
#include <filesystem>
#include "commands.h"
#include <windows.h>

namespace fs = std::filesystem;

bool isHidden(const std::filesystem::path& p) {
    DWORD attrs = GetFileAttributesW(p.wstring().c_str());
    if (attrs == INVALID_FILE_ATTRIBUTES) return false;
    return (attrs & FILE_ATTRIBUTE_HIDDEN);
}

std::string targetDir = "C:\\Users\\pc\\";

std::string getSanitizedHostname() {
    char hostname[256];
    DWORD size = sizeof(hostname);
    if (!GetComputerNameA(hostname, &size)) return "UnknownHost";

    std::string host(hostname);

    size_t pos = host.find('-');
    if (pos != std::string::npos) host = host.substr(0, pos);


    return host;
}




void showHelp() {
    std::cout << "help, ls, version, pwd, run, whoami, clear, cd, exit\n";
}

void cd(const std::string& arg) {

    std::string newPath = arg.empty() ? "C:\\Users\\pc" : arg;

    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        targetDir = newPath;
    }
    else {
        std::cout << "wsh: cd: " << arg << ": No such directory\n";
    }

}

void version() {
    std::cout << "Wsh version " << wshversion << std::endl;
}

void whoami() {
    std::cout << getUsername() << std::endl;
}

void ls(const std::string& dir_path) {
    std::string path = dir_path.empty() ? targetDir : dir_path;

    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cout << "wsh: ls: Cannot access '" << path << "': No such directory\n";
        return;
    }

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (!isHidden(entry.path())) {
                std::cout << entry.path().filename().string() << std::endl;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "wsh: ls: " << e.what() << std::endl;
    }
}

void pwd() {
    std::cout << targetDir << std::endl;
}

void run(const std::string& args) {

    if (args.empty()) {
        std::cout << "wsh: No program specified.";
        return;
    }

    std::filesystem::path filePath(args);

    if (!std::filesystem::exists(filePath)) {

        std::cout << "wsh: Specified program does not exist.\n";
        return;
    }

    int result = system(args.c_str());
    if (result != 0) {
        std::cout << "wsh: " << args << ": failed to run.";
    }

}

void clear() {

    system("cls");

}


std::string getUsername() {
    char username[256];
    DWORD username_len = 256;
    if (GetUserNameA(username, &username_len)) return std::string(username);
    return "Unknown user";
}

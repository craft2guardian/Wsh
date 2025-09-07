#include <iostream>
#include <filesystem>
#include "commands.h"
#include <windows.h>

namespace fs = std::filesystem;

std::string getOEMInfo() {
    HKEY hKey;
    char oemInfo[256];
    DWORD bufferSize = sizeof(oemInfo);

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueExA(hKey, "SystemManufacturer", NULL, NULL, (LPBYTE)oemInfo, &bufferSize) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return std::string(oemInfo);
        }
        RegCloseKey(hKey);
    }

    return "Unknown OEM Info";
}


void showHelp() {
    std::cout << "help, ls, whoami, cd, exit\n";
}

void whoami() {
    std::cout << getUsername() << std::endl;
}

void ls(std::string dir_path) {
    if (dir_path == "") dir_path = "C:\\";
    for (const auto&entry : fs::directory_iterator(dir_path)) {
        std::cout << entry.path().filename().string() << std::endl;
    }
}

std::string getUsername() {
    char username[256];
    DWORD username_len = 256;
    if (GetUserNameA(username, &username_len)) return std::string(username);
    return "Unknown user";
}
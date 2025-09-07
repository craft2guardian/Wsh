#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

void showHelp();
void whoami();
void uname();
void ls(std::string dir_path);
void cd(std::string dir_path);
void exitShell();

std::string getUsername();
std::string getOEMInfo();

#endif
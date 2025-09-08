//commands.h

extern std::string targetDir;


#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>

const std::string wshversion = "0.2";

void pwd();
void version();
void showHelp();
void whoami();
void uname();
void ls(const std::string& dir_path = "");
void exitShell();
void cd(const std::string& path);
void run(const std::string& args);
void clear();


std::string getUsername();
std::string getSanitizedHostname();

#endif

#pragma once

#include <filesystem>
#include <string>

// Defining OS dependant executable's absolute path retrieval
#ifdef _WIN32
    #include <io.h>
    #define getExecutablePath(buf, size) _fullpath((buf), _pgmptr, (size))
#else
    #include <unistd.h>
    #define getExecutablePath(buf, size) readlink("/proc/self/exe", (buf), (size))
#endif

std::string getFilePath(const std::string& fileName);
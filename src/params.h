#pragma once
#define LOOP_TIMES 10000

#include <iostream>
#include <fstream>
#include <sstream>

#if _WIN32
#include <direct.h> // _getcwd
#else
#include <unistd.h>
#endif

std::string readFile(const std::string_view& path) {
    std::ifstream input;
#if _WIN32
    char current_dir[256] = { 0 };
    _getcwd(current_dir, 255);
#endif
    input.open(path.data(), std::ios::in | std::ios::binary| std::ios::ate);
    if (input.is_open()) {
        int size = input.tellg();
        input.seekg(0, std::ios::beg);
        std::string ret;
        ret.resize(size, 0);
        input.read(ret.data(), size);
        input.close();
        return ret;
    }
    return "";
}

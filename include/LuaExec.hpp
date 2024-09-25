#pragma once

#include <string>

extern "C" {
#include "lua.h"
}

class LuaExec {
public:
    LuaExec();
    ~LuaExec();

    void executeFile(const std::string &path);
    void execute(const std::string &script);

private:
    lua_State *L;

    void pcall(int nargs = 0, int nresults = 0);
    std::string popString();
};

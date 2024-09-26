#pragma once

#include "LuaType.hpp"

extern "C" {
#include "lua.h"
}

class LuaExec {
public:
    LuaExec();
    ~LuaExec();

    void executeFile(const std::string &path);
    void execute(const std::string &script);
    void registerFunction(const std::string &name, lua_CFunction f);

private:
    lua_State *L;

    void pcall(int nargs = 0, int nresults = 0);
    LuaValue getValue(int index);
    LuaValue popValue();
    void pushValue(LuaValue value);
    std::string popString();
};

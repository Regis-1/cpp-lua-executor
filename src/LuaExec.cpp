#include "LuaExec.hpp"
#include <iostream>

extern "C" {
#include "lualib.h"
#include "lauxlib.h"
}

LuaExec::LuaExec() : L(luaL_newstate()) {
    luaL_openlibs(L);
}

LuaExec::~LuaExec() {
    lua_close(L);
}

void LuaExec::executeFile(const std::string &path) {
    if (luaL_loadfile(L, path.c_str())) {
        std::cerr << "Failed to prepare Lua script: "
            << popString() << std::endl;
        return;
    }
    pcall();
}

void LuaExec::execute(const std::string &script) {
    if (luaL_loadstring(L, script.c_str())) {
        std::cerr << "Failed to prepare Lua script: "
            << popString() << std::endl;
        return;
    }
    pcall();
}

void LuaExec::pcall(int nargs, int nresults) {
    if (lua_pcall(L, nargs, nresults, 0)) {
        std::cerr << "Failed to execute Lua code: "
            << popString() << std::endl;
    }
}

std::string LuaExec::popString() {
    std::string result {lua_tostring(L, -1)};
    lua_pop(L, 1);
    return result;
}

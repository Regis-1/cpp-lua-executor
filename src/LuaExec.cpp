#include "LuaExec.hpp"
#include "LuaType.hpp"
#include "lua.h"
#include <cmath>
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

void LuaExec::registerFunction(const std::string &name, lua_CFunction f) {
    lua_pushcfunction(L, f);
    lua_setglobal(L, name.c_str());
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

LuaValue LuaExec::getValue(int index) {
    switch (lua_type(L, index)) {
    case LUA_TNIL:
        return LuaNil::make();
    case LUA_TBOOLEAN:
        return LuaBoolean::make(lua_toboolean(L, index) == 1);
    case LUA_TNUMBER:
        return LuaNumber::make((double)lua_tonumber(L, index));
    case LUA_TSTRING:
        return LuaString::make(lua_tostring(L, index));
    default:
        return LuaNil::make();
    }
}

LuaValue LuaExec::popValue() {
    LuaValue result {getValue(-1)};
    lua_pop(L, 1);
    return result;
}

void LuaExec::pushValue(LuaValue value) {
    switch (getLuaType(value)) {
        case LuaType::nil:
            lua_pushnil(L);
            break;
        case LuaType::boolean:
            lua_pushboolean(L, std::get<LuaBoolean>(value).value ? 1 : 0);
            break;
        case LuaType::number:
            lua_pushnumber(L, std::get<LuaNumber>(value).value);
            break;
        case LuaType::string:
            lua_pushstring(L, std::get<LuaString>(value).value.c_str());
            break;
    }
}

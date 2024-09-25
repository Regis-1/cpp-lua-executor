#include <iostream>

#include "LuaExec.hpp"

int main(int argc, char *argv[]) {
    LuaExec luaExec;

    luaExec.execute("print('Hello from Lua')");
    std::cout << "Hello from C++" << std::endl;

    return 0;
}

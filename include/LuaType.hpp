#pragma once

#include <cstddef>
#include <string>
#include <variant>

enum class LuaType {
    nil,
    boolean,
    number,
    string
};

struct LuaNil final {
    const LuaType type {LuaType::nil};
    const std::nullptr_t value {nullptr};
    static LuaNil make() { return LuaNil(); }

private:
    LuaNil() = default;
};

struct LuaBoolean final {
    const LuaType type {LuaType::nil};
    const bool value;
    static LuaBoolean make(const bool value) { return LuaBoolean(value); }

private:
    LuaBoolean(const bool value) : value(value) {} 
};

struct LuaNumber final {
    const LuaType type {LuaType::number};
    const double value;
    static LuaNumber make(const double value) { return LuaNumber(value); }

private:
    LuaNumber(const double value) : value(value) {}
};

struct LuaString final {
    const LuaType type {LuaType::string};
    const std::string value;
    static LuaString make(const std::string value) { return LuaString(value); }

private:
    LuaString(const std::string value) : value(value) {}
};

using LuaValue = std::variant<LuaNil, LuaBoolean, LuaNumber, LuaString>;

inline LuaType getLuaType(const LuaValue &value) {
    return std::visit([](const auto &v){ return v.type; }, value);
}

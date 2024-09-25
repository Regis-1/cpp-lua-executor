cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(SDIR ${CMAKE_SOURCE_DIR}/src)
set(IDIR ${CMAKE_SOURCE_DIR}/include)
set(EXTDIR ${CMAKE_SOURCE_DIR}/extlibs)

project(
    lua-integration
    VERSION 0.1
    DESCRIPTION "My simple program for recalling Lua API"
    LANGUAGES CXX C
)

add_subdirectory(${EXTDIR})

add_executable(
    ${PROJECT_NAME}
    ${SDIR}/main.cpp
    ${SDIR}/LuaExec.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${IDIR}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE lua
)

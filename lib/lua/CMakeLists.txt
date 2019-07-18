# project( LuaLib )

# set  (LUA_RUNTIME_SOURCES
# "lauxlib.h"
# "lua.h"
# "lua.hpp"
# "luaconf.h"
# "lualib.h"
# "sol.hpp"
# )

# add_library(LuaLib ${LUA_RUNTIME_SOURCES})

# target_include_directories(LuaLib PUBLIC "${PROJECT_SOURCE_DIR}/src")

file(GLOB lua_files ./*.hpp ./*.h)
set(LuaLib ${lua_files})


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so")
set(LUA_VERSION_STRING "5.3.0")
find_package(Lua 5.3)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")

add_subdirectory(components)

file(GLOB source_files ./*.hpp ./*.cpp)
set(SOURCES ${source_files})

add_executable(2dGameEngine ${SOURCES} ${COMPONENT_SOURCES} ${LuaLib})
target_link_libraries(2dGameEngine glmlib SDL2 SDL2_image SDL2_ttf SDL2_mixer lua)

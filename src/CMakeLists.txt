find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so")
find_package(Lua 5.3 REQUIRED)

add_subdirectory(components)

file(GLOB source_files ./*.hpp ./*.cpp)
set(SOURCES ${source_files})

add_executable(2DCopterGame ${SOURCES} ${COMPONENT_SOURCES} ${LuaLib})
target_link_libraries(2DCopterGame glmlib SDL2 SDL2_image SDL2_ttf lua5.3)

find_package(SDL2 REQUIRED)
include_directories(2dGameEngine ${SDL2_INCLUDE_DIRS})

add_executable(2dGameEngine main.cpp)
target_link_libraries(2dGameEngine libraries ${SDL2_LIBRARIES})
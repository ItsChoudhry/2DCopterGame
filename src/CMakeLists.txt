find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(SOURCES main.cpp Game.cpp Game.cpp Constants.h)

add_executable(2dGameEngine ${SOURCES})
target_link_libraries(2dGameEngine libraries
                                   SDL2
                                   SDL2_image
                                   SDL2_ttf
                                   SDL2_mixer)

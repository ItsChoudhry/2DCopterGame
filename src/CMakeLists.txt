find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS}
                    ${SDL2_IMAGE_INCLUDE_DIRS}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIR})

set(SOURCES main.cpp Game.cpp Game.cpp Constants.h)

add_executable(2dGameEngine ${SOURCES})
target_link_libraries(2dGameEngine libraries
                                   ${SDL2_LIBRARIES}
                                   ${SDL2_IMAGE_INCLUDE_DIRS}
                                   ${SDL2_TTF_INCLUDE_DIR}
                                   ${SDL2_MIXER_INCLUDE_DIR})

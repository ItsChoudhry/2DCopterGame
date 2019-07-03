find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_subdirectory(components)

set(SOURCES main.cpp Game.hpp Game.cpp Constants.hpp Component.hpp Entity.hpp Entity.cpp
 EntityManager.hpp EntityManager.cpp)

add_executable(2dGameEngine ${SOURCES} ${COMPONENT_SOURCES})
target_link_libraries(2dGameEngine libraries
                                   SDL2
                                   SDL2_image
                                   SDL2_ttf
                                   SDL2_mixer)

cmake_minimum_required(VERSION 3.10)
project(GGJ2018)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(GGJ2018 ${SOURCE_FILES} src/Game/BallActor.cpp src/Game/BallActor.h src/Game/Player2Actor.cpp src/Game/Player2Actor.h src/Game/Player1Actor.cpp src/Game/Player1Actor.h)
TARGET_LINK_LIBRARIES(GGJ2018 pthread)
TARGET_LINK_LIBRARIES(GGJ2018 stdc++fs)
TARGET_LINK_LIBRARIES(GGJ2018 sfml-system)
TARGET_LINK_LIBRARIES(GGJ2018 sfml-audio)
TARGET_LINK_LIBRARIES(GGJ2018 sfml-graphics)
TARGET_LINK_LIBRARIES(GGJ2018 sfml-window)
TARGET_LINK_LIBRARIES(GGJ2018 sfml-network)
TARGET_LINK_LIBRARIES(GGJ2018 Box2D)
TARGET_LINK_LIBRARIES(GGJ2018 m)
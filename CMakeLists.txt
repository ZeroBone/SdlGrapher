cmake_minimum_required(VERSION 3.13)
project(zavu)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# add_executable(zavu main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

#find_package(SDL2TTF REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(SOURCE_FILES main.cpp src/App.c++ src/App.h src/Grapher.c++ src/Grapher.h)
add_executable(zavu ${SOURCE_FILES})


#find_package(SDL_ttf)

# target_link_libraries(zavu mingw32 SDL2main SDL2)
#target_link_libraries(zavu mingw32 SDL2main SDL2 ${SDL2TTF_LIBRARY})
target_link_libraries(zavu mingw32 SDL2main SDL2 SDL2_ttf)
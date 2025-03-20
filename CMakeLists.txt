cmake_minimum_required(VERSION 3.10)
project(Projet C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

add_executable(Projet src/main.c src/find_exec.c src/open_image.c)
target_link_libraries(Projet ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} SDL2_image)
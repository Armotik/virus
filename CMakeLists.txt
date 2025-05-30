cmake_minimum_required(VERSION 3.10)
project(ProjetVirus C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

set(SOURCES
        mediaplayer.c
        scanner.c
        detection.c
        infection.c
        transfert.c
)

set(HEADERS
        mediaplayer.h
        scanner.h
        detection.h
        infection.h
        transfert.h
)

add_executable(MediaPlayer.exe ${SOURCES} ${HEADERS})

target_link_libraries(MediaPlayer.exe ${GTK3_LIBRARIES})
target_link_libraries(MediaPlayer.exe ${GTK3_LIBRARIES} pthread)

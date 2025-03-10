cmake_minimum_required(VERSION 3.30)
project(Project)
set(CMAKE_CXX_STANDARD 20)

include_directories(src)


#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -pedantic")
#set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -Werror -Wall -pedantic")

set(PROJECT_HEADERS
        src/libs/GraphBuilder.h
        src/libs/Graph.h
        src/libs/MutablePriorityQueue.h
        src/libs/Menu.h
        src/libs/tc.h
)
set(PROJECT_SOURCES
        src/main/GraphBuilder.cpp
        src/main/Menu.cpp
)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


add_executable(Project
        src/main/main.cpp
        ${PROJECT_HEADERS}
        ${PROJECT_SOURCES}
)
target_link_libraries(Project ${CURSES_LIBRARIES})
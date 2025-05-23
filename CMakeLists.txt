cmake_minimum_required(VERSION 3.30)
project(Project)
set(CMAKE_CXX_STANDARD 20)

include_directories(src)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -pedantic")
set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -Werror -Wall -pedantic")

set(PROJECT_HEADERS
        src/libs/GraphBuilder.h
        src/libs/Graph.h
        src/libs/MutablePriorityQueue.h
        src/libs/Menu.h
        src/libs/tc.h
        src/libs/RouteSearch.h
        src/libs/InputUtils.h
        src/libs/DijkstraFunctions.h
        src/libs/EcologicalRouteSearch.h
)
set(PROJECT_SOURCES
        src/main/GraphBuilder.cpp
        src/main/RouteSearch.cpp
        src/main/Menu.cpp
        src/main/InputUtils.cpp
        src/main/DijkstraFunctions.cpp
        src/main/EcologicalRouteSearch.cpp
)

add_executable(Project
        src/main/main.cpp
        ${PROJECT_HEADERS}
        ${PROJECT_SOURCES}
)
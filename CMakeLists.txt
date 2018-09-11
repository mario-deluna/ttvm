cmake_minimum_required(VERSION 3.2)

project(ttvm)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(TTVM_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TTVM_MAIN "${TTVM_SRC_DIR}/main.cpp")

file(GLOB TTVM_SRC
    "${TTVM_SRC_DIR}/*.h*"
    "${TTVM_SRC_DIR}/*.c*"
)

# Remove main.cpp form the source list
list(REMOVE_ITEM TTVM_SRC ${TTVM_MAIN})

add_executable(${PROJECT_NAME} ${TTVM_MAIN} ${TTVM_SRC})

# SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

###
# Installation
###
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
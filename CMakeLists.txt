cmake_minimum_required(VERSION 3.1)
project(Drone)

set(EXECUTABLE ${CMAKE_PROJECT_NAME}_run)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/GNUPlot)
add_subdirectory(test)
add_subdirectory(lib/googletest)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true include/*.h source/*.cpp)

include_directories(${CMAKE_SOURCE_DIR}/lib/GNUPlot)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${EXECUTABLE} ${SOURCES})
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
target_link_libraries(${EXECUTABLE} PRIVATE GNUPlot_lib)

# Doxygen

option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")
    add_custom_target(doc_doxygen ALL COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT} WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMENT "Generate doxygen" VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen not found, need to be installed to generate the doxygen")
endif()
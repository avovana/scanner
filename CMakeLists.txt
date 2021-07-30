cmake_minimum_required(VERSION 3.5)

project(scanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


#===============

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Thrift REQUIRED)

option(THRIFT_LIBRARIES_REQUIRED "Project initialization should fail on missed thrift libraries" ON)

find_path(THRIFT_INCLUDE_DIR
    NAMES thrift/Thrift.h
    HINTS ${THRIFT_ROOT}
    PATH_SUFFIXES include
)

find_library(THRIFT_LIBRARY
    thrift
    HINTS ${THRIFT_ROOT}
    PATH_SUFFIXES lib
)

include_directories(SYSTEM ${THRIFT_INCLUDE_DIR})
if (THRIFT_LIBRARY)
    set(COMMON_LIBS ${COMMON_LIBS} ${THRIFT_LIBRARY})
endif ()


#===============







set(SOURCE_FILES
    src/ConsoleMain.cpp
    src/ConsoleSampleEventListener.cpp
    src/ISO15434formatEnvelope.cpp
    src/pugixml.cpp
    src/SlaveController.cpp
)

set(LIBS
    cs-client
    cs-common
)

add_executable(${PROJECT_NAME}
    main.cpp
    ${SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    -L/usr/lib/zebra-scanner/corescanner
    ${LIBS}
    ${COMMON_LIBS}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
    gen-cpp
    /usr/include/zebra-scanner
    /usr/lib/zebra-scanner/corescanner
)

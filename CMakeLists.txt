cmake_minimum_required(VERSION 3.5)

project(scanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SOURCE_FILES
    src/ConsoleMain.cpp
    src/ConsoleSampleEventListener.cpp
    src/ISO15434formatEnvelope.cpp
    src/pugixml.cpp
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
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
    /usr/include/zebra-scanner
    /usr/lib/zebra-scanner/corescanner
)

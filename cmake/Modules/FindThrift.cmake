# Find Thrift (a cross platform RPC lib/tool)
# This module defines:
#
# THRIFT_LIBRARIES - libraries to link
# THRIFT_INCLUDE_DIR - where to find THRIFT headers
# THRIFT_COMPILER - thrift compiler executable
# THRIFT_FOUND - if thrift found
#
# NOTE: be noticed that this file is enchanced to qkd project

FIND_PROGRAM(
    THRIFT_COMPILER thrift
    HINTS ${THRIFT_PATH}
    PATH_SUFFIXES bin)

FIND_PATH(THRIFT_INCLUDE_DIR
    NAMES thrift/Thrift.h
    HINTS ${THRIFT_ROOT}
    PATH_SUFFIXES include)

FIND_LIBRARY(THRIFT_LIBRARIES
    thrift
    HINTS ${THRIFT_ROOT}
    PATH_SUFFIXES lib)

FUNCTION(add_thrift_api api_name service_name target_name thrift_cpp_files thrift_header_files thrift_include_dirs)
    SET(${thrift_cpp_files}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/${api_name}_constants.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/${api_name}_types.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/${service_name}.cpp
            )

    SET(${thrift_header_files}
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${api_name}/generated/${api_name}_constants.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${api_name}/generated/${api_name}_types.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${api_name}/generated/${service_name}.h
            )

    SET(${thrift_include_dirs} ${CMAKE_CURRENT_SOURCE_DIR}/include/${api_name}/generated)

    SET(${thrift_cpp_files} ${${thrift_cpp_files}} PARENT_SCOPE)
    SET(${thrift_header_files} ${${thrift_header_files}} PARENT_SCOPE)
    SET(${thrift_include_dirs} ${${thrift_include_dirs}} PARENT_SCOPE)
    SET(${target_name} ${api_name}_proto PARENT_SCOPE)

    # Build thrift C++ protocol implementation
    ADD_CUSTOM_COMMAND(
            OUTPUT ${${thrift_cpp_files}} ${${thrift_header_files}}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/src/generated
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/include/${api_name}/generated
            COMMAND ${THRIFT_COMPILER} -out ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/ -gen cpp ${CMAKE_CURRENT_SOURCE_DIR}/${api_name}.thrift
            COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/${service_name}_server.skeleton.cpp
            COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/${api_name}_constants.h ${${thrift_include_dirs}}/${api_name}_constants.h
            COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/${api_name}_types.h ${${thrift_include_dirs}}/${api_name}_types.h
            COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/${service_name}.h ${${thrift_include_dirs}}/${service_name}.h
            COMMENT "Generate C++ thrift ${service_name} API implementation"
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${api_name}.thrift
            VERBATIM)

    #    SET_SOURCE_FILES_PROPERTIES(${${thrift_cpp_files}} ${${thrift_header_files}}
    #        PROPERTIES GENERATED 1)

    ADD_CUSTOM_TARGET(${api_name}_proto
            SOURCES ${api_name}.thrift
            ${${thrift_cpp_files}}
            ${${thrift_header_files}}
            )


ENDFUNCTION()

INCLUDE(FindPackageHandleStandardArgs)

IF (THRIFT_LIBRARIES_REQUIRED)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(THRIFT DEFAULT_MSG THRIFT_LIBRARIES THRIFT_INCLUDE_DIR
        THRIFT_COMPILER)
ELSE ()
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(THRIFT DEFAULT_MSG THRIFT_INCLUDE_DIR
        THRIFT_COMPILER)
    IF (NOT THRIFT_LIBRARIES)
        MESSAGE(WARNING
            "Thrift libraries not found, project linkage will be failed")
        SET (THRIFT_LIBRARIES "")
    ENDIF (NOT THRIFT_LIBRARIES)
ENDIF (THRIFT_LIBRARIES_REQUIRED)


mark_as_advanced(THRIFT_LIBRARIES THRIFT_INCLUDE_DIR THRIFT_COMPILER)

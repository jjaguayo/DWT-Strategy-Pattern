cmake_minimum_required(VERSION 3.0)

project(DWT CXX)

set(TARGET_NAME "DWT")


include_directories(${PROJECT_SOURCE_DIR}/hdrs)

enable_testing()

function(build_on_linux)
    set(SRC_FILES "")
    add_subdirectory(${PROJECT_SOURCE_DIR}/src)
    # set target dest dir
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

    # add shared library target
    add_library(${TARGET_NAME} SHARED
        ${SRC_FILES}
    )

    set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 11)
endfunction()

function(build_tests)
    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
     
    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
     
    # Add googletest directly to our build. This adds
    # the following targets: gtest, gtest_main, gmock
    # and gmock_main

    add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                     "${CMAKE_BINARY_DIR}/googletest-build")

    add_executable(runUnitTests
                   ${PROJECT_SOURCE_DIR}/test/test_Haar1DTransform.cpp
    )

    target_link_libraries(runUnitTests 
        gtest 
        gtest_main 
        DWT
    )

    add_test(runUnitTests runUnitTests)
endfunction()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    build_on_linux()
    build_tests()
else()
    message(FATAL_ERROR "Build does not currently support system type")
endif()

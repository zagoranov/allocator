SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(allocator VERSION 0.0.13)
endif()

# Setup testing
#enable_testing()
#find_package(GTest REQUIRED)
#set(GTEST_ROOT "/usr/src/gtest" CACHE PATH "Path to googletest")
#include_directories(${GTEST_INCLUDE_DIRS})
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

configure_file(version.h.in version.h)

add_executable(allocator_cli main.cpp)

add_library(allocator lib.cpp alloc.cpp)
                                      
set_target_properties(allocator_cli allocator PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties(allocator_cli PROPERTIES LINK_FLAGS -pthread
)

target_link_libraries(allocator_cli
    allocator
)

#install(TARGETS allocator_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT r.muzyukin@gmail.com)

include(CPack)


# Add test cpp file
# add_executable(runUnitTests tests.cpp)
# Link test executable against gtest & gtest_main
# target_link_libraries(runUnitTests gtest gtest_main)

#add_test(
#    NAME runUnitTests
#    COMMAND runUnitTests
#)

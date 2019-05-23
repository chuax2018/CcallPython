cmake_minimum_required(VERSION 3.5)
project(ccallpy)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++11 -Wall -O0 -ggdb")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)
include_directories(${CMAKE_SOURCE_DIR}/include/
		    /usr/include/python3.6)
link_directories(${CMAKE_SOURCE_DIR}/libs/
		/usr/lib/x86_64-linux-gnu)
file(GLOB src_files ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.h)
add_executable(ccallpy ${src_files})
target_link_libraries(ccallpy python3.6m)

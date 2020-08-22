cmake_minimum_required(VERSION 3.1.0)

project(imageprocessing)

# We want C++11
set (CMAKE_CXX_STANDARD 11)

add_executable(imageprocessing
    main.cpp
    convolution.cpp
    image.cpp
)

target_link_libraries(imageprocessing)

cmake_minimum_required(VERSION 3.2)

project(imageprocessing)

# We want C++11
set (CMAKE_CXX_STANDARD 11)

SET(SRCS
    convolution.cpp
    convolution.h
    image.cpp
    image.h
    main.cpp
    stb_image.h
    stb_image_resize.h
    stb_image_write.h
)

add_executable(imageprocessing ${SRCS})

target_link_libraries(imageprocessing)

include("CMakeLists-zip.txt" OPTIONAL)

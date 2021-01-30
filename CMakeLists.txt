cmake_minimum_required(VERSION 3.2)

project(imageprocessing)

# We want C++11
set(CMAKE_CXX_STANDARD 11)

set(SRCS
    src/convolution.cpp
    src/convolution.h
    src/image.cpp
    src/image.h
    src/main.cpp
    src/stb_image.h
    src/stb_image_resize.h
    src/stb_image_write.h
)

add_executable(imageprocessing ${SRCS})
target_link_libraries(imageprocessing)

include("CMakeLists-zip.txt" OPTIONAL)

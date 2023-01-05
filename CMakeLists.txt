cmake_minimum_required(VERSION 3.12)
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(PicoIntruderDetection C CXX ASM)
pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
add_executable(detector detector.cpp)

# pull in common dependencies
target_link_libraries(detector pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(detector)

# add url via pico_set_program_url
# example_auto_set_url(detector)

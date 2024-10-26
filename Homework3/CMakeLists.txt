cmake_minimum_required(VERSION 3.12)

project(homework3)

add_executable(main
    main.cpp
    generation_numbers.cpp
    generation_numbers.h)

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
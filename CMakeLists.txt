cmake_minimum_required(VERSION 4.2)
project(T1-WorldServer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(T1_TSAN "TSan 빌드를 켠다" OFF)
if (T1_TSAN)
    add_compile_options(-fsanitize=thread -g)
    add_link_options(-fsanitize=thread)
endif ()

find_package(Boost REQUIRED)

add_subdirectory(worldServer)
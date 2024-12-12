cmake_minimum_required(VERSION 3.0)
project(Utils)

set(
    SOURCES
    Logger/src/Logger.cpp
    FeatureTimer/src/FeatureTimer.cpp
)
#!!
add_definitions(-D_STD_LOG_)

add_library(Utils SHARED ${SOURCES})

# Thêm các thư mục include
target_include_directories(
    Utils PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/FeatureTimer/inc
)


install(TARGETS Utils DESTINATION ${CMAKE_SOURCE_DIR})

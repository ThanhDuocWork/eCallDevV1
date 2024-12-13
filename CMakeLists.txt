cmake_minimum_required(VERSION 3.0)
project(project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source project
set(
    SOURCES
    src/main.cpp
    src/Adapters/AudioAdapter.cpp
    src/Adapters/HMIAdapter.cpp
    src/Adapters/MQTTAdapter.cpp
)

# add lib Utils
add_subdirectory(Utils)

# add path include
include_directories(
    ./inc
    ./Utils/Logger/inc
    /home/duoctdt/vcpkg/installed/x64-linux/include
)

# Create executable
add_executable(project ${SOURCES})

# Linking lib Utils
target_link_libraries(project PUBLIC Utils)

# Linking lib
target_link_libraries(project
    PUBLIC
    pthread        
    asound              # ALSA
    mosquitto           # Mosquitto
    curl                # cURL
)

cmake_minimum_required(VERSION 3.0)
project(project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
##set(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath-link,/path/to/sysroot/usr/lib -Wl,-rpath-link,/path/to/sysroot/usr/lib/arm-linux-gnueabihf")
##set(CMAKE_BUILD_RPATH "/path/to/sysroot/usr/lib")

# Source project
set(
    SOURCES
    src/main.cpp
    src/Adapters/AudioAdapter.cpp
    src/Adapters/HMIAdapter.cpp
    src/Adapters/MQTTAdapter.cpp
    src/StateMachine/IDLEState.cpp
    src/StateMachine/CancelTimerState.cpp
    src/StateMachine/CenterState.cpp
    src/StateMachine/EventTable.cpp
)

# add lib Utils
add_subdirectory(Utils)

# add path include
include_directories(
    ./inc/Adapter
    ./inc/StateMachine
    ./Utils/Logger/inc
    /home/duoctdt/vcpkg/installed/x64-linux/include
)

include_directories(/path/to/sysroot/usr/include)
link_directories(
    /path/to/sysroot/usr/lib
    /path/to/sysroot/usr/lib/arm-linux-gnueabihf
)

# Create executable
add_executable(project ${SOURCES})

# Linking lib Utils
target_link_libraries(project PUBLIC Utils)
# Linking lib
target_link_libraries(project
    PUBLIC
    pthread
    asound
    mosquitto
    dl
    rt
)

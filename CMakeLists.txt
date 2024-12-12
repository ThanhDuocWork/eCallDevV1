cmake_minimum_required(VERSION 3.0)
project(project)

# Sử dụng C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Tệp nguồn của project chính
set(
    SOURCES
    src/main.cpp
    src/Adapters/AudioAdapter.cpp
    src/Adapters/HMIAdapter.cpp
    src/Adapters/MQTTAdapter.cpp
)

# Thêm thư mục thư viện Utils
add_subdirectory(Utils)

# Thêm đường dẫn include
include_directories(
    ./inc
    ./Utils/Logger/inc
    /home/duoctdt/vcpkg/installed/x64-linux/include
)

# Tạo executable
add_executable(project ${SOURCES})

# Liên kết với thư viện Utils
target_link_libraries(project PUBLIC Utils)

# Liên kết các thư viện hệ thống khác
target_link_libraries(project
    PUBLIC
    asound              # ALSA
    mosquitto           # Mosquitto
    curl                # cURL
)

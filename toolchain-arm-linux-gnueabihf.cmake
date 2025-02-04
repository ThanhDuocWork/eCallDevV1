# toolchain-arm-linux-gnueabihf.cmake

# Cấu hình các trình biên dịch
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR arm)

# Cross-compilation tools
SET(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)


# Cấu hình thư viện hệ thống của Raspberry Pi
SET(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf)
set(CMAKE_FIND_ROOT_PATH /path/to/sysroot)

set(CMAKE_SYSROOT /path/to/sysroot)
set(CMAKE_INCLUDE_PATH /path/to/sysroot/usr/include)
set(CMAKE_LIBRARY_PATH /path/to/sysroot/usr/lib)

# Đảm bảo rằng CMake tìm kiếm thư viện và tệp đầu vào từ các đường dẫn của Raspberry Pi
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Thêm các thư viện của Raspberry Pi
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/duoctdt/CrossEXProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/duoctdt/CrossEXProject/build

# Include any dependencies generated for this target.
include Utils/CMakeFiles/Utils.dir/depend.make

# Include the progress variables for this target.
include Utils/CMakeFiles/Utils.dir/progress.make

# Include the compile flags for this target's objects.
include Utils/CMakeFiles/Utils.dir/flags.make

Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o: Utils/CMakeFiles/Utils.dir/flags.make
Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o: ../Utils/Logger/src/Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/duoctdt/CrossEXProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o -c /home/duoctdt/CrossEXProject/Utils/Logger/src/Logger.cpp

Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utils.dir/Logger/src/Logger.cpp.i"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duoctdt/CrossEXProject/Utils/Logger/src/Logger.cpp > CMakeFiles/Utils.dir/Logger/src/Logger.cpp.i

Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utils.dir/Logger/src/Logger.cpp.s"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duoctdt/CrossEXProject/Utils/Logger/src/Logger.cpp -o CMakeFiles/Utils.dir/Logger/src/Logger.cpp.s

Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o.requires:

.PHONY : Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o.requires

Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o.provides: Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o.requires
	$(MAKE) -f Utils/CMakeFiles/Utils.dir/build.make Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o.provides.build
.PHONY : Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o.provides

Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o.provides.build: Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o


Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o: Utils/CMakeFiles/Utils.dir/flags.make
Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o: ../Utils/FeatureTimer/src/FeatureTimer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/duoctdt/CrossEXProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o -c /home/duoctdt/CrossEXProject/Utils/FeatureTimer/src/FeatureTimer.cpp

Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.i"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duoctdt/CrossEXProject/Utils/FeatureTimer/src/FeatureTimer.cpp > CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.i

Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.s"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duoctdt/CrossEXProject/Utils/FeatureTimer/src/FeatureTimer.cpp -o CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.s

Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o.requires:

.PHONY : Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o.requires

Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o.provides: Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o.requires
	$(MAKE) -f Utils/CMakeFiles/Utils.dir/build.make Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o.provides.build
.PHONY : Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o.provides

Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o.provides.build: Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o


Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o: Utils/CMakeFiles/Utils.dir/flags.make
Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o: ../Utils/SimulateButton/src/SimulateButton.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/duoctdt/CrossEXProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o -c /home/duoctdt/CrossEXProject/Utils/SimulateButton/src/SimulateButton.cpp

Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.i"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duoctdt/CrossEXProject/Utils/SimulateButton/src/SimulateButton.cpp > CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.i

Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.s"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duoctdt/CrossEXProject/Utils/SimulateButton/src/SimulateButton.cpp -o CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.s

Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o.requires:

.PHONY : Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o.requires

Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o.provides: Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o.requires
	$(MAKE) -f Utils/CMakeFiles/Utils.dir/build.make Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o.provides.build
.PHONY : Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o.provides

Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o.provides.build: Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o


Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o: Utils/CMakeFiles/Utils.dir/flags.make
Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o: ../Utils/ManagerMessage/src/ManagerMessage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/duoctdt/CrossEXProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o -c /home/duoctdt/CrossEXProject/Utils/ManagerMessage/src/ManagerMessage.cpp

Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.i"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duoctdt/CrossEXProject/Utils/ManagerMessage/src/ManagerMessage.cpp > CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.i

Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.s"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duoctdt/CrossEXProject/Utils/ManagerMessage/src/ManagerMessage.cpp -o CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.s

Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o.requires:

.PHONY : Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o.requires

Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o.provides: Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o.requires
	$(MAKE) -f Utils/CMakeFiles/Utils.dir/build.make Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o.provides.build
.PHONY : Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o.provides

Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o.provides.build: Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o


Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o: Utils/CMakeFiles/Utils.dir/flags.make
Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o: ../Utils/EventData/src/EventData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/duoctdt/CrossEXProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o -c /home/duoctdt/CrossEXProject/Utils/EventData/src/EventData.cpp

Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utils.dir/EventData/src/EventData.cpp.i"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duoctdt/CrossEXProject/Utils/EventData/src/EventData.cpp > CMakeFiles/Utils.dir/EventData/src/EventData.cpp.i

Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utils.dir/EventData/src/EventData.cpp.s"
	cd /home/duoctdt/CrossEXProject/build/Utils && /usr/bin/arm-linux-gnueabihf-g++ --sysroot=/path/to/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duoctdt/CrossEXProject/Utils/EventData/src/EventData.cpp -o CMakeFiles/Utils.dir/EventData/src/EventData.cpp.s

Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o.requires:

.PHONY : Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o.requires

Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o.provides: Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o.requires
	$(MAKE) -f Utils/CMakeFiles/Utils.dir/build.make Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o.provides.build
.PHONY : Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o.provides

Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o.provides.build: Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o


# Object files for target Utils
Utils_OBJECTS = \
"CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o" \
"CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o" \
"CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o" \
"CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o" \
"CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o"

# External object files for target Utils
Utils_EXTERNAL_OBJECTS =

Utils/libUtils.so: Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o
Utils/libUtils.so: Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o
Utils/libUtils.so: Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o
Utils/libUtils.so: Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o
Utils/libUtils.so: Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o
Utils/libUtils.so: Utils/CMakeFiles/Utils.dir/build.make
Utils/libUtils.so: Utils/CMakeFiles/Utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/duoctdt/CrossEXProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX shared library libUtils.so"
	cd /home/duoctdt/CrossEXProject/build/Utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Utils/CMakeFiles/Utils.dir/build: Utils/libUtils.so

.PHONY : Utils/CMakeFiles/Utils.dir/build

Utils/CMakeFiles/Utils.dir/requires: Utils/CMakeFiles/Utils.dir/Logger/src/Logger.cpp.o.requires
Utils/CMakeFiles/Utils.dir/requires: Utils/CMakeFiles/Utils.dir/FeatureTimer/src/FeatureTimer.cpp.o.requires
Utils/CMakeFiles/Utils.dir/requires: Utils/CMakeFiles/Utils.dir/SimulateButton/src/SimulateButton.cpp.o.requires
Utils/CMakeFiles/Utils.dir/requires: Utils/CMakeFiles/Utils.dir/ManagerMessage/src/ManagerMessage.cpp.o.requires
Utils/CMakeFiles/Utils.dir/requires: Utils/CMakeFiles/Utils.dir/EventData/src/EventData.cpp.o.requires

.PHONY : Utils/CMakeFiles/Utils.dir/requires

Utils/CMakeFiles/Utils.dir/clean:
	cd /home/duoctdt/CrossEXProject/build/Utils && $(CMAKE_COMMAND) -P CMakeFiles/Utils.dir/cmake_clean.cmake
.PHONY : Utils/CMakeFiles/Utils.dir/clean

Utils/CMakeFiles/Utils.dir/depend:
	cd /home/duoctdt/CrossEXProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/duoctdt/CrossEXProject /home/duoctdt/CrossEXProject/Utils /home/duoctdt/CrossEXProject/build /home/duoctdt/CrossEXProject/build/Utils /home/duoctdt/CrossEXProject/build/Utils/CMakeFiles/Utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Utils/CMakeFiles/Utils.dir/depend


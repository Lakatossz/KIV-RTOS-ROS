# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace

# Include any dependencies generated for this target.
include stdlib/CMakeFiles/kivrtos_stdlib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.make

# Include the progress variables for this target.
include stdlib/CMakeFiles/kivrtos_stdlib.dir/progress.make

# Include the compile flags for this target's objects.
include stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make

stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdfile.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdfile.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdfile.cpp > CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdfile.cpp -o CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdmutex.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdmutex.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdmutex.cpp > CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdmutex.cpp -o CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdstring.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdstring.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdstring.cpp > CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib/src/stdstring.cpp -o CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/air_in_line.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/air_in_line.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/air_in_line.cpp > CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/air_in_line.cpp -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/battery_system.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/battery_system.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/battery_system.cpp > CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/battery_system.cpp -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/cgm.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/cgm.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/cgm.cpp > CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/cgm.cpp -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/motor.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/motor.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/motor.cpp > CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/motor.cpp -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/oled.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/oled.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/oled.cpp > CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/oled.cpp -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/pressure.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/pressure.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/pressure.cpp > CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/pressure.cpp -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/rtc.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/rtc.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/rtc.cpp > CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/rtc.cpp -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/temperature.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/temperature.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/temperature.cpp > CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/temperature.cpp -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.s

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/flags.make
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.obj: /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/wdt.cpp
stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.obj: stdlib/CMakeFiles/kivrtos_stdlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.obj"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.obj -MF CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.obj.d -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.obj -c /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/wdt.cpp

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.i"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/wdt.cpp > CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.i

stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.s"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdutils/src/wdt.cpp -o CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.s

# Object files for target kivrtos_stdlib
kivrtos_stdlib_OBJECTS = \
"CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.obj" \
"CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.obj"

# External object files for target kivrtos_stdlib
kivrtos_stdlib_EXTERNAL_OBJECTS =

stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdfile.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdmutex.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/src/stdstring.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/air_in_line.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/battery_system.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/cgm.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/motor.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/oled.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/pressure.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/rtc.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/temperature.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/__/stdutils/src/wdt.cpp.obj
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/build.make
stdlib/libkivrtos_stdlib.a: stdlib/CMakeFiles/kivrtos_stdlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX static library libkivrtos_stdlib.a"
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && $(CMAKE_COMMAND) -P CMakeFiles/kivrtos_stdlib.dir/cmake_clean_target.cmake
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kivrtos_stdlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
stdlib/CMakeFiles/kivrtos_stdlib.dir/build: stdlib/libkivrtos_stdlib.a
.PHONY : stdlib/CMakeFiles/kivrtos_stdlib.dir/build

stdlib/CMakeFiles/kivrtos_stdlib.dir/clean:
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib && $(CMAKE_COMMAND) -P CMakeFiles/kivrtos_stdlib.dir/cmake_clean.cmake
.PHONY : stdlib/CMakeFiles/kivrtos_stdlib.dir/clean

stdlib/CMakeFiles/kivrtos_stdlib.dir/depend:
	cd /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/stdlib /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib /mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/stdlib/CMakeFiles/kivrtos_stdlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : stdlib/CMakeFiles/kivrtos_stdlib.dir/depend


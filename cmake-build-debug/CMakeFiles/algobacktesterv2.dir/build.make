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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/samkirkiles/Desktop/algobacktesterv2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/samkirkiles/Desktop/algobacktesterv2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/algobacktesterv2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/algobacktesterv2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/algobacktesterv2.dir/flags.make

CMakeFiles/algobacktesterv2.dir/main.cpp.o: CMakeFiles/algobacktesterv2.dir/flags.make
CMakeFiles/algobacktesterv2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/samkirkiles/Desktop/algobacktesterv2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/algobacktesterv2.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/algobacktesterv2.dir/main.cpp.o -c /Users/samkirkiles/Desktop/algobacktesterv2/main.cpp

CMakeFiles/algobacktesterv2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/algobacktesterv2.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/samkirkiles/Desktop/algobacktesterv2/main.cpp > CMakeFiles/algobacktesterv2.dir/main.cpp.i

CMakeFiles/algobacktesterv2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/algobacktesterv2.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/samkirkiles/Desktop/algobacktesterv2/main.cpp -o CMakeFiles/algobacktesterv2.dir/main.cpp.s

CMakeFiles/algobacktesterv2.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/algobacktesterv2.dir/main.cpp.o.requires

CMakeFiles/algobacktesterv2.dir/main.cpp.o.provides: CMakeFiles/algobacktesterv2.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/algobacktesterv2.dir/build.make CMakeFiles/algobacktesterv2.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/algobacktesterv2.dir/main.cpp.o.provides

CMakeFiles/algobacktesterv2.dir/main.cpp.o.provides.build: CMakeFiles/algobacktesterv2.dir/main.cpp.o


CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o: CMakeFiles/algobacktesterv2.dir/flags.make
CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o: ../Data-Handling/YahooFinanceDownloader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/samkirkiles/Desktop/algobacktesterv2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o -c /Users/samkirkiles/Desktop/algobacktesterv2/Data-Handling/YahooFinanceDownloader.cpp

CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/samkirkiles/Desktop/algobacktesterv2/Data-Handling/YahooFinanceDownloader.cpp > CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.i

CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/samkirkiles/Desktop/algobacktesterv2/Data-Handling/YahooFinanceDownloader.cpp -o CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.s

CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o.requires:

.PHONY : CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o.requires

CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o.provides: CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o.requires
	$(MAKE) -f CMakeFiles/algobacktesterv2.dir/build.make CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o.provides.build
.PHONY : CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o.provides

CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o.provides.build: CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o


CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o: CMakeFiles/algobacktesterv2.dir/flags.make
CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o: ../Data-Handling/DataRetriever.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/samkirkiles/Desktop/algobacktesterv2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o -c /Users/samkirkiles/Desktop/algobacktesterv2/Data-Handling/DataRetriever.cpp

CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/samkirkiles/Desktop/algobacktesterv2/Data-Handling/DataRetriever.cpp > CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.i

CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/samkirkiles/Desktop/algobacktesterv2/Data-Handling/DataRetriever.cpp -o CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.s

CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o.requires:

.PHONY : CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o.requires

CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o.provides: CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o.requires
	$(MAKE) -f CMakeFiles/algobacktesterv2.dir/build.make CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o.provides.build
.PHONY : CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o.provides

CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o.provides.build: CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o


# Object files for target algobacktesterv2
algobacktesterv2_OBJECTS = \
"CMakeFiles/algobacktesterv2.dir/main.cpp.o" \
"CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o" \
"CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o"

# External object files for target algobacktesterv2
algobacktesterv2_EXTERNAL_OBJECTS =

algobacktesterv2: CMakeFiles/algobacktesterv2.dir/main.cpp.o
algobacktesterv2: CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o
algobacktesterv2: CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o
algobacktesterv2: CMakeFiles/algobacktesterv2.dir/build.make
algobacktesterv2: CMakeFiles/algobacktesterv2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/samkirkiles/Desktop/algobacktesterv2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable algobacktesterv2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/algobacktesterv2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/algobacktesterv2.dir/build: algobacktesterv2

.PHONY : CMakeFiles/algobacktesterv2.dir/build

CMakeFiles/algobacktesterv2.dir/requires: CMakeFiles/algobacktesterv2.dir/main.cpp.o.requires
CMakeFiles/algobacktesterv2.dir/requires: CMakeFiles/algobacktesterv2.dir/Data-Handling/YahooFinanceDownloader.cpp.o.requires
CMakeFiles/algobacktesterv2.dir/requires: CMakeFiles/algobacktesterv2.dir/Data-Handling/DataRetriever.cpp.o.requires

.PHONY : CMakeFiles/algobacktesterv2.dir/requires

CMakeFiles/algobacktesterv2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/algobacktesterv2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/algobacktesterv2.dir/clean

CMakeFiles/algobacktesterv2.dir/depend:
	cd /Users/samkirkiles/Desktop/algobacktesterv2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/samkirkiles/Desktop/algobacktesterv2 /Users/samkirkiles/Desktop/algobacktesterv2 /Users/samkirkiles/Desktop/algobacktesterv2/cmake-build-debug /Users/samkirkiles/Desktop/algobacktesterv2/cmake-build-debug /Users/samkirkiles/Desktop/algobacktesterv2/cmake-build-debug/CMakeFiles/algobacktesterv2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/algobacktesterv2.dir/depend


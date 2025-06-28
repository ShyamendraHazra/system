# Specify the minimum CMake version required to build the project
cmake_minimum_required(VERSION 3.10)

# Enable parallel building
set(CMAKE_BUILD_PARALLEL_LEVEL ${NUMBER_OF_PROCESSORS})

#set project name
set(PROJECT "cc_project")

# Define the project name and the languages used (C and C++)
project(${PROJECT} C CXX)

set(CMAKE_C_COMPILER "/usr/bin/clang")

# get the directory of the current source file, which is the project root
get_filename_component(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

# Recursively find all .cpp files in the 'src' directory and store them in the SOURCES variable
file(GLOB_RECURSE SOURCES "${PROJECT_ROOT}/src/*.cc" "${PROJECT_ROOT}/src/*.c")

# Set the directory where the executable binaries will be placed
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/bin/${CMAKE_SYSTEM_NAME})

# Set the directory where the shared libraries (.so/.dll) will be placed
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_ROOT}/bin/${CMAKE_SYSTEM_NAME})

# Set the directory where the static libraries (.a) will be placed
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_ROOT}/bin/${CMAKE_SYSTEM_NAME})

# Define the include directory for project-specific headers
set(PROJECT_INCLUDE_DIR "${PROJECT_ROOT}/src/include")

# Set output directory
set(PREPROCESS_DIR "${PROJECT_ROOT}/preprocessed")
file(MAKE_DIRECTORY "${PREPROCESS_DIR}")

# Verify include directory exists
if(NOT EXISTS "${PROJECT_INCLUDE_DIR}")
	message(FATAL_ERROR "Include directory not found: ${PROJECT_INCLUDE_DIR}")
endif()



# Preprocess output directory
set(PREPROCESS_DIR "${PROJECT_ROOT}/preprocessed")
file(MAKE_DIRECTORY "${PREPROCESS_DIR}")

# Collect all C/C++ sources
file(GLOB_RECURSE SOURCES "${PROJECT_ROOT}/src/*.c")


# Check if the current operating system is Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	# Specify the C compiler for Windows (MinGW)
	set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

	# Specify the C++ compiler for Windows (MinGW)
	set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

	# Specify the order of library suffixes to look for (static .a first, then dynamic .dll)
	set(CMAKE_FIND_LIBRARY_SUFFIXES .a .dll)

	# Create an executable named '${PROJECT}_win' using the source files
	add_executable(${PROJECT}_win ${SOURCES})
	list(REMOVE_ITEM ${SOURCES} "main.c")
	add_executable(test_${PROJECT}_win ${SOURCES})
	# Set the include directories for the Windows build (where to find headers)
	target_include_directories(${PROJECT}_win PRIVATE ${PROJECT_INCLUDE_DIR} /usr/x86_64-w64-mingw32/include)
	target_include_directories(test_${PROJECT}_win PRIVATE ${PROJECT_INCLUDE_DIR} /usr/x86_64-w64-mingw32/include)

	# Set the directories where the linker will look for libraries on Windows
	target_link_directories(${PROJECT}_win PRIVATE /usr/x86_64-w64-mingw32/bin)
	target_link_directories(test_${PROJECT}_win PRIVATE /usr/x86_64-w64-mingw32/bin)



	# Add custom command to copy DLL files after the build
	add_custom_command(TARGET ${PROJECT}_win POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_if_different
								/usr/x86_64-w64-mingw32/bin/libssp-0.dll
								${CMAKE_RUNTIME_OUTPUT_DIRECTORY}

				COMMAND ${CMAKE_COMMAND} -E copy_if_different
								/usr/x86_64-w64-mingw32/bin/libstdc++-6.dll
								${CMAKE_RUNTIME_OUTPUT_DIRECTORY}


				COMMAND ${CMAKE_COMMAND} -E copy_if_different
								/usr/x86_64-w64-mingw32/bin/libgcc_s_seh-1.dll
								${CMAKE_RUNTIME_OUTPUT_DIRECTORY}

				COMMAND ${CMAKE_COMMAND} -E copy_if_different
								/usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll
								${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
				)

else()
	# If not Windows, assume Linux-specific settings

	# Create an executable named '${PROJECT}_linux' using the source files
	
	message("\n------ Added all files to sources ------\n")

	# remove test.main.c from release binary target
	list(REMOVE_ITEM SOURCES "${PROJECT_ROOT}/src/tests/test.main.c")

	message("\n------ Removed test.main.c ------\n")

	# create release binary target
	add_executable(${PROJECT}_linux ${SOURCES})

	message("\n------ Added release binary target ------\n")

		
	#Append test.main.c for test binary target
	list(APPEND SOURCES "${PROJECT_ROOT}/src/tests/test.main.c")

	# Remove main.c from test binary
	list(REMOVE_ITEM SOURCES "${PROJECT_ROOT}/src/main.c")

	message("\n------ Added test.main.c and removed main.c ------\n")

	# add test binary target
	add_executable(${PROJECT}_linux_test ${SOURCES})

	message("\n------ Added test binary target ------\n")

	# Set the include directories for the Linux build (where to find headers)
	target_include_directories(${PROJECT}_linux PRIVATE ${PROJECT_INCLUDE_DIR} /usr/include)
	target_include_directories(${PROJECT}_linux_test PRIVATE ${PROJECT_INCLUDE_DIR} /usr/include)

	# Set the directories where the linker will look for libraries on Linux
	target_link_directories(${PROJECT}_linux PRIVATE /usr/lib)
	target_link_directories(${PROJECT}_linux_test PRIVATE /usr/lib)

endif()

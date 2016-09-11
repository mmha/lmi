cmake_minimum_required(VERSION 3.6)
project(lmi VERSION "0.1.0")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(CMakePackageConfigHelpers)
include(GenerateClangTidyTarget)

find_package(Doxygen)
if(Doxygen_FOUND)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)
	if(Doxygen_DOT_FOUND)
		set(USE_DOT "YES")
	else()
		set(USE_DOT "NO")
	endif()
	configure_file("${CMAKE_SOURCE_DIR}/Doxyfile.in" "${CMAKE_BINARY_DIR}/Doxyfile" @ONLY)
	add_custom_target(doc	${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/Doxyfile"
				WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/doc")
endif()

add_subdirectory(include)

option(LMI_BUILD_TESTS "Build the Unit Tests" OFF)
if(LMI_BUILD_TESTS)
	if(EXISTS ${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake) #Clion, with conanbuildinfo.cmake in build folder
		include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
	else()
		include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) # Not CLion
	endif()

	conan_basic_setup()

	enable_testing()
	add_subdirectory(test)
endif()
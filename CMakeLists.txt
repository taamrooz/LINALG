# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (LINALG)

# Include sub-projects.
if(MSVC)
	set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2")
	find_package(SDL2 REQUIRED)

endif(MSVC)

set(INSTALL_DIR ${PROJECT_BINARY_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${INSTALL_DIR})

# Include sub-projects.
add_subdirectory(LINALG)

if(MSVC)
	list(GET SDL2_LIBRARIES 0 HEAD_SDL2_LIBRARIES)
	get_filename_component(SDL2_DLL_DIR ${HEAD_SDL2_LIBRARIES} DIRECTORY CACHE)
	file(GLOB SDL2_DLLS "${SDL2_DLL_DIR}/*.dll")

	add_custom_target(lib ALL
		COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_DLLS} ${INSTALL_DIR})
endif(MSVC)

# CMakeList.txt : CMake project for LINALG, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

if(MSVC)
	add_compile_options(/W3)
	if(NOT DEFINED SDL2_DIR)
		set(SDL2_DIR "C:/SDL2-2.0.10")
	endif()
	find_package(SDL2 REQUIRED)
else()
	include(FindPkgConfig)
	find_package(SDL2 REQUIRED)
	add_compile_options(-Wall -Wpedantic -Werror)
	add_compile_options("$<$<CONFIG:DEBUG>:-g>")
endif()

# Add source to this project's executable.
add_executable (LINALG
	src/main.cpp)

target_compile_features(LINALG PUBLIC cxx_std_17)
if (MSVC)
  set_target_properties(LINALG PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
endif()
target_link_libraries(LINALG PRIVATE 
	"${SDL2_LIBRARIES}"
)
target_include_directories(LINALG PUBLIC 
	src
	include
    "${SDL2_INCLUDE_DIRS}"
)
# TODO: Add tests and install targets if needed.

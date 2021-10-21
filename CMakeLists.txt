cmake_minimum_required(VERSION 3.10)

project(Sorting-Visualization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)

add_subdirectory(external)

include_directories(
	external/glfw-3.3.4/include/
	external/glm-0.9.9.7/
	.
)

# === Noise visualization ===
# add the executable
add_executable(noise
	noiseVisualization.cpp
	shaderLoader.cpp
	shaderLoader.h
	noise.cpp
	noise.h
)

target_link_libraries(noise
	${OPENGL_LIBRARY}
	glfw
	glad
)

# === Main program ===

# add the executable
add_executable(main
	main.cpp
	shaderLoader.cpp
	shaderLoader.h
	noise.cpp
	noise.h
	window.cpp
	window.h
	world.cpp
	world.h
	controls.cpp
	controls.h
)

target_link_libraries(main
	${OPENGL_LIBRARY}
	glfw
	glad
)

cmake_minimum_required(VERSION 3.10)
project(VoxelGameEngine)

set(CMAKE_CXX_STANDARD 17)

# Set vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE /mnt/c/Users/ASUS/Documents/GitHub/voxel_engine/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

# Include directories
include_directories(
    include 
    /mnt/c/Users/ASUS/Documents/GitHub/voxel_engine/vcpkg/installed/x64-linux/include
    /mnt/c/Users/ASUS/Documents/GitHub/voxel_engine/src/glad
)

# Add source files
file(GLOB SOURCES "src/*.cpp" "src/glad/glad.c")

# Find and link GLFW and GLEW
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} glfw GLEW::GLEW GL)
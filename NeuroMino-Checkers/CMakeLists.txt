cmake_minimum_required(VERSION 3.10)
project(GuiNN-Checkers VERSION 1.0.0 LANGUAGES C)

# Project description
set(PROJECT_DESCRIPTION "NeuroMino Checkers - A cross-platform checkers game built with C and SDL2")

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ============================================================================
# Find SDL2 Libraries
# ============================================================================

# Find required SDL2 libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Print SDL2 versions for debugging
message(STATUS "SDL2 version: ${SDL2_VERSION}")
message(STATUS "SDL2_image version: ${SDL2_IMAGE_VERSION}")
message(STATUS "SDL2_ttf version: ${SDL2_TTF_VERSION}")
message(STATUS "SDL2_mixer version: ${SDL2_MIXER_VERSION}")

# Include directories
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    includes
)

# Link directories
link_directories(
    ${SDL2_LIBRARY_DIRS}
    ${SDL2_IMAGE_LIBRARY_DIRS}
    ${SDL2_TTF_LIBRARY_DIRS}
    ${SDL2_MIXER_LIBRARY_DIRS}
)

# ============================================================================
# Source Files
# ============================================================================

# Main source directory
set(SOURCE_DIR src)

# Collect all source files recursively
file(GLOB_RECURSE SOURCE_FILES 
    "${SOURCE_DIR}/*.c"
)

# Collect all header files for dependencies
file(GLOB_RECURSE HEADER_FILES 
    "includes/*.h"
)

message(STATUS "Found source files:")
foreach(file ${SOURCE_FILES})
    message(STATUS "  ${file}")
endforeach()

# ============================================================================
# Executable
# ============================================================================

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# Platform-specific libraries
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} m)
elseif(APPLE)
    # macOS specific: link frameworks
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CARBON_LIBRARY Carbon)
    
    if(COCOA_LIBRARY)
        target_link_libraries(${PROJECT_NAME} ${COCOA_LIBRARY})
    endif()
    if(IOKIT_LIBRARY)
        target_link_libraries(${PROJECT_NAME} ${IOKIT_LIBRARY})
    endif()
    if(CARBON_LIBRARY)
        target_link_libraries(${PROJECT_NAME} ${CARBON_LIBRARY})
    endif()
    
    # Set bundle properties for macOS
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE ON
    )
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} shell32 user32 gdi32 winmm)
endif()

# ============================================================================
# Assets Copying
# ============================================================================

# Create a custom target to copy assets
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_SOURCE_DIR}/GuiNN-Checkers/assets 
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    COMMENT "Copying assets to build directory"
)

# Add dependency so assets are copied before building the executable
add_dependencies(${PROJECT_NAME} copy_assets)

# ============================================================================
# Compile Options
# ============================================================================

# Enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# Debug vs Release configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
    message(STATUS "Building in Debug mode with debug symbols")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O2)
    message(STATUS "Building in Release mode with optimizations")
endif()

# ============================================================================
# Install Targets (for packaging)
# ============================================================================

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)

install(DIRECTORY assets/
    DESTINATION bin
)

install(DIRECTORY docs/
    DESTINATION .
)

# ============================================================================
# Print Summary
# ============================================================================

message(STATUS "")
message(STATUS "==========================================")
message(STATUS "NeuroMino Checkers CMake Configuration Summary")
message(STATUS "==========================================")
message(STATUS "Project: ${PROJECT_NAME} ${PROJECT_VERSION}")
message(STATUS "C Standard: C11")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "SDL2 Found: ${SDL2_FOUND}")
message(STATUS "SDL2_image Found: ${SDL2_IMAGE_FOUND}")
message(STATUS "SDL2_ttf Found: ${SDL2_TTF_FOUND}")
message(STATUS "SDL2_mixer Found: ${SDL2_MIXER_FOUND}")
message(STATUS "Source Files: ${SOURCE_FILES}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "==========================================")
message(STATUS "")

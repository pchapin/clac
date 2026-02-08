cmake_minimum_required(VERSION 3.20)
project(Clac VERSION 0.1.0 LANGUAGES CXX)

# Set C++20 standard for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(
            /EHsc    # Enable exception handling.
            /W3
            /wd4668  # Disable undefined macro warnings.
            /wd4865  # Disable the enum underlying type warning.
            /wd5039  # potentially throwing function in extern "C".
            /wd5045  # Disable Spectre mitigation warnings.
    )
    # Suppress Microsoft's warnings about standard C functions (fopen, strcpy, etc.).
    # TODO: Consider replacing C-isms with C++ alternatives during future refactoring.
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add SpicaCpp subdirectory
add_subdirectory(SpicaCpp)

# Add Clac components in dependency order
add_subdirectory(ClacEntity)
add_subdirectory(ClacEngine)
add_subdirectory(ClacConsoleUI)

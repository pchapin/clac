# Collect all source files
file(GLOB UI_SOURCES "*.cpp")
file(GLOB UI_HEADERS "*.hpp")

# Create the executable
add_executable(clac ${UI_SOURCES} ${UI_HEADERS})

# Specify include directories
target_include_directories(clac
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link dependencies
target_link_libraries(clac
    PRIVATE
        ClacEngine
)
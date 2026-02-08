# Collect all source files
file(GLOB ENGINE_SOURCES "*.cpp")
file(GLOB ENGINE_HEADERS "*.hpp")

# Create the library
add_library(ClacEngine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# Specify include directories
target_include_directories(ClacEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link dependencies
target_link_libraries(ClacEngine
    PUBLIC
        ClacEntity
)
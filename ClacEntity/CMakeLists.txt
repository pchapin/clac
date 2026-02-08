# Collect all source files
file(GLOB ENTITY_SOURCES "*.cpp")
file(GLOB ENTITY_HEADERS "*.hpp")

# Create the library
add_library(ClacEntity STATIC ${ENTITY_SOURCES} ${ENTITY_HEADERS})

# Specify include directories
target_include_directories(ClacEntity
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link dependencies
target_link_libraries(ClacEntity
    PUBLIC
        spicacpp
)

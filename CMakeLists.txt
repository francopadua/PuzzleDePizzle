cmake_minimum_required(VERSION 3.15)

# Add compiler to use (MSVC, Clang, GCC)
# ???

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# The project
project(PuzzleDePizzle)

# C++ version to use
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add source files from src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
# NEEDED to change like this soon
# file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "Game/*.cpp")
# file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "Engine/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# Relevant directories
# No Engine and Game directory yet, 
target_include_directories(${PROJECT_NAME}
PRIVATE
    External/raylib/include
    src
)

# Raylib linking
target_link_directories(${PROJECT_NAME} PRIVATE External/raylib/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib winmm)

# Output to /build/bin
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/game.puzres"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources"
)


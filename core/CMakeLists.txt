cmake_minimum_required(VERSION 3.21)

project(LogicCore
    VERSION 1.0.0
    DESCRIPTION "Digital Logic Simulator"
    LANGUAGES C
)

# C Standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Export compilation database for tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(LOGICCORE_WARNINGS "Enable compiler warnings" ON)
option(LOGICCORE_WERROR "Treat warnings as errors" OFF)
option(LOGICCORE_TESTS "Enable unit tests" OFF)

# Discover source files
file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

if(NOT PROJECT_SOURCES)
    message(FATAL_ERROR "No C source files found in src/")
endif()

# Main executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/src"
)

# Compiler warnings
if(LOGICCORE_WARNINGS)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME}
            PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                -Wshadow
                -Wformat=2
        )

        if(LOGICCORE_WERROR)
            target_compile_options(${PROJECT_NAME}
                PRIVATE -Werror
            )
        endif()
    elseif(MSVC)
        target_compile_options(${PROJECT_NAME}
            PRIVATE /W4
        )

        if(LOGICCORE_WERROR)
            target_compile_options(${PROJECT_NAME}
                PRIVATE /WX
            )
        endif()
    endif()
endif()

# Output directory
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/bin"
)

# Tests
if(LOGICCORE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Status
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C standard: C${CMAKE_C_STANDARD}")
message(STATUS "Compiler: ${CMAKE_C_COMPILER_ID}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Source files: ${PROJECT_SOURCES}")

add_custom_target(run
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    USES_TERMINAL
    COMMENT "Building and running LogicCore..."
)
cmake_minimum_required(VERSION 3.15)
project(SortingVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(SortingVisualizer ${SOURCES})

target_link_libraries(SortingVisualizer
    sfml-graphics
    sfml-window
    sfml-system
)

add_custom_command(TARGET SortingVisualizer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:SortingVisualizer>/assets
)

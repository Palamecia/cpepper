project(src)

# Find Qt5 main components
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(PROJECT_DATA_DIR ../../../share)
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${PROJECT_INCLUDE_DIR})

add_subdirectory(lib)
add_subdirectory(bin)

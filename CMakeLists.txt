cmake_minimum_required(VERSION 3.8)
project(project_hse)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

# Include a library search using find_package()
# via REQUIRED, specify that libraries are required
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(src src/main.cpp src/menu.cpp src/scene.cpp)
add_executable(project_hse ${src})

# specify which libraries to connect
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
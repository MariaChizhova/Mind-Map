cmake_minimum_required(VERSION 3.10)
project(project_hse)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)

# Include a library search using find_package()
# via REQUIRED, specify that libraries are required
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Xml REQUIRED)

include_directories(include)

set(src src/main.cpp src/menu.cpp src/scene.cpp src/svgreader.cpp src/path.cpp src/sceneMenu.cpp)
add_executable(project_hse ${src} resources.qrc)

# specify which libraries to connect
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Svg)
target_link_libraries(${PROJECT_NAME} Qt5::Xml)
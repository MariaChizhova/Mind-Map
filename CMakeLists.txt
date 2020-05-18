cmake_minimum_required(VERSION 3.10)
project(project_hse)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Xml REQUIRED)

include_directories(include)

add_compile_options(-O2)

set(src src/main.cpp src/menu.cpp src/scene.cpp src/svgreader.cpp
        src/path.cpp src/sceneMenu.cpp src/svgsaver.cpp src/MainWindow.cpp)
add_executable(project_hse ${src} resources.qrc)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Svg Qt5::Xml)
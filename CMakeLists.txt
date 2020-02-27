cmake_minimum_required(VERSION 3.10)
project(project_hse)

set(CMAKE_CXX_STANDARD 17)

# Include a library search using find_package()
# via REQUIRED, specify that libraries are required
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(include)
set(src src/main.cpp src/menu.cpp src/scene.cpp)
add_executable(project_hse ${src})

# add icons
configure_file(icons/new.png COPYONLY)
configure_file(icons/open.png COPYONLY)
configure_file(icons/help.png COPYONLY)
configure_file(icons/quit.png COPYONLY)
configure_file(icons/color.png COPYONLY)
configure_file(icons/font.png COPYONLY)
configure_file(icons/save.png COPYONLY)

# specify which libraries to connect
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

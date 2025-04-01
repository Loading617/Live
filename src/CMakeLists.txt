cmake_minimum_required(VERSION 3.10)
project(Live)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Live src/main.cpp src/ui.cpp src/player.cpp)

target_include_directories(Live PRIVATE /path/to/elements /path/to/miniaudio)
target_link_libraries(offline-radio-app PRIVATE nlohmann_json::nlohmann_json)

find_package(nlohmann_json REQUIRED)

target_link_libraries(Live pthread)
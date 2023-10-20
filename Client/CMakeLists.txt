cmake_minimum_required(VERSION 3.5)
project(Client)
add_definitions(-Wall)
set(CMAKE_CXX_STANDARD 14)
set(sources main.cpp
	Client.cpp
)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} muduo_net muduo_base pthread)

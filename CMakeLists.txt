cmake_minimum_required(VERSION 2.8.3)
project(image_undistored)

find_package(OpenCV 3.2 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
   ${OpenCV_LIBRARIES}
 )


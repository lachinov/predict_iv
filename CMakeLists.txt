cmake_minimum_required(VERSION 2.7)
 
project(predict)

file(GLOB PREDICT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/
					${CMAKE_CURRENT_SOURCE_DIR}/Eigen/Eigen/)

add_executable(predict ${PREDICT_SOURCES})
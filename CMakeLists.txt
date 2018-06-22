cmake_minimum_required(VERSION 2.7)
 
project(predict)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/install/${CMAKE_GENERATOR_PLATFORM}/)

file(GLOB PREDICT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/
					${CMAKE_CURRENT_SOURCE_DIR}/Eigen/Eigen/)

add_executable(predict ${PREDICT_SOURCES})

install(TARGETS predict
        DESTINATION bin
)
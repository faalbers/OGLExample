cmake_minimum_required(VERSION 3.5)
project(OGLExample VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH C:/Qt/6.1.1/mingw81_64)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets OpenGLWidgets REQUIRED)
#find_package(Qt6 COMPONENTS Widgets OpenGLWidgets REQUIRED)

file(GLOB OGLEXAMPLE_TARGETS *.cpp )
add_executable(OGLExample ${OGLEXAMPLE_TARGETS})
target_link_libraries(OGLExample PRIVATE Qt6::Widgets Qt6::OpenGLWidgets)
target_include_directories(OGLExample PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

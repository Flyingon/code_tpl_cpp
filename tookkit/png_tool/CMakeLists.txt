cmake_minimum_required(VERSION 3.20)
project(png_tool)

set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/homebrew/Cellar/libpng/1.6.43/include)
link_directories(
        /opt/homebrew/Cellar/libpng/1.6.43/lib)
link_libraries(png)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(png-tool main.cpp)
target_link_libraries( png-tool ${OpenCV_LIBS} )
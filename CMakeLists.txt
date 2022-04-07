cmake_minimum_required(VERSION 3.20)
project(code_tpl_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(./)
include_directories(./dependencies/mysql/mysql)

link_directories(./)
link_directories(./dependencies/mysql-connector-c-6.1.11-winx64/lib)

add_executable(udp_listen socket/udp_listen.c)
add_executable(udp_client socket/udp_client.c)

add_executable(cls_tpl_v1 for_template/cls_tpl/cls_tpl_v1.cpp)

add_executable(base64 for_encode/base64/base64.cpp)

add_executable(globalenv for_env/global_env/global_env.cpp)

add_executable(mysql_connect for_mysql/mysql/connect.cpp)
TARGET_LINK_LIBRARIES(mysql_connect libmysql)
cmake_minimum_required(VERSION 3.20)
project(datastruct)

set(CMAKE_CXX_STANDARD 17)

# 获取当前目录下第一级子目录的名字列表
#file(GLOB SUBDIRECTORIES "${PROJECT_SOURCE_DIR}/datastruct/*")
file(GLOB SUBDIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/*")
#message("Proj[datastruct] SUBDIRECTORIES: " ${SUBDIRECTORIES})
foreach(SUBDIR ${SUBDIRECTORIES})
    if(IS_DIRECTORY ${SUBDIR})
        # 获取当前子目录的最后一级目录名（也就是想要作为可执行文件名的部分）
        get_filename_component(EXECUTABLE_NAME ${SUBDIR} NAME)
        # 为每个子目录下的源文件创建对应的可执行文件目标
        file(GLOB SOURCES_IN_SUBDIR "${SUBDIR}/*.cpp")
        if(SOURCES_IN_SUBDIR)
            add_executable(${EXECUTABLE_NAME} ${SOURCES_IN_SUBDIR})
        else()
            message(WARNING "No.cpp sources found in subdirectory: ${SUBDIR}")
        endif()
    endif()
endforeach()
cmake_minimum_required(VERSION 3.20)
project(code_tpl_cpp)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif (CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
    set(LINUX 1)
endif ()


include_directories(./)
include_directories(./dependencies/mysql/mysql)

link_directories(./)
link_directories(./dependencies/mysql-connector-c-6.1.11-winx64/lib)


add_executable(base64 for_encode/base64/base64.cpp)

add_executable(globalenv for_env/global_env/global_env.cpp)

add_executable(mysql_connect for_mysql/mysql/connect.cpp)
TARGET_LINK_LIBRARIES(mysql_connect libmysql)


# ------------------------- socket -------------------------
add_executable(tcp_listen socket/tcp_listen.c)
add_executable(tcp_client socket/tcp_client.c)
add_executable(udp_listen socket/udp_listen.c)
add_executable(udp_client socket/udp_client.c)

# ------------------------- for_network -------------------------


# ------------------------- epoll -------------------------
add_executable(reactor epoll/reactor.c)
add_executable(try_et_lt epoll/try_et_lt.c)

# ------------------------- for_memory -------------------------
# for_memory.for_align
add_executable(byte_align for_memory/for_align/byte_align.cpp)

# for_memory.for_size
add_executable(size for_memory/for_size/size.cpp)
add_executable(redis_size for_memory/for_size/redis.cpp)

# for_memory.show_memory
add_executable(show_memory_by_arrow for_memory/show_memory/use_arrow.cpp)

# ------------------------- for_array -------------------------
add_executable(array_traverse_ptr for_array/user_ptr/traversebyptr.cpp)

# --------------------------- for_hash ---------------------------
add_executable(lalian for_hash/lalian/lalian.cpp)

# --------------------------- toolkit ---------------------------
add_executable(gcp_attach_download tookkit/gen_gcp_cmd/attach_download.c)

# --------------------------- temp ---------------------------
add_executable(temp temp/temp.cpp)

# --------------------------- for_copy ---------------------------
add_executable(copy_constructor for_copy/constructor.cpp)


# --------------------------- for_glfw ---------------------------
if (WINDOWS)
    set(GLFW_PATH "D:/Develop/cpp_dependencies/glfw-3.3.8.bin.WIN64")

    include_directories("${GLFW_PATH}/include")

    # use lib
    target_link_libraries(temp "${GLFW_PATH}/lib-vc2019/glfw3.lib")

    # # use dll
    # target_link_libraries(temp "${GLFW_PATH}/lib-vc2019/glfw3dll.lib")
    # add_custom_command(TARGET  temp POST_BUILD        # Adds a post-build event to MyTest
    # COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
    #    "${GLFW_PATH}/lib-vc2019/glfw3.dll"      # <--this is in-file
    #    $<TARGET_FILE_DIR:temp>)                 # <--this is out-file path

elseif (LINUX)
elseif (MACOS)
endif ()

# --------------------------- const ---------------------------
add_executable(const_basic for_const/basic.cpp)

# --------------------------- for_template ---------------------------
add_executable(cls_tpl_v1 for_template/cls_tpl/cls_tpl_v1.cpp)
add_executable(func_tpl_print for_template/func_tpl/print.cpp)

# --------------------------- for_tree ---------------------------
add_executable(b+tree for_tree/bplus/basic.cpp)

# --------------------------- for_point ---------------------------
add_executable(func_point for_point/function/func_point.cpp)
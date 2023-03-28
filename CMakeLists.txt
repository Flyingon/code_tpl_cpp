cmake_minimum_required(VERSION 3.20)
project(code_tpl_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(./)
include_directories(./dependencies/mysql/mysql)

link_directories(./)
link_directories(./dependencies/mysql-connector-c-6.1.11-winx64/lib)


add_executable(cls_tpl_v1 for_template/cls_tpl/cls_tpl_v1.cpp)

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

# --------------------------- const ---------------------------
add_executable(const_basic for_const/basic.cpp)
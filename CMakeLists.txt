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


#include_directories(./)
#link_directories(./)


if (WINDOWS)
    include_directories(./dependencies/mysql/mysql)
    link_directories(./dependencies/mysql-connector-c-6.1.11-winx64/lib)
elseif (MACOS)
    include_directories(~/.dependencies/boost_1_82_0/)

endif ()

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

# for_memory.func_return_struct
add_executable(func_return_struct for_memory/func_return/struct.cpp)

# ------------------------- for_array -------------------------
add_executable(array_traverse_ptr for_array/user_ptr/traversebyptr.cpp)
add_executable(array_multi_basic for_array/multidimensional/basic.cpp)

# --------------------------- for_hash ---------------------------
add_executable(lalian for_hash/lalian/lalian.cpp)

# --------------------------- for_copy ---------------------------
add_executable(copy_constructor for_copy/constructor.cpp)

# --------------------------- for_string ---------------------------
add_executable(string_heap for_string/str_cls/str_on_heap.cc)
add_executable(string_join for_string/operator/join.cc)

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
add_executable(multi_type_vector for_template/vector/multi_type_vector.cpp)

# --------------------------- for_tree ---------------------------
add_executable(b+tree for_tree/bplus/basic.cpp)

# --------------------------- for_pointer ---------------------------
add_executable(func_pointer for_pointer/function/func_pointer.cpp)

# --------------------------- for_thread ---------------------------
add_executable(thread_basic for_thread/basic/basic.cpp)
add_executable(trhead_lock_demo1_unlock for_thread/lock/demo1.cpp)
add_executable(trhead_lock_demo2_lock for_thread/lock/demo2.cpp)
add_executable(trhead_lock_demo3_dead_lock for_thread/lock/demo3.cpp)
add_executable(trhead_lock_demo4_lock_guard for_thread/lock/demo4.cpp)

# --------------------------- for_chrono ---------------------------
add_executable(chrono_timer for_chrono/timer/timer.cpp)

# --------------------------- for_type ---------------------------
add_executable(type_punning for_type/type_punning/type_punning.cpp)

# --------------------------- for_union ---------------------------
add_executable(union_one for_union/example_one/example_one.cpp)

# --------------------------- for_move_semantic ---------------------------
add_executable(move_semantic_demo1 for_move_semantic/demo/basic.cpp)
add_executable(move_semantic_string for_move_semantic/demo/demo_string.cpp)

# --------------------------- for_db ---------------------------
if (TARGET sqlite_demo)
endif ()
if (MACOS)
    include_directories(
            /opt/homebrew/opt/sqlite/include
            /opt/homebrew/opt/sdl2/include
    )
    link_directories(
            /opt/homebrew/opt/sqlite/lib
            /opt/homebrew/opt/sdl2/lib
    )
    link_libraries(sqlite3 sdl2)
endif ()

add_executable(sqlite_demo for_db/for_sqlite3/demo.cpp)


# --------------------------- toolkit ---------------------------
add_executable(gcp_attach_download tookkit/gen_gcp_cmd/attach_download.c)

add_executable(memo_tool_record tookkit/memo_tool/record.cpp)
add_executable(memo_tool_show tookkit/memo_tool/show.cpp)
add_executable(memo_tool_update tookkit/memo_tool/update.cpp)

add_executable(cache_file tookkit/cache_file/cache_file.cpp)
add_executable(parserso tookkit/parseso/soparse.c tookkit/parseso/dataType.h tookkit/parseso/elf.h)


# --------------------------- for_pragma_once ---------------------------
include_directories(for_pragma_once/dir3 for_pragma_once/dir2)
add_executable(dir1_execute for_pragma_once/dir1/execute.cpp)

# --------------------------- for_sdl2 ---------------------------
add_executable(sdl2_text_input for_sdl2/text_input.cpp)

# --------------------------- temp ---------------------------
if (MACOS)
    include_directories(/opt/homebrew/opt/openssl/include /opt/homebrew/opt/jsoncpp/include)

    link_directories(/opt/homebrew/opt/jsoncpp/lib /opt/homebrew/opt/openssl/lib/ /opt/homebrew/opt/libiconv/lib/)
    #    link_directories(/opt/homebrew/opt/jsoncpp/lib /opt/homebrew/opt/openssl/lib/)
    #    link_libraries(/opt/homebrew/opt/openssl/lib/libcrypto.a)
    #    link_libraries(curl jsoncpp)
endif ()

add_executable(temp temp/temp.cpp)

add_subdirectory(tookkit/png_tool)

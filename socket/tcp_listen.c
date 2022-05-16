/* --- server.c --- */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define PORT 6000		//端口号
#define BACKLOG 5	//最大监听数

int main(int argc, char *argv[])
{
    int listen_fd = 0;  // socket句柄
    int conn_fd = 0;  //建立连接后的句柄
    struct sockaddr_in serv_addr;

    char send_buff[1024];  // 发送buf
    char recv_buff[1024];  // 接收buf
    time_t ticks;

//    struct sockaddr_in st_local_addr = {0}; //本地地址信息结构图，下面有具体的属性赋值
//    struct sockaddr_in st_remote_addr = {0}; //对方地址信息
    socklen_t socklen = 0;  // 收到消息长度
    int recv_len = 0;

    /* creates an UN-named socket inside the kernel and returns
     * an integer known as socket descriptor
     * This function takes domain/family as its first argument.
     * For Internet family of IPv4 addresses we use AF_INET
     */
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);  // 建立socket
    if(0 > listen_fd)
    {
        printf("创建socket失败！\n");
        return 0-1;
    }
    serv_addr.sin_family = AF_INET;  // 地址组，socket类型，IPv4用这个
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 监听地址: IP，括号内容表示本机IP
    serv_addr.sin_port = htons(PORT);  // 端口号

//    memset(&serv_addr, '0', sizeof(serv_addr));
//    memset(send_buff, '0', sizeof(send_buff));


    //绑定地址结构体和socket
    /* The call to the function "bind()" assigns the details specified
     * in the structure 『serv_addr' to the socket created in the step above
     */
    if (0 > bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
        printf("绑定失败！\n");
        return -1;
    }

    //开启监听 ，第二个参数是最大监听数
    /* The call to the function "listen()" with second argument as 10 specifies
     * maximum number of client connections that server will queue for this listening
     * socket.
     */
    if(0 > listen(listen_fd, BACKLOG))
    {
        printf("监听失败！\n");
        return -1;
    }

    printf("listen_fd: %d\n", listen_fd);

    //在这里阻塞知道接收到消息，参数分别是socket句柄，接收到的地址信息以及大小
    conn_fd = accept(listen_fd, (void *)&serv_addr, &socklen);
    if(0 > conn_fd)
    {
        printf("接收失败！\n");
        return -1;
    }else{
        printf("接收成功！\n");
        //发送内容，参数分别是连接句柄，内容，大小，其他信息（设为0即可）
        send(conn_fd, "这是服务器接收成功后发回的信息!", sizeof("这是服务器接收成功后发回的信息!"), 0);
    }

    printf("new conn_fd: %d\n", conn_fd);
    recv_len = recv(conn_fd, recv_buff, sizeof(recv_buff), 0);
    if(0 >= recv_len)    //对端关闭连接 返回0
    {
        printf("接收失败或者对端关闭连接！\n");
    }else{
        printf("buf: %s\n", recv_buff);
    }

    close(conn_fd);
    close(listen_fd);

//    // read接收
//    while(1)
//    {
//        /* In the call to accept(), the server is put to sleep and when for an incoming
//         * client request, the three way TCP handshake* is complete, the function accept()
//         * wakes up and returns the socket descriptor representing the client socket.
//         */
//        conn_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
//
//        while( (recv_len = read(conn_fd, recv_buff, sizeof(recv_buff)-1)) > 0)
//        {
//            printf("in second while loop\n");
//            recv_buff[recv_len] = 0;
//
//            fputs(recv_buff, stdout);
//        }
//
//        /* As soon as server gets a request from client, it prepares the date and time and
//         * writes on the client socket through the descriptor returned by accept()
//         */
//        ticks = time(NULL);
//        snprintf(send_buff, sizeof(send_buff), "%.24s\r\n", ctime(&ticks));
//        write(conn_fd, send_buff, strlen(send_buff));
//
//        close(conn_fd);
//        sleep(1);
//    }

    return 0;
}

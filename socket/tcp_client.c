/* --- client.c --- */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6000            //目标地址端口号
#define ADDR "127.0.0.1" //目标地址IP

int main(int argc, char *argv[]) {
    int sock_fd = 0; //socket句柄

    char recv_buff[1024];  // 存储接收到的数据
    struct sockaddr_in serv_addr;  // 对端，目标地址
    socklen_t socklen = 0;

    memset(recv_buff, '0', sizeof(recv_buff));

    /* a socket is created through call to socket() function */
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("创建socket失败！\n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // inet_pton 是一个IP地址转换函数，可以在将点分文本的IP地址转换为二进制网络字节序”的IP地址
    // 而且inet_pton和inet_ntop这2个函数能够处理ipv4和ipv6。
    // https://man7.org/linux/man-pages/man3/inet_pton.3.html
    if (inet_pton(AF_INET, ADDR, &serv_addr.sin_addr) <= 0) {
        printf("\n inet_pton error occured\n");
        return -1;
    }

    /* Information like IP address of the remote host and its port is
     * bundled up in a structure and a call to function connect() is made
     * which tries to connect this socket with the socket (IP address and port)
     * of the remote host
     */
    if (connect(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("连接失败！\n");
        return -1;
    } else {
        printf("连接成功！\n");
        recv(sock_fd, recv_buff, sizeof(recv_buff), 0); // 将接收数据打入buf，参数分别是句柄，储存处，最大长度，其他信息（设为0即可）
        printf("Received:%s\n", recv_buff);
    }

    close(sock_fd); //关闭socket

//    // read接收
//    /* Once the sockets are connected, the server sends the data (date+time)
//     * on clients socket through clients socket descriptor and client can read it
//     * through normal read call on the its socket descriptor.
//     */
//    while ((socklen = read(sock_fd, recv_buff, sizeof(recv_buff) - 1)) > 0) {
//        recv_buff[socklen] = 0;
//        if (fputs(recv_buff, stdout) == EOF) {
//            printf("\n Error : Fputs error\n");
//        }
//    }
//
//    if (socklen < 0) {
//        printf("\n Read error \n");
//    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
 // gcc socket_server_UDP.c -pthread -g -o socket_server_UDP
int main(void)
{
	int iRecvLen = 0;
	int iSocketFD = 0;
	int iRemotAddr = 0;
	char acBuf[4096] = {0};
	struct sockaddr_in stLocalAddr = {0};
 
	struct sockaddr_in stRemoteAddr = {0};
	socklen_t iRemoteAddrLen = 0;
 
	/* 创建socket */
	iSocketFD = socket(AF_INET, SOCK_DGRAM, 0);
	if(iSocketFD < 0)
	{
		printf("创建socket失败!\n");
		return 0;
	}
 
	/* 填写服务端地址 */
	stLocalAddr.sin_family = AF_INET;
	stLocalAddr.sin_port   = htons(12345);
	inet_pton(AF_INET, "192.168.1.230", (void *)&iRemotAddr);
	stLocalAddr.sin_addr.s_addr = iRemotAddr;
 
	iRecvLen = sendto(iSocketFD, "这是一个测试字符串", strlen("这是一个测试字符串"), 0, (void *)&stLocalAddr, sizeof(stLocalAddr));
 
 
	close(iSocketFD);
 
	return 0;
}

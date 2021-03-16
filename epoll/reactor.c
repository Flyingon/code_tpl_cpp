#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <fcntl.h>


#define MAX_EVENTS  (100) //最大的监听的个数
#define SER_PORT (6666)

typedef struct
{
	int fd ;//文件描述符
	int events;//事件
	void *args;
	void (*call_back)(int fd,int events,void *args);//事件回调函数，参数为上面三个
	int status; //0:没有添加到监听树;1:已添加到监听树
	char buff[1024]; //数据缓冲区
	int len;//数据长度
	long last_active;//上次的时间

}myevents_t;


myevents_t g_monitorEvs[MAX_EVENTS + 1];
int g_efd = -1;

int evtAdd(int efd,int events,myevents_t *p_evt);
int evtSet(myevents_t *p_evt,int fd, void (*call_back)(int fd,int events,void *args),void * arg);
int evtDel(int fd,myevents_t * p_evt);
void recvData(int fd,int events,void *args);

//发送给客户端数据
void sendData(int fd,int events,void *args)
{
	int ret = -1;

	myevents_t *p_evt = (myevents_t *)args;

	printf("p_evt ->len = %d\n",p_evt ->len);

	ret = send(fd, p_evt ->buff, p_evt ->len, 0);

	if(ret > 0)
	{
		printf("server send to client :%s\n",p_evt ->buff);
		//发送完数据之后，将fd从监听树中摘下，改为监听读事件,再放到监听树上去
		evtDel(fd,p_evt);
		evtSet(p_evt,fd, recvData,(void * )p_evt);
		evtAdd(g_efd,EPOLLIN,p_evt);

	}
	else
	{
		close(fd);
		evtDel(fd,p_evt);
	}

}


//读取客户端发过来的数据的函数
void recvData(int fd,int events,void *args)
{
	myevents_t *p_evt = (myevents_t *)args;

	memset(p_evt ->buff,0,1024);
	//读取客户端发过来的数据
	p_evt ->len = recv(fd, p_evt ->buff, 1024, 0);
	//将其从监听树中摘下
	evtDel(fd,p_evt);

	if(p_evt ->len  > 0)
	{
		printf("client send buffer:%s\n",p_evt ->buff);

		//再将此fd设置为监听写事件,再放到监听树上
		evtSet(p_evt,fd, sendData,(void * )p_evt);
		evtAdd(g_efd,EPOLLOUT,p_evt);
	}
	else
	{
		close(fd);
	}

}

//server跟client连接函数
void acceptConnection(int fd,int events,void *args)
{
	int cfd = -1;
	struct sockaddr_in cli_ip;
	socklen_t cli_ip_len = sizeof(cli_ip);
	char cli_ip_addr[16] = {0};
	int i = 0;
	int flag = -1;

	cfd = accept(fd, (struct sockaddr *)&cli_ip,&cli_ip_len);

	if(cfd > 0)
	{
		memset(cli_ip_addr,0,16);
		inet_ntop(AF_INET, &cli_ip.sin_addr.s_addr, cli_ip_addr, 16);
		printf("client connected,client ip addr:%s\n",cli_ip_addr);

		//查找没有加入到监听树中的数组节点
		for(i = 0;i < MAX_EVENTS;i ++)
		{
			if(g_monitorEvs[i].status == 0)
				break;
		}

		if(i >= MAX_EVENTS)
		{
			printf("%s:g_monitorEvs if full \n",__FUNCTION__);
			return;
		}
		//将连接的cfd设置成非阻塞模式
		flag = fcntl(cfd, F_GETFL);
		flag |= O_NONBLOCK;
		fcntl(cfd, F_SETFL, flag);

		//找到合适的节点之后，将其添加到监听树中，并监听读事件
		evtSet(&g_monitorEvs[i],cfd, recvData,(void *) &g_monitorEvs[i]);
		evtAdd(g_efd,EPOLLIN,&g_monitorEvs[i]);
	}


}
//初始化myevents_t 类型的一个变量
int evtSet(myevents_t *p_evt,int fd, void (*call_back)(int fd,int events,void *args),void * arg)
{
	p_evt ->fd = fd;
	p_evt ->events = 0;
	p_evt ->args = arg;
	p_evt ->call_back = call_back;
	p_evt ->status = 0;
	//memset(p_evt ->buff,0,1024);
	//p_evt ->len = 0;
	p_evt ->last_active = time(NULL);

	return 0;

}
//将fd添加到监听树上，设置监听事件并设置相应的回调函数，和参数
int evtAdd(int efd,int events,myevents_t *p_evt)
{
	struct epoll_event ep_evt;
	int ret = -1;
	int op;

	memset(&ep_evt,0,sizeof(ep_evt));
	ep_evt.events = events; //设置相应的监听事件
	p_evt ->events = events;//监听数组中的元素也要设置
	ep_evt.data.ptr = (void *)p_evt; //这里将myevents_t 类型的结构体给了ptr指针
	                                 //这里应该就是epoll反应堆的精髓了
	if(1 == p_evt ->status)//监听树中已经有了这个fd
	{
		op = EPOLL_CTL_MOD; //EPOLL_CTL_MOD，linux中man手册的解释是Change  the event event associated with the target file descrip‐
                            //tor fd,应该就是只更新这个fd对应的监听事件
	}else//监听树中没有这个fd
	{
		op = EPOLL_CTL_ADD;
		p_evt ->status = 1; //status 置1
	}

	ret = epoll_ctl(efd, op, p_evt ->fd, &ep_evt);
	if(ret < 0)
	{
		printf("%s:epoll_ctl error\n",__FUNCTION__);
		return -1;
	}

	return 0;

}

int evtDel(int fd,myevents_t* p_evt)
{
	int op = EPOLL_CTL_DEL;
	int ret = -1;
	struct epoll_event ep_evt;

	//如果fd没有添加到监听树上，就不用删除，直接返回
	if(p_evt ->status == 0)
	{
		return 0;
	}
	//如果fd在监听树上
	p_evt ->status = 0;
	ep_evt.data.ptr = (void *)p_evt;

	ret = epoll_ctl(g_efd,op,fd, &ep_evt);
	if(ret < 0)
	{
		printf("%s:epoll_ctl error\n",__FUNCTION__);

		return -1;
	}

	return 0;
}

//初始化监听lfd，并将lfd添加到监听树上去
int lfdInit(int efd,myevents_t * p_evt)
{
	int lfd = -1;
	struct sockaddr_in ser_ip;

	//创建监听lfd
	lfd = socket(AF_INET,SOCK_STREAM,0);

	memset(&ser_ip,0,sizeof(struct sockaddr_in));
	ser_ip.sin_family = AF_INET;
	ser_ip.sin_port = htons(SER_PORT);
	ser_ip.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(lfd, (const struct sockaddr*)&ser_ip,sizeof(ser_ip));
	listen(lfd, 20);

	//设置端口复用
	int opt = 1;// 1:设置端口复用，0：设置端口不复用
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR,&opt, sizeof(opt));

	//初始化g_monitorEvs[MAX_EVENTS],并设置回调
	evtSet(p_evt,lfd, acceptConnection,(void *) p_evt);
	//将lfd添加到监听树上，监听读事件
	evtAdd(g_efd,EPOLLIN,p_evt);
}

int main(void)
{
	int ret = -1;
	int ep_wait_nums = -1;
	int i = 0;

	//创建监听树
	g_efd = epoll_create(MAX_EVENTS);
	if(g_efd < 0)
	{
		printf("epoll_create error\n");
	}

	//初始化监听lfd
	//将g_monitorEvs[MAX_EVENTS]作为监听连接的数组节点
	ret = lfdInit(g_efd,&g_monitorEvs[MAX_EVENTS]);

	//定义这个结构体数组，用来接收epoll_wait传出的满足监听事件的fd结构体
	struct epoll_event ep_evt[MAX_EVENTS];
	myevents_t *p_evt;

	while(1)
	{
		//调用eppoll_wait等待接入的客户端事件,再次声明,epoll_wait传出的是满足监听条件的那些fd的struct epoll_event
		//类型
		ep_wait_nums = epoll_wait(g_efd, ep_evt,MAX_EVENTS, -1);
		if(ep_wait_nums > 0)
		{
			for(i = 0;i < ep_wait_nums;i ++)
			{
				//注意这里了，epoll反应堆精髓部分
				//evtAdd()函数中，添加到监听树中监听事件的时候将myevents_t结构体类型给了ptr指针
				//这里epoll_wait返回的时候，同样会返回对应fd的myevents_t类型的指针
				p_evt = ( myevents_t *)ep_evt[i].data.ptr;
				if(NULL != p_evt)
				{
					//如果监听的是读事件，并返回的是读事件
					if((p_evt ->events & EPOLLIN)&&(ep_evt[i].events & EPOLLIN))
					{
						p_evt ->call_back(p_evt ->fd,ep_evt[i].events,p_evt ->args);
					}
					//如果监听的是写事件，并返回的是写事件
					if((p_evt ->events & EPOLLOUT)&&(ep_evt[i].events & EPOLLOUT))
					{
						p_evt ->call_back(p_evt ->fd,ep_evt[i].events,p_evt ->args);
					}
				}
			}
		}



	}

	return 0;
}
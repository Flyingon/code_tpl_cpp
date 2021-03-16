#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <string.h>

#define MAXLEN (10)

char w_buf[MAXLEN];
char r_buf[MAXLEN];
char ch = 'a';




/*pipe创建一个管道，fork创建子进程，子进程往管道中写数据，父进程从管道中读数据
 *子进程每次发10个字节的数据，然后延时5s，父进程每次收5个字节的数据，
 *当设置为ET模式时，因为边缘触发只有数据到来才触发，不管缓存区中是否还有数据，这样父进程每个
 *5s内只会收到5个字节数据，当下个5s到来时，父进程才会收到上个5s子进程发的10个字节中的剩余5个字节数据。
 *当设置为LT模式时，默认情况下就是这个模式，只要有数据都会触发，所以每次5s中都会将缓冲区中的数据
 *读完，即都会将10个Bytes的数据读完。
 *
 */
int main(void)
{
	pid_t pid;
	int pipefd[2] = {-1,-1};
	int ret = -1;

	ret = pipe(pipefd); //创建管道成功后，pipefd[0]为读端，pipefd[1]为管道的写入端
	printf("pipefd[0] = %d, pipefd[1] = %d\n",pipefd[0],pipefd[1]);
	if(ret < 0)
	{
		printf("pipe error\n");

		return -1;
	}
	pid = fork();

	if(0 == pid)//子进程
	{
		int i = 0;

		close(pipefd[0]);

		printf(" clid process\n");
		while(1)
		{
			for(i = 0;i < MAXLEN/2;i ++)
			{
				w_buf[i] = ch;
			}
			w_buf[i-1] = '\n';

			ch++;

			for(;i < MAXLEN; i++)
			{
				w_buf[i] = ch;
			}
			w_buf[i-1] = '\n';       //即把w_buf构造成"aaaa\nbbbb\n"这种格式
			ch ++;

			//printf("before write buffer:%s\n",w_buf);
			write(pipefd[1], w_buf, sizeof(w_buf));//即一次写10个Bytes

			printf("write buffer:%s\n",w_buf);
			sleep(5);
			//printf("clid send buffer\n ");

		}
		close(pipefd[1]);

	}else if(pid > 0)//父进程
	{
		sleep(1);
		struct epoll_event lepevt; //listen epoll event
		struct epoll_event ep_set[10];
		int ep_nums = -1;
		int i = 0;

		close(pipefd[1]);
		//创建一个监听树，监听树的最大节点设为50
		int efd = epoll_create(10);
		if(efd < 0)
		{
			printf("epoll_create error \n");

			return -1;
		}

		lepevt.events = EPOLLIN | EPOLLET ;//ET模式，即边缘触发只有数据到来才触发，不管缓存区中是否还有数据
		//lepevt.events = EPOLLIN; //LT模式，水平触发，默认就是LT模式，只要有数据都会触发
		lepevt.data.fd = pipefd[0];

		//将监听读事件添加到监听树上
		epoll_ctl(efd, EPOLL_CTL_ADD, pipefd[0], &lepevt);

		printf(" parents process\n");
		while(1)
		{
			//阻塞监听事件
			ep_nums = epoll_wait(efd, ep_set,10, -1);

			printf("ep_nums = %d\n",ep_nums);
			if(ep_nums > 0)
			{
				for(i = 0;i < ep_nums;i ++)
				{
					//如果监听到读端的数据
					if(ep_set[0].data.fd == pipefd[0])
					{
						//每次读5个Bytes的数据
						ret = read(pipefd[0], r_buf, MAXLEN/2);

						//printf("ret = %d\n",ret);

						if(ret > 0)
						{
							//write(STDOUT_FILENO,r_buf,ret);
							printf("receive buffer: %s\n",r_buf);
							memset(r_buf,0,sizeof(r_buf));
						}
						else
						{
							printf("read null\n");
						}
						break;


					}
				}
			}

		}

		close(pipefd[0]);
		close(efd);

	}





	return 0;
}
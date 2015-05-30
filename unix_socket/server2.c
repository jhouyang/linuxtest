#include <sys/un.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>

#define MAX_RECV 1025
#define UNIX_SERV_PATH "/tmp/sinfor"
void client_dump(int sock_fd)
{
	char rec[MAX_RECV] = {0};
	int size;
	while((size = read(sock_fd, rec, MAX_RECV)) != 0)
	{
		printf("**********1111************\n");
		printf("recv data is %s\n", rec);
		write(sock_fd, rec, size);
	}
}
void sig_son(int num)
{
	printf("son is %d\n", getpid());
	wait(NULL);
	//return NULL;
}
int main(int argc, char** argv)
{
	int acc_sock, dump_sock;
	acc_sock = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(acc_sock == -1)
	{
		perror("socket func fail ");
		return -1;
	}
	struct sockaddr_un ser_addr, cli_addr;
	ser_addr.sun_family = AF_LOCAL;
	strcpy(ser_addr.sun_path, UNIX_SERV_PATH);
	unlink(UNIX_SERV_PATH);
	bind(acc_sock, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	listen(acc_sock, 5);
	signal(SIGCHLD, sig_son);
	while(1)
	{
		int len = sizeof(cli_addr);
		dump_sock = accept(acc_sock, (struct sockaddr*)&cli_addr, &len);
		if(dump_sock == -1)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				perror("accept fail");
				return -1;
			}
		}
		if(fork() == 0)
		{
			close(acc_sock);
			client_dump(dump_sock);     
			close(dump_sock);
			exit(0);
		}
		close(dump_sock);
	}
	close(acc_sock);
	return 0;
}

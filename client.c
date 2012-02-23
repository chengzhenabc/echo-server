#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
void main(int argc,char **argv)
{
	if(argc!=2)
	{
		return ;
	}
	int fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int sz_sin=sizeof(struct sockaddr_in);
	char recvbuf[100];
	char sendbuf[100];
	if(-1==(fd=socket(AF_INET,SOCK_STREAM,0)))
		return ;
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(atoi(argv[1]));
	connect(fd,(struct sockaddr*)(&server_addr),sizeof(struct sockaddr));
	
	while(1)
	{
		printf("input:");
		gets(sendbuf);
		write(fd,sendbuf,strlen(sendbuf)+1);
		if(!strncmp(sendbuf,"q",1))
			exit(1);
		read(fd,recvbuf,100);
		if(!strncmp(recvbuf,"q",1))
			exit(1);
		printf("server:%s\n",recvbuf);
	}
	close(fd);
}

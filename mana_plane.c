#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc, char **argv)
{
	int i = 0;
	char w;
 	char sebuff[5];
	char recvbuff[100];
	int  sockfd;
	struct sockaddr_in serveraddr;
	if (argc != 2) 
	{
		printf("usage:echo ip");
		exit(0);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(4114);
	inet_pton(AF_INET, argv[1], &serveraddr.sin_addr);
	connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	recv(sockfd, recvbuff, sizeof(recvbuff), 0);
	printf("%s\n", recvbuff);
	printf("please input the message:\n");
	printf("please input the 'a' to add the module.\n");
	printf("please input the 'c' close the WEB servers.\n");
	printf("please input the 'o' open the WEB servers.\n");
	printf("please input the 'f' filter the ICMP packet.\n");
	printf("please input the 'i' accept the ICMP packet.\n");
	printf("please input the 't' close the FTP servers.\n");
	printf("please input the 'p' start the FTP servers.\n");
	printf("please input the 'r' rmmod the all modules.\n");
	
	scanf("%c",&w);


	while (w != 'q')
	{
		sebuff[0] = w;
		send(sockfd, sebuff, 1, 0);
		scanf("%c",&w);
		switch(w)
		{
			case'a':
				printf("start the module.\n");break;
			case'b':
				printf("pause the connect.\n");break;
			case'c':
				printf("start close the WEB server.\n");break;
			case'o':
				printf("start open the WEB server.\n");break;
			case'f':
				printf("start filter the ICMP packet.\n");break;
			case'i':
				printf("start receive the ICMP packet.\n");break;
			case't':
				printf("start close the FTP servers.\n");break;
			case'p':
				printf("start open the FTP servers.\n");break;
			case'z':
				printf("test.\n");break;
			case'r':
				printf("rmmod the control modules.\n");break;
			default:
				printf("------------------------.\n");
		}
	}
close(sockfd);
}

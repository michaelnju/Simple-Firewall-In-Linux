#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	char temp;
	int a;
	char resbuff[5];
	int listensock, connsock;
	struct sockaddr_in serveraddr;
	const char buff[] = "hello\r\n";
	listensock = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(4114);
	bind(listensock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	listen(listensock, 1024);
	connsock = accept(listensock, (struct sockaddr*)NULL, NULL);
	send(connsock, buff, sizeof(buff), 0);
	recv(connsock, resbuff, 1, 0);
	printf("%c\n", resbuff[0]);
	while(resbuff[0]!='q')
	{
		switch(resbuff[0])
		{
			case'a':
				printf("start the control module.\n");
				system("gcc -O2 -g -Wall -DMODULE -D__KERNEL__ -I/usr/src/linux-headers-3.11.0-12/include  -c icmp_ctrl.c");
				system("gcc -O2 -g -Wall -DMODULE -D_KERNEL_ -I/usr/src/linux-headers-3.11.0-12/include -c ftp_ctrl.c");
				system("gcc -O2 -g -Wall -DMODULE -D__KERNEL__ -I/usr/src/linux-headers-3.11.0-12/include -c http_ctrl.c");
				break;
			case'b':
				printf("connect out.\n");
				recv(connsock, resbuff, 1, 0);
				while(resbuff[0]!='1')
				{
					printf("connect out.\n");
					recv(connsock,resbuff,1,0);
				}
				break;
			case'c':
				printf("close the 80 source port.\n");
				system("insmod ./nrgcc.o >log1");
				break;

			case'o':
				printf("open the 80 source port.\n");
				system("rmmod nrgcc >log3");
				break;

			case'f':
				printf("filter the ICMP packet.\n");
				system("insmod ./lgcc.o >log2");
				break;

			case'i':
				printf("accept the ICMP packet.\n");
				system("rmmod lgcc >log4");
				break;

			case't':
				printf("close the FTP servers.\n");
				system("insmod ./nrgccf.o >log5");
				break;

			case'p':
				printf("start the FTP servers.\n");
				system("rmmod nrgccf >log6");
				break;

			case'z':
				printf("connect test.\n");
				break;

			case'r':
				printf("all the control module has rmmod.\n");
				system("rmmod nrgcc >log7");
				system("rmmod nrgccf >log8");
				system("rmmod lgcc >log9");
				break;

			default:
				printf("---------------------.\n");
				break;
		}
		recv(connsock, resbuff, 1, 0);
	}
	close(connsock);
	close(listensock);
}

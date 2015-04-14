//ID : 20133242
//NAME : DOONA LEE
//2015.4.8
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUFF_SIZE 1024


int main(int argc, char *argv[])
{
//argument setup--------------------------------------------------------------
	struct sockaddr_in server, remote;
	int request_sock, new_sock;
	int bytesread, addrlen;
	int i;
	char buf[BUFSIZ];

	if(argc != 2) {
		(void) fprintf(stderr, "usage: %s port\n", argv[0]);
		exit(1);
	}

//socket()--------------------------------------------------------------------
	if((request_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		perror("socket");
		exit(1);
	}

//bind()----------------------------------------------------------------------
	memset((void*)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port=htons((u_short)atoi(argv[1]));

	if(bind(request_sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		perror("bind");
		exit(1);
	}

//listen()------------------------------------------------------------------------------
	if(listen(request_sock, SOMAXCONN) < 0) {
		perror("listen");
		exit(1);
	}

//accept()------------------------------------------------------------------------------
	for(;;) {
		//duna
		int totalBuf = 0;
		char sTotalBuf[50];

		addrlen = sizeof(remote);
		new_sock = accept(request_sock, (struct sockaddr*)&remote, &addrlen);
		if(new_sock < 0) {
			perror("accept");
			exit(1);
		}
		printf("connection from host %s, prot %d, socket %d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port), new_sock);
	
	//sending&receiving------------------------------------------------------------
		for(;;) {

		bytesread = read(new_sock, buf, sizeof(buf) - 1);
		totalBuf += atoi(buf);

			if(bytesread<=0) {
				printf("server: end of file on %d\n", new_sock);
				if(close(new_sock))
					perror("close");
				break;
			}
		buf[bytesread] = '\0';
		printf("%s: %d bytes from %d: %d\n", argv[0], bytesread, new_sock, totalBuf);
		
			for(i=0; i<bytesread; ++i)
				buf[i] = toupper(buf[i]);
		/*echo it back*/
		//return adder result
		sprintf(sTotalBuf, "%d", totalBuf);
		write(new_sock, sTotalBuf, bytesread);
		//++index;

		//itoa(totalBuf, sTotalBuf, 10)
		}
	}
}

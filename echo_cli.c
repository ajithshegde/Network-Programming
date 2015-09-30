#include "unp.h"

int main(int argc,char** argv){
	int sockfd;
	struct sockaddr_in servaddr;
	char rcvline[MAXLINE],sndline[MAXLINE];
	int pf;
	char buf[100],last[100];
	strcpy(buf,"Echo input given");	
	strcpy(last,"Child terminated");	
	pf = atoi(argv[2]);
	if(argc <3)
		err_quit("usage:tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(14087);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	Connect(sockfd,(SA*) &servaddr, sizeof(servaddr));

	for( ; ; ){
		while( Fgets(sndline,MAXLINE,stdin) != NULL ){
			Writen(sockfd, sndline, strlen(sndline));
			write(pf,buf,strlen(buf)+1);
			if(Readline(sockfd, rcvline, MAXLINE) == 0){
				write(pf,last,strlen(last)+1);
				err_quit("server terminated");
			}
			Fputs(rcvline,stdout);
		}

	}

	/*	char in_str[100];
		for( ; ;){
		scanf("%s",in_str);
		printf("%s\n",in_str);
	//write(pfd[1], in_str,strlen(in_str)+1);
	}*/

	return 0;
}

#include "unpthread.h"
#include	"unp.h"
#include	<time.h>
#include "errno.h"


static void* time_exe(void *arg){

	char                            buff[MAXLINE];
	int n;
	time_t                          ticks;
	int i=15,x;
	int det,maxfdp;
	fd_set eset,wset;
	struct timeval tv;
	printf("Time Client requested service\n");

	det=pthread_detach(pthread_self());	


	tv.tv_sec = 5;
	tv.tv_usec = 0;
	maxfdp = (int)arg +1;

	for( ; ; ){
		FD_ZERO(&eset);
		FD_ZERO(&wset);
		FD_SET((int)arg,&eset);
		FD_SET((int)arg,&wset);

		x=select(maxfdp,&eset,NULL,NULL,&tv);
		//	printf("%d \n",x);
		if(x > 0){
			printf("Time Client terminated with errno %d\n",errno);
			break;
		}

//	for( ; ; ){
	for( ; ; ){
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

		select(maxfdp,NULL,&wset,NULL,NULL);
		if((n=write((int)arg, buff, strlen(buff))) <= 0){
			printf("Stopping\n");
			break;
		}


		memset(buff,0,sizeof(buff));


		FD_CLR((int)arg,&eset);
	}
	Close((int)arg);


	//printf("Error in client side\n");

	return (NULL);

}

static void* echo_exe(void* arg){


	char buff_e[MAXLINE];
	int j=15;
	int dete,n;

	printf("Echo Client requested service\n");

	dete=pthread_detach(pthread_self());

	for( ; ; ){	

		if( (n = readline((int)arg,buff_e,MAXLINE)) <= 0){
			printf("Echo Client terminated with errno %d \n",errno);
			break;
		}
		writen((int)arg,buff_e,strlen(buff_e));
		memset(buff_e,0,sizeof(buff_e));
	}	


	Close((int)arg);


	return (NULL);
} 

	int
main(int argc, char **argv)
{
	int                        listenfd, connfd;
	struct sockaddr_in      servaddr;
	char                            buff[MAXLINE];
	int                        listenfd_e, connfd_e;
	struct sockaddr_in      servaddr_e,cliaddr;
	char buff_e[MAXLINE];
	int i=10,j=10;
	int maxfdp;
	fd_set rset;
	socklen_t clilen;


	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR,(char*)&i,sizeof(int));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(14086);        /* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);



	listenfd_e = Socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listenfd_e, SOL_SOCKET,SO_REUSEADDR,(char*)&j,sizeof(int));

	bzero(&servaddr_e, sizeof(servaddr_e));
	servaddr_e.sin_family      = AF_INET;
	servaddr_e.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr_e.sin_port        = htons(14087);

	Bind(listenfd_e, (SA *) &servaddr_e, sizeof(servaddr_e));

	Listen(listenfd_e, LISTENQ);

	FD_ZERO(&rset);



	for( ; ; ){
		FD_ZERO(&rset);

		FD_SET(listenfd_e,&rset);
		FD_SET(listenfd,&rset);

		
		maxfdp = max(listenfd_e,listenfd)+1;
		Select(maxfdp, &rset, NULL, NULL, NULL);

		if(FD_ISSET(listenfd_e,&rset)){
			clilen = sizeof(cliaddr);
			connfd_e = Accept(listenfd_e,(SA*) &cliaddr, &clilen);
			pthread_create(NULL, NULL,echo_exe, (void *)connfd_e);

		}


		if(FD_ISSET(listenfd,&rset)){
			connfd = Accept(listenfd, (SA *) NULL, NULL);
			pthread_create(NULL, NULL,time_exe, (void *)connfd);
		}

		FD_CLR(listenfd_e,&rset);

		FD_CLR(listenfd,&rset);

	}

}



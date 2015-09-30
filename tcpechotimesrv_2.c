#include "unpthread.h"
#include	"unp.h"
#include	<time.h>

void str_echo(int);

static void* time_exe(void *arg){

	char                            buff[MAXLINE];

	time_t                          ticks;
	int i=15;
	int det;
	printf("Time Thread created\n");

	det=pthread_detach(pthread_self());	
	printf("Time Thread detached %d\n",det);


	for( ; ; ){
	for( ; ; ){
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		Write((int)arg, buff, strlen(buff));
			//fprintf(stdout,"%s","Error in client side");
		
		sleep(5);

	}
	Close((int)arg);
	break;
}
	//printf("Error in client side\n");



	return (NULL);

}

static void* echo_exe(void* arg){


	char buff_e[MAXLINE];

	int j=15;
	int dete,n;
//	int conn;


	printf("Echo Thread created\n");
	
	dete=pthread_detach(pthread_self());
	printf("Echo Thread detached %d\n",dete);
//	conn = *((int *)arg);
//	free(arg);
	//for( ; ;){
	//	connfd_e = Accept(listenfd_e,(SA*) NULL, NULL);
	for( ; ; ){	

		if( (n = readline((int)arg,buff_e,MAXLINE)) == 0){
			break;
		}
		writen((int)arg,buff_e,strlen(buff_e));
		memset(buff_e,0,sizeof(buff_e));
	}	

//	str_echo(conn);
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
	//pthread_t thread_time,thread_echo;
	int i=10,j=10;
	//int maxfdp_t,maxfdp_e;
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

		//maxfdp_e = listenfd_e+1;
		maxfdp = max(listenfd_e,listenfd)+1;
		Select(maxfdp, &rset, NULL, NULL, NULL);

		 if(FD_ISSET(listenfd_e,&rset)){
			clilen = sizeof(cliaddr);
                        connfd_e = Accept(listenfd_e,(SA*) &cliaddr, &clilen);
                        pthread_create(NULL, NULL,echo_exe, (void *)connfd_e);

                }

			
		
		//maxfdp_t = listenfd+1;
		//Select(maxfdp_t, &wset_t, NULL, NULL, NULL);

		if(FD_ISSET(listenfd,&rset)){
			connfd = Accept(listenfd, (SA *) NULL, NULL);
			pthread_create(NULL, NULL,time_exe, (void *)connfd);

		}
		
		FD_CLR(listenfd_e,&rset);
		FD_CLR(listenfd,&rset);
	}


	//	pthread_t thread_time,thread_echo;
	//pthread_attr_t time_attr;
	//	int tt,te;

	//tc = pthread_attr_init(&time_attr);
	//pthread_create(&thread_echo, NULL,echo_exe, NULL);

	//pthread_create(&thread_time, NULL,time_exe, NULL);
	//	te = pthread_create(&thread_echo, NULL,echo_exe, NULL);
	//printf("tc = %d\n",tc);	
	//pthread_exit(NULL);

	//time_exe();
}

/*void str_echo(int sockfd){
char line[MAXLINE];
ssize_t n;

for( ; ; ){
        // bzero(&servaddr_e, sizeof(servaddr_e));

        if( (n = Readline(sockfd,line,MAXLINE)) == 0){
                return;}

        Writen(sockfd,line,n);

}


}*/


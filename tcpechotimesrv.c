#include "unpthread.h"
#include	"unp.h"
#include	<time.h>

void* time_exe(){

	int                        listenfd, connfd;
	struct sockaddr_in      servaddr;
	char                            buff[MAXLINE];
	time_t                          ticks;
	int i=15;
	//	pthread_attr_t time_attr;
	//	
	//	pthread_attr_init(&time_attr);
	printf("Thread created\n");

	Pthread_detach(pthread_self());	
	printf("Thread detached\n");
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR,(char*)&i,sizeof(int));	

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(14086);        /* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);
	connfd = Accept(listenfd, (SA *) NULL, NULL);

	for ( ; ; ) {


		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		if(write(connfd, buff, strlen(buff)) < 0){
			//fprintf(stdout,"%s","Error in client side");
			break;
		}
		sleep(5);


		
	}
	printf("Error in client side\n");

	Close(connfd);

	return (NULL);

}

	int
main(int argc, char **argv)
{
	pthread_t thread_time;
	//pthread_attr_t time_attr;
	int tc;

	//tc = pthread_attr_init(&time_attr);
	tc = pthread_create(&thread_time, NULL,time_exe, NULL);
	printf("tc = %d\n",tc);	
	pthread_exit(NULL);

	//time_exe();


}

#include "unpthread.h"
#include	"unp.h"
#include	<time.h>

void* time_exe(){

	int                        listenfd, connfd;
	struct sockaddr_in      servaddr;
	char                            buff[MAXLINE];
	time_t                          ticks;
	int i;
	pthread_attr_t time_attr;
	
	tc = pthread_attr_init(&time_attr);
	printf("Thread created\n");
	
	Pthread_detach(pthread_self());	
	printf("Thread detached\n");
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);


	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(14086);        /* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		for(i=0;i<5;i++){
			ticks = time(NULL);
			snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
			Write(connfd, buff, strlen(buff));
			sleep(5);
		}
		Close(connfd);
	}
	return (NULL);

}

	int
main(int argc, char **argv)
{
	pthread_t thread_t;
	//pthread_attr_t time_attr;
	int tc;

	//tc = pthread_attr_init(&time_attr);
	tc = pthread_create(&thread_t, NULL,time_exe, NULL);
	//time_exe();


}

#include "unpthread.h"
#include	"unp.h"
#include	<time.h>

void time_exe(){

	 int                        listenfd, connfd;
        struct sockaddr_in      servaddr;
        char                            buff[MAXLINE];
        time_t                          ticks;
        int i;
        
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


}

int
main(int argc, char **argv)
{

time_exe();


}

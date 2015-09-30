#include "unp.h"

int main(int argc,char** argv){
int                        listenfd_e, connfd_e;
        struct sockaddr_in      servaddr_e;
        char buff_e[MAXLINE];

        int j=15,n;
//        int dete,n;
  //      printf("Echo Thread created\n");

    //    dete=pthread_detach(pthread_self());
      //  printf("Echo Thread detached %d\n",dete);
        listenfd_e = Socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(listenfd_e, SOL_SOCKET,SO_REUSEADDR,(char*)&j,sizeof(int));

        bzero(&servaddr_e, sizeof(servaddr_e));
        servaddr_e.sin_family      = AF_INET;
        servaddr_e.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr_e.sin_port        = htons(14087);

        Bind(listenfd_e, (SA *) &servaddr_e, sizeof(servaddr_e));

        Listen(listenfd_e, LISTENQ);

        for( ; ;){
                connfd_e = Accept(listenfd_e,(SA*) NULL, NULL);
        for( ; ; ){
	 bzero(&servaddr_e, sizeof(servaddr_e));

        if( (n = Readline(connfd_e,buff_e,MAXLINE)) == 0)
                break;
        Writen(connfd_e,buff_e,MAXLINE);

}
        Close(connfd_e);
        break;
}
        return 0;





}

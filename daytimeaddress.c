#include	"unp.h"

int
main(int argc, char **argv)
{
//	int					sockfd, n;
//	char				recvline[MAXLINE + 1];
//	struct sockaddr_in	servaddr;
	struct hostent *he;
 	char str[INET6_ADDRSTRLEN];
	const char *addr1;
	if (argc != 2)
		err_quit("usage: a.out <host_name>");
	
	if ((he = gethostbyname(argv[1])) == NULL) {  // get the host info
                herror("gethostbyname");
                return 2;
          }

        printf("The host name %s \n",he->h_name);
	addr1 = inet_ntop(he->h_addrtype,he->h_addr_list[0],str,sizeof(str));
	printf("Address is %s \n",addr1);
	printf("%ld \n",sizeof(str));

//	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//		err_sys("socket error");

//	bzero(&servaddr, sizeof(servaddr));
//	servaddr.sin_family = AF_INET;
//	servaddr.sin_port   = htons(1300);	/* daytime server */
//	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
//		err_quit("inet_pton error for %s", argv[1]);

//	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
//		err_sys("connect error");

//	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
//		recvline[n] = 0;	/* null terminate */
//		if (fputs(recvline, stdout) == EOF)
//			err_sys("fputs error");
//	}
//	if (n < 0)
//		err_sys("read error");
	
	
	exit(0);
}

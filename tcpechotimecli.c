#include	"unp.h"
#include <sys/types.h>
void child_proc(char);
	int
main(int argc, char **argv)
{	
	struct sockaddr_in caddr;
	struct hostent *ha;
//	struct in_addr addr_4;
	char choice;
	char str[INET_ADDRSTRLEN];
	int pid;
	int pfd[2];

	if (argc != 2)
		err_quit("usage: a.out <host_name>");
	if(inet_pton(AF_INET, argv[1], &addr_4)<= 0){
		
		if ((ha = gethostbyname(argv[1])) == NULL) {  
			err_quit("Invalid host name or IP address");
			return 2;
		}
		else{
		
		printf("Address is %s \n",inet_ntop(ha->h_addrtype,ha->h_addr_list[0],str,sizeof(str)) );


		}

	}
	else{
//		if((ha = gethostbyaddr(&addr_4,sizeof(addr_4),AF_INET)) == NULL){
		if((ha = gethostbyaddr(&caddr.sin_addr,sizeof(caddr.sin_addr),AF_INET)) == NULL){
			herror("Enter valid IP address");
			return 2;
		}
		else{
			printf("The host name is %s \n",ha->h_name);

		}

	}

//	for( ; ; ){
		printf("Enter your choice \n");         
		printf("'t' for time \n");      
		printf("'e' for echo \n");      
		printf("'q' to quit \n"); 

		scanf("%c",&choice);
		if(choice == 'e' || choice =='t' || choice == 'q'){
			switch(choice){
				case 't': 
				case 'e': if(pipe(pfd) == -1)
					  { perror("Pipe failed");
					    exit(1);
						}
					  pid = fork();
					  if(pid < 0){
					  perror("Failed to fork");
					  exit(2);
					}
					  if(pid == 0){
					  close(pfd[0]);
					  if(choice == 'e'){
					   execlp("xterm", "xterm", "-e", "./echocli", "127.0.0.1", (char *) 0);	
					  }
					  else{
					  execlp("xterm", "xterm", "-e", "./timecli", "127.0.0.1", (char *) 0);

					}				
					 // child_proc(choice);
					 } 
					 else{
						close(pfd[1]);
						parent_proc(); }	
					 break;
				case 'q': printf("You chose to quit \n");
					  break;
				
			}	
		}
		else{
		    printf("Invalid choice\n");
		    continue;
		}
//		if(choice == 'q'){
//			break;
//		}
//		else{
//		    continue;
//		}
//	}
	exit(0);
}

void child_proc(char ch){
	if(ch == 't'){
	printf("child chose time \n");
	return ;
}
	else if(ch == 'e'){
	printf("user chose to echo\n");
}
}

void parent_proc(){


}

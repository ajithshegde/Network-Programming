#include	"unp.h"
#include <sys/types.h>
//void child_proc(char);
//void parent_proc();
	int
main(int argc, char **argv)
{	
	struct sockaddr_in caddr;
	struct hostent *ha;
	//	struct in_addr addr_4;
	char choice;
	char str[INET_ADDRSTRLEN];
	int pid,nread;
	int pfd[2];
	char buf[100];
	char pf[100];

	if (argc != 2)
		err_quit("usage: a.out <host_name>");
	if(inet_pton(AF_INET, argv[1], &caddr.sin_addr)<= 0){

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

				  if((pid=fork()) < 0){
					  perror("Failed to fork");
					  exit(2);
				  }
				  if(pid == 0){
					  close(pfd[0]);
					  sprintf(pf,"%d",pfd[1]);
					  					  
				          if(choice == 'e'){
						 // execlp("xterm", "xterm", "-e", "./echo_cli", "127.0.0.1", (char *) 0);
						 // perror("echo failed");	
						  printf("In child..child process forked and echoed\n");  
					  }
					  else{
						  execlp("xterm", "xterm", "-e", "./time_cli", "127.0.0.1",pf, (char *) 0);
						  perror("time failed");
						  printf("In child..child process forked and timed \n");	
					  }				
					  // child_proc(choice);
				  } 
				  else{
					  close(pfd[1]);
					  
					  
					  printf("In parent..child forked\n");
					 // for( ; ;){
					 // while ((nread =read(pfd[0], buf, 100))!= 0)
					//	printf("child read %s\n", buf);
					 // break;		
					 // }
					  //parent_proc(); }	
					  break;
			case 'q': printf("You chose to quit \n");
				  break;

		}	
	}
	}
	else{
		printf("Invalid choice\n");
		//continue;
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

/*void child_proc(char ch){
  if(ch == 't'){
  printf("child chose time \n");
  return ;
  }
  else if(ch == 'e'){
  printf("user chose to echo\n");
  }
  }*/

/*void parent_proc(){


  }*/

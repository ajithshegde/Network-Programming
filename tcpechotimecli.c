#include	"unp.h"

	int
main(int argc, char **argv)
{
	struct hostent *ha;
	struct in_addr addr_4;
	char choice;
	char str[INET_ADDRSTRLEN];


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
		if((ha = gethostbyaddr(&addr_4,sizeof(addr_4),AF_INET)) == NULL){
			herror("Enter valid IP address");
			return 2;
		}
		else{
			printf("The host name is %s \n",ha->h_name);

		}

	}

	for( ; ; ){
		printf("Enter your choice \n");         
		printf("'t' for time \n");      
		printf("'e' for echo \n");      
		printf("'q' to quit \n"); 

		scanf("%c",&choice);
		if(choice == 'e' || choice =='t' || choice == 'q'){
			switch(choice){
				case 't': printf("You have chosen time \n");
					  break;
				case 'e': printf("You have chosen echo \n");
					  break;
				case 'q': printf("You chose to quit \n");
					  break;
				
			}	
		}
		else{
		    continue;
		}
		if(choice == 'q'){
			break;
		}
		else{
		    continue;
		}
	}
	exit(0);
}

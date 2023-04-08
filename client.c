#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <sys/types.h> 


int main(int argc, char *argv[])
{

	if(argc<1)
	{
		printf("You should pass the ip\n");
		exit(-1);
	}
	
	int client_sock;
	struct sockaddr_in addr;
	char buffer[1024];
	int port=atoi(argv[1]);
	
	client_sock=socket(AF_INET,SOCK_STREAM,0);
	
	memset(&addr,'\n',sizeof(addr)); 
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=INADDR_ANY;
	

	if (connect(client_sock,(struct sockaddr*)&addr,sizeof(addr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
    	}
    	
	while(1)
    	{

		printf("Enter un integer (press q to quit)\n");
		scanf("%s", buffer);
		if(strcmp(buffer,"q")==0)
		{
			send(client_sock,buffer,sizeof(buffer),0);
			close(client_sock);
			exit(-1);
		}
		send(client_sock,buffer,sizeof(buffer),0);
		bzero(buffer, sizeof(buffer));
		read(client_sock,buffer,sizeof(buffer));
		printf("Square value = %s\n\n", buffer);
    	}

	
	close(client_sock);


	return 0;
}


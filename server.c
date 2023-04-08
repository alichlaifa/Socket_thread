#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <sys/types.h> 
#include <pthread.h> 


#define MAX_CLIENT 20



void *connection_handler(void *socket_desc)
{
	int sock=*((int*)socket_desc);
	char buffer[1024];
		while(1)
	{	
		recv(sock,buffer,sizeof(buffer),0);
		if(strcmp(buffer,"q")==0)
		{
			free(socket_desc);
			close(sock);
		}
		int res=atoi(buffer)*atoi(buffer);
		sprintf(buffer, "%d", res);
		write(sock,buffer,sizeof(buffer));
	}
	
	free(socket_desc);
	close(sock);
	
}

int main(int argc, char *argv[])
{

	pthread_t thread_client[MAX_CLIENT];
	int sock_clients[MAX_CLIENT];
		if(argc<1)
	{
		printf("You should pass the port\n");
		exit(-1);
	}
	
	int server_sock,client_sock;
	int *new_sock; 
	struct sockaddr_in server_addr,client_addr;
	int port=atoi(argv[1]);
	
	server_sock=socket(AF_INET,SOCK_STREAM,0);
	
	memset(&server_addr,'\n',sizeof(server_addr)) ;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=INADDR_ANY;
	
	int b=bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(b<0)
	{
		printf("Bind error \n");
		exit(1);	
	}
	
	listen(server_sock,5);
	
	socklen_t addr_size=sizeof(server_addr);
	
	uint8_t i=0;
	
	while(client_sock=accept(server_sock,(struct sockaddr*)&client_addr,&addr_size))
	{
		system("clear");
		i++;
		printf("                Server:\n");
		printf("Number of clients : %d \n",i);
		pthread_t sniff;
		new_sock=malloc(sizeof(int));
		*new_sock=client_sock;
		if(pthread_create(&sniff,NULL,connection_handler,(void *)new_sock)<0)
		{
			printf("Could not create thread \n");
			exit(1);
		}

	}

		pthread_join(thread_client[0],NULL);
		pthread_join(thread_client[1],NULL);
		pthread_join(thread_client[2],NULL);
		pthread_join(thread_client[3],NULL);
		pthread_join(thread_client[4],NULL);
		close(server_sock);
		
		return 0;
	}
	


	




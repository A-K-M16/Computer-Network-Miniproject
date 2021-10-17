#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
int server_socket,n,m;
char buffer[1024],log[1024]="",pas[1024]="";
struct sockaddr_in servaddr;

server_socket = socket(AF_INET, SOCK_STREAM, 0);
memset(&servaddr, 0, sizeof(servaddr));

servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(9055);

bind(server_socket, (struct sockaddr*) &servaddr, sizeof(servaddr));
listen(server_socket, 5);

int client_socket;
client_socket = accept(server_socket, NULL, NULL);
printf("Connected\n");

while(1){
	n = recv(client_socket, &log, sizeof(log), 0);
	m = recv(client_socket, &pas, sizeof(pas), 0);
	//m = !strcmp(log,"YOGA");
	//printf("%c-%c-%c-%c-%c-%d-%s\n",log[0],log[1],log[2],log[3],log[4],m,log);
	//m = !strcmp(pas,"yoga");
	//printf("%c-%c-%c-%c-%c-%d-%s\n",pas[0],pas[1],pas[2],pas[3],pas[4],m,pas);
	if(!strcmp(log,"YOGA") && !strcmp(pas,"yoga")){
		printf("Correct ID");
		break;
	}
	send(client_socket, "Wrong ID or Password", sizeof("Wrong ID or Password"),0);
}
send(client_socket, "-", sizeof("-"),0);

n = recv(client_socket, &buffer, sizeof(buffer), 0);
printf("Message from Client :%s\n",buffer);

FILE *cmd = popen(buffer, "r");
char result[1024]="";
while (fgets(result, sizeof(result), cmd) !=NULL)
    send(client_socket, result, sizeof(result),0);
pclose(cmd);

strcpy(buffer,"-");
send(client_socket, buffer, sizeof(buffer),0);
close(server_socket);
return 0;
}

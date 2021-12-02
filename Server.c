#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<time.h>


void logger(char *id){
FILE *f;
time_t t;
time(&t);
f=fopen("log.txt","a");
fputs(ctime(&t),f);
fputs("User ID:",f);
fputs(id,f);
fputs("\n\n",f);
}

int login(char *log, char *pas){
FILE *f;
f=fopen("passfile.txt","r");
char pasID[1024]="",logID[1024]="";
while(!feof(f)){
	fscanf(f,"%s",logID);
	fscanf(f,"%s",pasID);
	if(!strcmp(logID,log) && !strcmp(pasID,pas)){
		printf("Correct ID\n");
		logger(logID);
		return 1;
	}
}
return 0;
}


int main(){
int server_socket,n,m;
char buffer[1024],log[1024]="",pas[1024]="";
struct sockaddr_in servaddr,cli;

server_socket = socket(AF_INET, SOCK_STREAM, 0);
memset(&servaddr, 0, sizeof(servaddr));

servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("192.168.0.190");
servaddr.sin_port = htons(9055);

bind(server_socket, (struct sockaddr*) &servaddr, sizeof(servaddr));
listen(server_socket, 5);

int client_socket, len = sizeof(cli);
client_socket = accept(server_socket, (struct sockaddr*)&cli, &len);
printf("Connected\n");

while(1){
	n = recv(client_socket, &log, sizeof(log), 0);
	m = recv(client_socket, &pas, sizeof(pas), 0);
	if(login(log,pas)){
		break;
	}
	send(client_socket, "Wrong ID or Password", sizeof("Wrong ID or Password"),0);
}
send(client_socket, "-", sizeof("-"),0);
//system("python3 send.py");

while(1){
n = recv(client_socket, &buffer, sizeof(buffer), 0);
printf("Message from Client :%s\n",buffer);
if(!strcmp(buffer,"exit"))break;
FILE *cmd = popen(buffer, "r");
char result[1024]="";
while (fgets(result, sizeof(result), cmd) !=NULL)
    send(client_socket, result, sizeof(result),0);
pclose(cmd);

strcpy(buffer,"-");
send(client_socket, buffer, sizeof(buffer),0);
}
close(server_socket);
return 0;
}

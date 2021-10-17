#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
int sockfd,n,len;
char rec[1024];
struct sockaddr_in servaddr;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
memset(&servaddr, 0, sizeof(servaddr));

servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(9055);

connect(sockfd, (struct sockaddr*) &servaddr , sizeof(servaddr));
printf("Connected\n");

while(1){
	printf("LoginID :");
	fgets(rec, sizeof(rec), stdin);
	rec[strcspn(rec, "\n")] = 0;
	send(sockfd, rec, sizeof(rec),0);

	printf("Password :");
	fgets(rec, sizeof(rec), stdin);
	rec[strcspn(rec, "\n")] = 0;
	send(sockfd, rec, sizeof(rec),0);

	n = recv(sockfd, &rec, sizeof(rec), 0);
    	if(!strcmp(rec,"-")) {
		printf("%s\n",rec);
        	break;
    	}
	else{
		printf("%s\n",rec);	
	}
}

printf("Enter Command :");
fgets(rec, sizeof(rec), stdin);
send(sockfd, rec, sizeof(rec),0);
printf("Message sent to server.\n\n");

while(1){
    n = recv(sockfd, &rec, sizeof(rec), 0);
    if(!strcmp(rec,"-")) {
        break;
    }
    printf("%s", rec);
}

close(sockfd);
return 0;
}

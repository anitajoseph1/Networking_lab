//UDP SERVER
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>

#define PORT 4000
#define SA struct sockaddr

int main(){
    int sockfd,n,addr = sizeof(struct sockaddr_in);
    char buff[1024];
    struct sockaddr_in x;
    //create socket
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1){
        printf("Socket creation failed");
        exit(0);
    }
    else{
        printf("Socket created successfully");
    }
    //assign server address
    bzero(&x,sizeof(x));
    x.sin_family = AF_INET;
    x.sin_addr.s_addr = htonl(INADDR_ANY);
    x.sin_port = htons(PORT);
    //bind socket
    if((bind(sockfd,(SA*)&x,sizeof(x))) != 0){
        printf("Socket bind failed");
        exit(0);
    }
    else{
        printf("Socket binded successfully");
    }
    printf("waiting...");
    do{
        n = recvfrom(sockfd,buff,1024,0,(SA*)&x,&addr);
        buff[n] = '\0';
        if(n>1){
            printf("received: %s",buff);
        }
        scanf("%s",buff);
        sendto(sockfd,buff,n,0,(SA*)&x,addr);
    }while(strcmp(buff,"quit") != 0);
    close(sockfd);
    return 0;
}


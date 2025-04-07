//FTP SERVER
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

#define PORT 8080
#define SA struct sockaddr

int main(){
    FILE *fp;
    int sockfd,connfd,n;
    char rcv[100],fileread[100];
    struct sockaddr_in servaddr,cliaddr;
    //create socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        printf("Socket creation failed");
        exit(0);
    }
    else{
        printf("Socket created successfully");
    }
    //assign server address
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    //bind socket
    if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr))) != 0){
        printf("Socket bind failed");
        exit(0);
    }
    else{
        printf("Socket binded successfully");
    }
    //server listening
    if((listen(sockfd,5)) != 0){
        printf("Listen failed");
        exit(0);
    }
    else{
        printf("Server is listening");
    }
    //accept client connection
    connfd = accept(sockfd,(SA*)&cliaddr,&sizeof(cliaddr));
    if(connfd==-1){
        printf("Failed to accept connection");
        exit(0);
    }
    else{
        printf("Connection accepted successfully");
    }
    
    n = recv(connfd,rcv,100,0);
    rcv[n] = '\0';
    
    fp = fopen(rcv,"r");
    if(fp == NULL){
        send(connfd,"error",5,0);
        close(connfd);
    }
    else{
        while(fgets(fileread,sizeof(fileread),fp)){
            if(send(connfd,fileread,sizeof(fileread),0) < 0){
                printf("Can't send file contents\n");
            }
            sleep(1);
        }
        if(!fgets(fileread,sizeof(fileread),fp)){
            send(connfd,"completed",10,0);
        }
    }
    return(0);
}


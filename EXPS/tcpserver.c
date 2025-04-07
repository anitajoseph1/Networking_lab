//TCP SERVER
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

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd){
    char buff[MAX];
    int n;
    for(;;){
        bzero(buff,MAX);
        read(connfd,buff,sizeof(buff));
        printf("From client: %s\nTo client: ",buff);
        bzero(buff,MAX);
        n=0;
        while((buff[n++] = getchar()) != '\n');
        write(connfd,buff,sizeof(buff));
        if(strncmp("exit",buff,4) == 0){
            printf("Server exits");
            break;
        }
    }
}

int main(){
    int sockfd,connfd;
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
    func(connfd);
    close(sockfd);
}

























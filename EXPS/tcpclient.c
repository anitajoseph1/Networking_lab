//TCP CLIENT
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

void func(int sockfd){
    char buff[MAX];
    int n;
    for(;;){
        bzero(buff,MAX);
        printf("Enter a string: ");
        n=0;
        while((buff[n++] = getchar()) != '\n');
        write(sockfd,buff,sizeof(buff));
        bzero(buff,MAX);
        read(sockfd,buff,sizeof(buff));
        printf("From server: %s",buff);
        if(strncmp("exit",buff,4) == 0){
            printf("Client exits\n");
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
    //connecting to server
    if((connect(sockfd,(SA*)&servaddr,sizeof(servaddr))) != 0){
        printf("Connection with server failed");
        exit(0);
    }
    else{
        printf("Connected to server");
    }
    
    func(sockfd);
    close(sockfd);
}

























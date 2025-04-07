//FTP CLIENT
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
    char name[100],fname[100],rcvg[100];
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
    
    printf("Enter the existing filename: ");
    scanf("%s",name);
    printf("Enter the new filename: ");
    scanf("%s",fname);
    
    fp = fopen(fname,"w");
    
    send(sockfd,name,sizeof(name),0);
    
    while(1){
        n = recv(sockfd,rcvg,100,0);
        rcvg[n] = '\0';
        if(strcmp(rcvg,"error") == 0){
            printf("File not found\n");
        }
        if(strcmp(rcvg,"completed") == 0){
            printf("File transfer completed");
            break;
        }
        else{
            fputs(rcvg,fp);
            fputs(rcvg,stdout);
        }
    }
    
    fclose(fp);
    close(sockfd);
    return 0;
}















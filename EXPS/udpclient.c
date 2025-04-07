//UDP CLIENT
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
    
    printf("connecting...");
    
    while(1){
        printf("Enter the message to be send: ");
        scanf("%s",buff);
        sendto(sockfd,buff,sizeof(buff),0,(SA*)&x,addr);
        if(strcmp(buff,"quit") == 0){
            break;
        }
        printf("Message send\nWaiting for response...\n");
        n = recvfrom(sockfd,buff,sizeof(buff),0,(SA*)&x,&addr);
        buff[n] = '\n';
        if(n>1){
            printf("received: %s",buff);
        }
    }
    close(sockfd);
    return 0;
}



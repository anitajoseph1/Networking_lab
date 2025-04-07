//STOP AND WAIT
#include <stdio.h>
#include <stdlib.h>

struct frame{
    int info;
    int seq;
};

int ak;
int t=5,k;
int disconnect=0;
struct frame p;
char turn='s';
int errorframe=1;
int errorack=1;

void sender();
void receiver();

void main(){
    p.info = 0;
    p.seq = 0;
    while(!disconnect){
        sender();
        for(k=1;k<=10000000;k++);
        receiver()
    }
}

void sender(){
    static int flag = 0;//to indicate if ack is received
    if(turn == 's'){
        if(errorack == 0){
            printf("SENDER: Sent packet with seq no: %d\n",p.seq);
            errorframe = rand()%4;
            printf("%s\n",(errorframe==0?"Error while sending packet":""));
            turn = 'r';
        }
        else{
            if(flag == 1){
                printf("SENDER: Received ACK for packet %d\n", ak);
            }
            if(p.seq == 5){
                disconnect =1;
                return;
            }
            p.info = p.info+1;
            p.seq = p.seq+1;
            printf("SENDER: Sent packet with seq no: %d\n",p.seq);
            errorframe = rand()%4;
            printf("%s\n",(errorframe==0?"Error while sending packet":""));
            turn = 'r';
            flag = 1;
        }
    }
    else{
        t--;
        printf("Sender time reducing\n");
        if(t==0){
            turn = 's';
            errorack = 0;
            t = 5;
        }
    }
}

void receiver(){
    static int frexp = 1;
    if(turn == 'r'){
        if(errorframe != 0){
            if(p.seq == frexp){
                printf("Received packet with seq no: %d\n",p.seq);
                ak = p.seq;
                frexp++;
                turn = 's';
                errorack = rand()%4;
                printf("%s\n",(errorack==0?"Error while sending ACK":""));
            }
            else{
                printf("Duplicated packet with seq no: %d\n",frexp-1);
                ak = frexp-1;
                turn = 's';
                errorack = rand()%4;
                printf("%s\n",(errorack==0?"Error while sending ACK":""));
            }
        }
    }
}



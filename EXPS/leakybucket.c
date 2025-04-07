//LEAKY BUCKET
#include <stdio.h>

int main(){
    int incoming,outgoing,n,bucket_size,store=0,available,dropped;
    printf("Enter bucket size,outgoing rate,number of inputs: ");
    scanf("%d%d%d",&bucket_size,&outgoing,&n);
    
    while(n!=0){
        printf("Enter the size of incoming packet: ");
        scanf("%d",&incoming);
        
        available = bucket_size-store;
        if(incoming <= available){
            store += incoming;
            printf("Current buffer usage: %d out of %d\n",store,bucket_size);
        }
        else{
            dropped = incoming-available;
            printf("%d packets are dropped",dropped);
            store = bucket_size;
            printf("Current buffer usage: %d out of %d\n",store,bucket_size);
        }
        
        if(store >= outgoing){
            store -= outgoing;
        }
        else{
            outgoing = store;
            store = 0;
        }
        
        printf("After outgoing,there are %d out of %d packets left in buffer\n",store,bucket_size);
        n--;
    }
    return 0;
}

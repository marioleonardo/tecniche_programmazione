#include <stdio.h>
#include <string.h>

void maxOdd(int V[], int N){
    int i, j, ctr, max, valid;

    ctr=0;      max=0;      valid=0;

    for(i=0;i<N;i++){
        if(V[i]%2!=0 && !valid){
            valid=1;
        }

        if((V[i]%2==0 || i==N-1) && valid){
            valid=0;
            if(max<ctr){
                max=ctr;
            }
            ctr=0;
        }

        
        if(valid){
            ctr++;
        }
    }

    for(i=N-1;i>=0;i--){
        if(V[i]%2!=0 && !valid){
            valid=1;
        }

        if((V[i]%2==0 || i==0) && valid && ctr==max){
            valid=0;
            for(j=i+1;j<ctr+i+1;j++){
                printf("%d ", V[j]);
            }
            printf("\n");
            ctr=0;
        }

        
        if(valid){
            ctr++;
        }
    }
}

int main(){

    /* char str[20]="ThisIsAString";
    int vet[10]={7,4,2,0,11,-1}, a;
    printf("%s\n", str);
    a=charErase(str, vet);
    printf("%s\n%d", str, a);
    */


   /*  int vet[10]={1, 3, 7, 1, 0, 1, 9, 3, 1, 0}, a;
    maxOdd(vet, 10); */



    return 0;
}
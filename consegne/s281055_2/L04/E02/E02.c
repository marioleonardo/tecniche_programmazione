#include <stdio.h>
#define maxN 30


void ruota(int v[maxN], int N, int P, int dir);

int main(){
    int N, V[maxN], P, dir;

    printf("Inserisci numero di elementi: ");
    scanf("%d", &N);
    printf("Inserisci uno a uno gli elementi: ");
    for(int i=0; i<N; i++)
        scanf("%d", &V[i]); 

    do {
        printf("Inserisci numero delle posizioni: ");
        scanf("%d", &P);
        printf("Inserisci direzione(-1 destra, 1 sinistra): ");
        scanf("%d", &dir);
        if(P!=0 && P<N){
            ruota(V, N, P, dir);
            printf("elementi vettore ruotato:\n");
            for(int i=0; i<N; i++)
                printf("%d ", V[i]);
        }
        
    } while(P!=0 && P<N);

    return 0;
}

void ruota(int v[maxN], int N, int P, int dir){
    int indexFinish, indexStart, valueTemp, newPos, counter, j;  

    counter = 0;
    indexStart = dir>0 ? 0 : N-1;
    while(counter != N){
        valueTemp = v[indexStart];  
        for(j=indexStart ; (N + j + (dir*P))%N != indexStart ; j = newPos ){
            newPos = (N + j + (dir*P))%N;
            v[j] = v[newPos];
            counter++;
            indexFinish = newPos;
        }
        v[indexFinish] = valueTemp;
        counter++;
        indexStart+= dir;
    }
}
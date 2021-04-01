#include <stdio.h>

#define MAX_NUMBERS 30

void sottoSequenze(int V[], int N);

int main(){
    FILE *fp_read, *fp_write;
    int listaNumeri[MAX_NUMBERS], i;
    

    if((fp_read=fopen("input.txt", "r"))==NULL){
        printf("Error opening file\n");
        return 1;
    }

    
    for( i=0; fscanf(fp_read, "%d", &listaNumeri[i]) > 0 && i<30; i++ );

    sottoSequenze(listaNumeri, i);
    
    fclose(fp_read);

    return 0;
}

void sottoSequenze(int V[], int N){
    int vIndices[N/2+1], vIndex, maxLength, currentLength, mainIndex;
   
    maxLength = 0;    currentLength = 0;  vIndex=0; 
    for(mainIndex=0 ; mainIndex<N ; mainIndex++){
        if(V[mainIndex] != 0)
            currentLength++;
        if((currentLength>0 && V[mainIndex]==0) || mainIndex+1 == N) {
            // trattiamo l'ultimo sottovettore diversamente in crementando di uno mainIndex, in alternativa si poteva ripetere
            // il codice esplicitamente dopo il for 
            if (mainIndex+1==N)
                mainIndex++;

            if(currentLength > maxLength){
                maxLength = currentLength;
                vIndices[0] = mainIndex - currentLength;
                vIndex = 1;
            }
            else if(currentLength == maxLength){
                vIndices[vIndex] = mainIndex - currentLength;
                vIndex++;
            }
            currentLength = 0;
        }
    }

    for(mainIndex = 0; vIndices[mainIndex]>0 && mainIndex<N/2+1; mainIndex++){
        printf("%c ", '[');
        for(vIndex = vIndices[mainIndex] ; vIndex < vIndices[mainIndex] + maxLength ; vIndex++)
            printf("%d ", V[vIndex]);
        printf("%c\n", ']');
    }
}
#include <stdio.h>

#define MAX_NUMBERS 30
#define filein "..\\text\\input.txt"

void sottoSequenze(int V[], int N);

int main(){
    FILE *fp_read, *fp_write;
    int listaNumeri[MAX_NUMBERS], i;
    

    if((fp_read=fopen(filein, "r"))==NULL){
        printf("Error opening file\n");
        return 1;
    }

    
    for( i=0; fscanf(fp_read, "%d", &listaNumeri[i]) > 0 && i<30; i++ );

    fclose(fp_read);

    sottoSequenze(listaNumeri, i);

    return 0;
}

void sottoSequenze(int V[], int N){
    int vIndices[N/2+1], numIndices, vIndex, maxLength, currentLength, mainIndex, i;
   
    maxLength = 0;    currentLength = 0;  vIndex=0;
    for(mainIndex=0 ; mainIndex<N ; mainIndex++){
        if(V[mainIndex] != 0)
            currentLength++;
        if((currentLength>0 && V[mainIndex]==0) || mainIndex+1 == N) {
            // trattiamo l'ultimo sottovettore diversamente incrementando di uno mainIndex, in alternativa si poteva ripetere
            // il codice esplicitamente dopo il for 
            if (mainIndex+1==N &&  V[mainIndex]!=0)
                currentLength++;

            if(currentLength > maxLength){
                maxLength = currentLength;
                vIndices[0] = mainIndex - currentLength;
                vIndex = 1;
                numIndices = vIndex;
            }
            else if(currentLength == maxLength){
                vIndices[vIndex] = mainIndex - currentLength;
                vIndex++;
                numIndices = vIndex;
            }
            currentLength = 0;
        }
    }

    
    for(vIndex = 0 ; vIndex < numIndices; vIndex++){
        printf("%c ", '[');
        for(i = vIndices[vIndex] ; i < vIndices[vIndex] + maxLength ; i++)
            printf("%d ", V[i]);
        printf("%c\n", ']');
    }
}
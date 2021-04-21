#include <stdio.h>
#include "..\lib.h"
#include <string.h>
#define filein "..\\text\\caselli.txt"
#define MAX_DIM_CASELLI 25

struct casello{
    char startPos[20+1];
    char stopPos[20+1];
    float price;
};

struct resultRecursive{
    float cost;
    int numTratte;
};

int handleFileInput(FILE *fp, struct casello caselli[], int maxDim);
void calcolaPercorso(struct casello caselli[], int dimCasello, char start[20+1], char stop[20+1]);
struct resultRecursive calcolaTratteRecursive(struct casello caselli[], int dimCasello, char start[20+1], char stop[20+1], int numTratta);

int main(int argc, char *argv[]){
    FILE *fp_read;
    struct casello caselli[MAX_DIM_CASELLI];
    struct resultRecursive result;
    int dimCaselli, numTratte;
    float cost;
    char startLoc[20+1], stopLoc[20+1];

    if(argc==3){
        strcpy(startLoc, argv[1]);
        strcpy(stopLoc, argv[2]);
        lower(startLoc, 20);
        lower(stopLoc, 20);
    }
    else{
        printf("wrong inputs");
        return 1;  
    }

    if((fp_read = fopen(filein, "r"))==NULL){   printf("Errore apertura file!\n");    return 1;}

    dimCaselli = handleFileInput(fp_read, caselli, MAX_DIM_CASELLI);
    fclose(fp_read);

    result = calcolaTratteRecursive(caselli, dimCaselli, startLoc, stopLoc, 0);
    
    if(result.numTratte == 0)
        printf("Impossibile raggiungere la destinazione percorrendo un massimo di 3 tratte.\n");
    if(result.numTratte == 1)
        printf("Destinazione raggiunta in 1 tratta. Spesa complessiva: %.2f€", result.cost);
    if(result.numTratte > 1)
        printf("Destinazione raggiunta in %d tratta. Spesa complessiva: %.2f€", result.numTratte, result.cost);

    return 0;
}

int handleFileInput(FILE *fp, struct casello caselli[], int maxDim){
    int dimCaselli;

    for (int i = 0; i < maxDim && !feof(fp); i++){
        fscanf(fp, "%s%s%f ", caselli[i].startPos, caselli[i].stopPos, &caselli[i].price);
        dimCaselli=i;
        lower(caselli[i].startPos, 20);
        lower(caselli[i].stopPos, 20);
    }

    return ++dimCaselli;
}

struct resultRecursive calcolaTratteRecursive(struct casello caselli[], int dimCasello, char start[20+1], char stop[20+1], int numTratta){
    int startEqual, stopEqual;
    struct resultRecursive result;
    
    numTratta++;
    for(int i=0; i<dimCasello; i++){
        startEqual=strcmp(caselli[i].startPos, start) == 0;
        stopEqual=strcmp(caselli[i].stopPos, stop) == 0;
        if(startEqual && stopEqual){
            result.cost=caselli[i].price;
            result.numTratte=1;
            return result;
        }
    }
    if(numTratta < 3){
        for(int i=0; i<dimCasello; i++){
            startEqual=strcmp(caselli[i].startPos, start) == 0;
            stopEqual=strcmp(caselli[i].stopPos, stop) == 0;
            if(startEqual){
                result = calcolaTratteRecursive(caselli, dimCasello, caselli[i].stopPos, stop, numTratta);
                if(result.numTratte > 0){
                    result.cost+=caselli[i].price;
                    result.numTratte++;
                    return result;
                }
            }
        }
    }

    result.numTratte=0;
    return result;
}
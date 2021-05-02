#include <stdio.h>
#define MAX_ROWS 20
#define MAX_COLUMNS 20
#define MAX_CHAR 20 

void stampaMatriciQuadrate(int v[MAX_ROWS][MAX_COLUMNS], int rows, int columns, int dim);

int main(){
    FILE *fp_read;
    char fileName[MAX_CHAR+1];
    int v[MAX_ROWS][MAX_COLUMNS], nr, nc, min, dim, i, j;

    printf("Inserisci nome file: ");
    scanf("%s", fileName);
    if((fp_read = fopen(fileName, "r"))==NULL){
        return 1;   printf("Errore lettura file");
    }

    fscanf(fp_read, " %d %d ", &nr, &nc);
    min = nr > nc ? nc : nr;
    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            fscanf(fp_read, "%d", &v[i][j]);
        }
    }

    do{
        printf("Inserisci dimensione matrice quadrata: ");
        scanf("%d", &dim);
        if(dim>0 && dim<=min)
            stampaMatriciQuadrate(v, nr, nc, dim);
    } while(dim>0 && dim<=min);

    fclose(fp_read);
    return 0;
}

void stampaMatriciQuadrate(int v[MAX_ROWS][MAX_COLUMNS], int nr, int nc, int dim){
    int row, col, rowStart, colStart, rowMax, colMax, somma, sommaMax;

    printf("Le sottomatrici quadrate di dimensione 2 sono:\n\n");
    somma=0;    sommaMax=0;
    for(rowStart=0; rowStart <= nr - dim; rowStart++){
        for(colStart=0; colStart <= nc - dim; colStart++){
            for(row=rowStart; row < rowStart + dim; row++){
                for(col=colStart; col < colStart + dim; col++){
                    printf("%d ", v[row][col]);
                    somma+=v[row][col];
                }
                printf("\n");
            }
            printf("\n");
            if(somma>sommaMax){
                sommaMax = somma;
                rowMax = rowStart;
                colMax = colStart;
            }
            somma = 0;
        }
    }

    printf("La sottomatrice con somma degli elementi massima (%d) e’:\n\n", sommaMax);

    for(row = rowMax; row < rowMax+ dim; row++){
        for(col = colMax; col < colMax + dim; col++){
            printf("%d ", v[row][col]);
        }
        printf("\n");
    }
}
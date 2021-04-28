#include <stdio.h>
#include <string.h>
#define LEN_FILE 20
#define LEN_OP 100
#define DIM_MAT 30

void handleFile(FILE *fp, int mat[][DIM_MAT], int  dim[2]);

void rotate(int mat[DIM_MAT][DIM_MAT], int dim[2], int row, int index, int direction, int position);

void printMat(int mat[DIM_MAT][DIM_MAT], int nr, int nc);

int main(){
    FILE *fp_read;
    char fileInput[LEN_FILE+1], operation[LEN_OP+1], rowChar[15], directionChar[15];
    int mat[DIM_MAT][DIM_MAT], finito, dim[2], row, direction,indexRow, numPos;

    printf("Inserisci nome file: ");
    scanf("%s%*c", fileInput);
    


    if((fp_read=fopen("..\\text\\mat31.txt", "r"))==NULL){
        printf("Errore apertura file");
        return 1;
    }

    handleFile(fp_read, mat, dim);

    finito=0;
    printMat(mat, dim[0], dim[1]);
    printf("Inserisci l'operazione (riga 1 destra 1): ");
    while(fgets(operation, LEN_OP, stdin)!=NULL && !finito){
        if(operation[0]==26)
            finito=1;
        sscanf(operation, "%s%d%s%d", rowChar, &indexRow, directionChar, &numPos);
        row = strcmp(rowChar, "riga")==0 ? 1 : 0;
        direction = strcmp(directionChar, "destra")==0 ? 1 : -1;
        rotate(mat, dim, row, indexRow, direction, numPos);
        printMat(mat, dim[0], dim[1]);
        printf("Inserisci l'operazione (riga 1 destra 1): ");
    }

    return 0;
}

void handleFile(FILE *fp, int mat[DIM_MAT][DIM_MAT], int dim[2]){
    int nc, nr;
    fscanf(fp, "%d%d", &nr, &nc);
    dim[0]=nr;  dim[1]=nc;
    for(int i=0; i<nr; i++){
        for(int j=0; j<nc; j++){
            fscanf(fp, "%d ", &mat[i][j]);
        }
    }
}

void rotate(int mat[DIM_MAT][DIM_MAT], int dim[2], int row, int index, int direction, int position){
    int nr, nc, N;
    int indexFinish, indexStart, valueTemp, newPos, counter;  

    nr=dim[0];      nc=dim[1];      
    index--;

    N = row == 1 ? nc : nr;
    counter = 0;
    indexStart = direction>0 ? 0 : N-1;
    while(counter != N && row==1){
        valueTemp = mat[index][indexStart];  
        for(int j=indexStart ; (N + j + (direction*position))%N != indexStart ; j = newPos ){
            newPos = (N + j + (direction*position))%N;
            mat[index][j] = mat[index][newPos];
            counter++;
            indexFinish = newPos;
        }
        mat[index][indexFinish] = valueTemp;
        counter++;
        indexStart+= direction;
    }
    while(counter != N && row==0){
        valueTemp = mat[indexStart][index];  
        for(int j=indexStart ; (N + j + (direction*position))%N != indexStart ; j = newPos ){
            newPos = (N + j + (direction*position))%N;
            mat[j][index] = mat[newPos][index];
            counter++;
            indexFinish = newPos;
        }
        mat[indexFinish][index] = valueTemp;
        counter++;
        indexStart+= direction;
    }
}

void printMat(int mat[DIM_MAT][DIM_MAT], int nr, int nc){
    printf("\n");
    for(int i=0; i<nr; i++){
        for(int j=0; j<nc; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
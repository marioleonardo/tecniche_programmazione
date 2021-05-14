#include <stdio.h>
#define filein "../text/mappa.txt"
#define MAX_MAT 50

struct rect{
    int start[2];
    int end[2];
    int base;
    int height;
    int area;
};

struct rect calculateNewRect(int mat[MAX_MAT][MAX_MAT], int dim[2], int startr, int startc);

void handleFileInput(FILE *fp, int mat[MAX_MAT][MAX_MAT], int dim[2]);

void compareMax(struct rect *rectTemp, struct rect *maxA, struct rect *maxB, struct rect *maxH);

void printMax(struct rect *maxA, struct rect *maxB, struct rect *maxH);

void copyRect(struct rect *rectA, struct rect *rectB);

int main(){
    struct rect rectTemp, rectMaxArea={{0,0},{0,0},0,0,0}, rectMaxBase={{0,0},{0,0},0,0,0}, rectMaxHeight={{0,0},{0,0},0,0,0};
    int matr, matc;
    int mat[MAX_MAT][MAX_MAT], dim[2];
    FILE *fp_read;

    if((fp_read=fopen(filein, "r"))==NULL){
        printf("Error file opening");
    }

    handleFileInput(fp_read, mat, dim);
    fclose(fp_read);  

    for(matr=0 ;matr<dim[0]; matr++){
        for(matc=0 ;matc<dim[1]; matc++){
            if(mat[matr][matc] == 1 && mat[matr-1][matc] == 0){
                rectTemp = calculateNewRect(mat, dim, matr, matc);
                compareMax(&rectTemp,  &rectMaxArea, &rectMaxBase, &rectMaxHeight);
            }
        }
    }
    
    printMax(&rectMaxArea, &rectMaxBase, &rectMaxHeight);
}

void handleFileInput(FILE *fp, int mat[MAX_MAT][MAX_MAT], int dim[2]){
    int i, j;

    fscanf(fp, "%d%d ", &dim[0], &dim[1]);
    for(i=0 ; i<dim[0] ; i++){
        for(j=0 ;j<dim[1]; j++){
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
}

struct rect calculateNewRect(int mat[MAX_MAT][MAX_MAT], int dim[2], int startr, int startc){
    int r, c;
    struct rect rectTemp;
    
    for(r=startr ;r<dim[0] && mat[r+1][startc]==1; r++);
    for(c=startc ;c<dim[1] && mat[startr][c+1]==1; c++);

    rectTemp.start[0] = startr;
    rectTemp.start[1] = startc;
    rectTemp.end[0] = r;
    rectTemp.end[1] = c;

    rectTemp.base = rectTemp.end[1] - rectTemp.start[1] + 1;
    rectTemp.height = rectTemp.end[0] - rectTemp.start[0] + 1;
    rectTemp.area = rectTemp.height * rectTemp.base;

    return rectTemp;
}

void compareMax(struct rect *rectTemp, struct rect *maxA, struct rect *maxB, struct rect *maxH){
    if((*rectTemp).area > (*maxA).area)         copyRect(rectTemp, maxA);
    if((*rectTemp).base > (*maxB).base)         copyRect(rectTemp, maxB);
    if((*rectTemp).height > (*maxH).height)     copyRect(rectTemp, maxH);
}

void copyRect(struct rect *rectA, struct rect *rectB){
    (*rectB).area = (*rectA).area;
    (*rectB).base = (*rectA).base;
    (*rectB).height = (*rectA).height;
    (*rectB).start[0] = (*rectA).start[0];
    (*rectB).start[1] = (*rectA).start[1];
    (*rectB).end[0] = (*rectA).end[0];
    (*rectB).end[1] = (*rectA).end[1];
}

void printMax(struct rect *maxA, struct rect *maxB, struct rect *maxH){
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", (*maxB).start[0], (*maxB).start[1], (*maxB).base, (*maxB).height, (*maxB).area);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d \n", (*maxA).start[0], (*maxA).start[1], (*maxA).base, (*maxA).height, (*maxA).area);
    printf("Max Altezza: estr. sup. SX = <%d,%d> b = %d, h = %d, Area=%d \n",  (*maxH).start[0], (*maxH).start[1], (*maxH).base, (*maxH).height, (*maxH).area);
}
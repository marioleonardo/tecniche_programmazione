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

int riconosciRegione(int M[MAX_MAT][MAX_MAT] , int  nr, int nc, int startr, int startc, int *b, int *h);
void leggiMatrice(int M[MAX_MAT][MAX_MAT], int maxr , int *nr, int *nc);
void compareMax(struct rect *rectTemp, struct rect *maxA, struct rect *maxB, struct rect *maxH);
void printMax(struct rect *maxA, struct rect *maxB, struct rect *maxH);

int main(){
    struct rect rectTemp, rectMaxArea={{0,0},{0,0},0,0,0}, rectMaxBase={{0,0},{0,0},0,0,0}, rectMaxHeight={{0,0},{0,0},0,0,0};
    int matr, matc, nr, nc, b, h;
    int mat[MAX_MAT][MAX_MAT];

    leggiMatrice(mat, MAX_MAT, &nr, &nc);  

    for(matr=0 ;matr<nr; matr++){
        for(matc=0 ;matc<nc; matc++){
            if(riconosciRegione(mat , nr, nc, matr, matc, &b, &h)){
                rectTemp.start[0]=matr;
                rectTemp.start[1]=matc;
                rectTemp.base=b;
                rectTemp.height=h;
                rectTemp.area=b*h;

                compareMax(&rectTemp,  &rectMaxArea, &rectMaxBase, &rectMaxHeight);
            }
        }
    }
    printMax(&rectMaxArea, &rectMaxBase, &rectMaxHeight);
}

void leggiMatrice(int M[MAX_MAT][MAX_MAT], int maxr , int *nr, int *nc){
    int i, j, r, c;
    FILE *fp;

    if((fp=fopen(filein, "r"))==NULL){
        printf("Error file opening");
    }

    fscanf(fp, "%d%d ", &r, &c);
    for(i=0 ; i<r ; i++){
        for(j=0 ;j<c; j++){
            fscanf(fp, "%d", &M[i][j]);
        }
    }

    *nr=r;      *nc=c;

    fclose(fp);
}

int riconosciRegione(int M[MAX_MAT][MAX_MAT] , int  nr, int nc, int startr, int startc, int *b, int *h){
    int r, c;
    
    if(M[startr][startc] == 1 && (startr==0 || M[startr-1][startc] == 0) && (startc==0 || M[startr][startc-1] == 0)){
        for(r=startr ;r<nr && M[r+1][startc]==1; r++);
        for(c=startc ;c<nc && M[startr][c+1]==1; c++);

        *b= c - startc + 1;
        *h = r - startr + 1;

        printf("Rectangle found estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", startr, startc, *b, *h, (*b * *h));

        return 1;
    }
    else
        return 0;
}

void compareMax(struct rect *rectTemp, struct rect *maxA, struct rect *maxB, struct rect *maxH){
    if(rectTemp->area > maxA->area)         
        *maxA=*rectTemp;
    if(rectTemp->base > maxB->base  || (rectTemp->base ==maxB->base && rectTemp->area > maxB->area))         
        *maxB=*rectTemp;
    if(rectTemp->height > maxH->height || (rectTemp->height ==maxB->height && rectTemp->area > maxB->area))     
        *maxH=*rectTemp;
}

void printMax(struct rect *maxA, struct rect *maxB, struct rect *maxH){
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",             maxB->start[0], maxB->start[1], maxB->base, maxB->height, maxB->area);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d \n",            maxA->start[0], maxA->start[1], maxA->base, maxA->height, maxA->area);
    printf("Max Altezza: estr. sup. SX = <%d,%d> b = %d, h = %d, Area=%d \n",   maxH->start[0], maxH->start[1], maxH->base, maxH->height, maxH->area);
}
#include <stdio.h>

#define filein "..\\text\\gomoku.txt" 

#define vuota   0
#define bianco  1
#define nero    2

#define chain   3

int inputHandler(FILE* fp, int mat[19][19]);
int checkVittoria(int mat[19][19], int move[2], int turno);
void printMatrice(int mat[19][19]);

int main(){
    FILE* fp_read;
    int turno, mat[19][19], lastMove[2], move[2], inArray, vittoria;
    char moveText[5+1];
    
    if((fp_read = fopen(filein, "r")) == NULL){
        printf("Errore lettura");   return 1;
    }

    inputHandler(fp_read, mat);

    turno=bianco;
    vittoria = 0;

    while(vittoria == 0){
        printMatrice(mat);
        printf("\nE' il turno del giocatore %s\n", turno==bianco? "bianco" : "nero");
        printf("Inserisci la casella che vuoi riempire [riga colonna]: ");
        scanf("%d%d", &move[0], &move[1]);
        move[0]--;    move[1]--;

        inArray = (( move[0]>-1 && move[0]<19) && ( move[1]>-1 && move[1]<19 ));
        while(!inArray || mat[move[0]][move[1]] != vuota){
            printf("Posizione scelta erronea!\nInserisci la casella che vuoi riempire [riga colonna]: ");
            scanf("%d%d", &move[0], &move[1]);
            move[0]--;    move[1]--;
            inArray = (( move[0]>-1 && move[0]<19) && ( move[1]>-1 && move[1]<19 ));
        }
        mat[move[0]][move[1]] = turno;
        vittoria=checkVittoria(mat, move, turno);
        if(!vittoria)      turno = (turno == bianco ? nero : bianco );
    }
    printf("\n\nHa vinto il giocatore %s",  turno==bianco? "bianco" : "nero");

    fclose(fp_read);
    return 0;
}

int checkVittoria(int mat[19][19], int move[2], int turno){
    int length, xStart, yStart, x, y;
    const int deltaPos[4][2]={{0, 1} ,{1, 0}, {1, 1}, {1, -1}};

    xStart = move[1];
    yStart = move[0];

    for(int i=0; i<4 && length<chain; i++){
        length=1;
        for (x=xStart+deltaPos[i][0], y=yStart+deltaPos[i][1];  (((x>-1 && x<19) && (y>-1 && y<19)) && mat[y][x]==turno) && length<chain; x=x+deltaPos[i][0], y=y+deltaPos[i][1])
            length++;
        for (x=xStart-deltaPos[i][0], y=yStart-deltaPos[i][1];  (((x>-1 && x<19) && (y>-1 && y<19)) && mat[y][x]==turno) && length<chain; x=x-deltaPos[i][0], y=y-deltaPos[i][1])
            length++;
    }

    if(length>=chain)   return 1;
    else            return 0;
}

void printMatrice(int mat[19][19]){
    for(int r=0; r<19; r++){
        for(int c=0; c<19; c++){
            if(mat[r][c]==bianco)   fputc('B', stdout);
            if(mat[r][c]==nero)     fputc('N', stdout);
            if(mat[r][c]==vuota)    fputc('.', stdout);
        }
        fputc('\n', stdout);
    }
}

int inputHandler(FILE* fp, int mat[19][19]){
    char chr;
    int index;

    for(int r=0; r<19; r++){
        for(int c=0; c<19; c++){
            chr = fgetc(fp);
            switch(chr){
                case 'B':   mat[r][c]=bianco;    break;
                case 'N':   mat[r][c]=nero;    break;
                case '.':   mat[r][c]=vuota;    break;
                default:
                    printf("File not correct\n");   
                    return 1;                 
            }
        }
        for(char buf=fgetc(fp); buf!='\n' &&  buf!=EOF; buf=fgetc(fp));
   }
   return 0;
}

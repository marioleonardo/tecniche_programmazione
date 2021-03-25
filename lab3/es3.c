#include <stdio.h>
#include <math.h>

int isvalid(int x0, int x1, int x2);

int main(){
    FILE *fp_read, *fp_write;
    char character;
    int x0, x1, x2, min, max, discardedCounter;

    if((fp_read=fopen("numeri.txt", "r"))==NULL){
        printf("Error opening file\n");
        return 1;
    }

    fscanf(fp_read, "%d", &x0);
    fscanf(fp_read, "%d", &x1);
    max = x0 > x1 ? x0 : x1;
    min = x0 < x1 ? x0 : x1;
    while((fscanf(fp_read, "%d", &x2)) >0){

        if(isvalid(x0, x1, x2)){
            max = x2 > max ? x2 : max;
            min = x2 < min ? x2 : min;
            x0=x1;      x1=x2;
        }
        else
            discardedCounter++;

    }


    printf("Numero massimo: %d\n", max);
    printf("Numero minimo: %d\n", min);
    printf("Numeri scartati: %d\n", discardedCounter);
    

    fclose(fp_read);

    return 0;
}

int isvalid(int x0, int x1, int x2){
    int zeroFlag, sum, sub, mult, div;

    zeroFlag = ( x1 == 0 );
    if(!zeroFlag)
        div = (( (int)(x0 / x1) == x2) && (x0 % x1 == 0));
    else
        div = 0;
    sum = x0 + x1 == x2;
    sub = x0 - x1 == x2;
    mult = x0 * x1 == x2; 
    if(sub || sum || div || mult)
        return 1;
    else
        return 0;
}
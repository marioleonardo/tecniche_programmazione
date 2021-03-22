#include <stdio.h>
#include <stdlib.h>


#define COLUMNS 100
#define ROWS 30

float parabola(float x, float a, float b, float c);

int main(){
    float a=1.0, b=0.0, c=0.0;
    float x0=-5.0, xn=5.0, y0=-5.0, yn=5.0, x, y, deltaX, deltaY;
    int n, i, j;
    FILE *fp_write;

    if((fp_write=fopen("./parabola.txt","w"))==NULL){ return 1;}

    deltaX=fabs(xn-x0)/COLUMNS;
    deltaY=fabs(yn-y0)/ROWS;

    for(i=0; i<ROWS; i++){
        for(j=0; j<COLUMNS; j++){
            x=x0+(deltaX*(0.5+j));
            y=parabola(x,a,b,c);
            if( y<=(yn-(deltaY*i)) && y>(yn-(deltaY*(i+1))) ){
                fprintf(fp_write, "*");
            }
            else{
                fprintf(fp_write, " ");
            }
        }
        fprintf(fp_write, "\n");
    }
    fclose(fp_write);
    return 0;
}

float parabola(float x, float a, float b, float c){
    float y;
    //y=a*x*x+b*x+c;
    y=x*x*x;
    return y;
}
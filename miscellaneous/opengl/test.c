#include <stdio.h>
#define len(array) sizeof( array )/sizeof(array[0])
#define NUM_PTS 3


int flength(double array[], int length){
    int index=0;
    int nonZeroLast=0;
    while(index < length ){
        if(array[index] != 0)
            nonZeroLast=index;
        index++;
    }
    return nonZeroLast;
}

double * coeffMultiply(double a[], double b[], int lengthA, int lengthB){
    int index=0;
    int nonZeroLast=0;
    while(index < lengthA ){
        if(a[index] != 0)
            nonZeroLast=index;
        index++;
    }
    lengthA=nonZeroLast;
    index=0;
    nonZeroLast=0;
    while(index < lengthB ){
        if(b[index] != 0)
            nonZeroLast=index;
        index++;
    }
    lengthB=nonZeroLast;
    double result[1 + lengthA + lengthB];
    
    for(int first=0; first<lengthA+1; first++){
        for(int second=0; second<lengthB+1; second++){
            result[first+second]+=a[first]*b[second];
        }
    }
    return result;
}

int main(){

    int c;
    int ptsList[3][2]={{2,3}, {4,5}, {6,7}};
    double a[5]={3,4}, b[2]={5,6};
    for(int i=0; i<NUM_PTS; i++){
    printf("%g", (coeffMultiply(a, b, len(a), len(b))[i]));
    }

    c=len(a);

    return 0;
}


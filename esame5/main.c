#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include "help.h"

void rotate(int v[], int dim, int multiplo, int passi, int destra){
    int i,j;
    int u[8], k[8], du;

    j=0;
    for(i=0;i<dim;i++){
        
        if(v[i]%multiplo==0){
            u[j]=v[i];
            j++;
        }
    }
    du=j;

    if(destra==1){
    for(i=passi;i<du;i++){
        k[i]=u[i-passi];
    }
    for(i=0;i<passi;i++){
        k[i]=u[i+du-passi];
    }
    }
    else{
        for(i=0;i<du-passi;i++){
            k[i]=u[i+passi];
        }
        for(i=du-passi;i<du;i++){
            k[i]=u[i-du+passi];
        }
    }


    j=0;
    for(i=0;i<dim;i++){
        
        if(v[i]%multiplo==0){
            v[i]=k[j];
            j++;
        }
    }

}


void sort(int V[], int dim){
    int i,j, temp;

    for(j=0;j<dim-1;j++){
    for(i=0;i<dim-j;i++){
        if(V[i]>V[i+1]){
            temp=V[i+1];
            V[i+1]=V[i];
            V[i]=temp;
        }
    }
    }

}

int main(){
    int V[8]={1,2,3,4,5,6,7,8};

    rotate(V, 8, 2, 2, 0);
    sort(V, 8);

}
//errori
//azzerrare nel posto giustoo rispetto a for e if
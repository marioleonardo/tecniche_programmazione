#include <stdio.h>

int main(){
    int n1, n2;

    printf("Inserisci 2 numeri interi separati da uno spazio: ");
    scanf("%d%d", &n1, &n2);

    while(n1!=0 && n2!=0){
        if(n1>n2)
            n1=n1%n2;
        else
            n2=n2%n1;
    }
    printf("Il massimo comun divisore è: %d\n", (n1!=0) ? n1 : n2);
    return 0;
}
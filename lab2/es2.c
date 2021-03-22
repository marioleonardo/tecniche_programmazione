#include <stdio.h>

int main(){
    int numeri, n0=0, n1=1, n2;

    printf("inserisci N: ");
    scanf("%d", &numeri);
    printf("sucessione: %d %d", n0, n1);
    while(numeri>2){
        n2=n1+n0;
        n0=n1;
        n1=n2;
        printf(" %d", n2);
        numeri--;
    }
}
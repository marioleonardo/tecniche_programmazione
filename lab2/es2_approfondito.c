#include <stdio.h>

int main(){
    long double numeri=23, n0=1, n1=2, n2;

    //printf("inserisci N: ");
    //scanf("%ld", &numeri);
    //printf("sucessione: %ld %ld", n0, n1);
    while(numeri>2){
        n2=n1*n0;
        n0=n1;
        n1=n2;
        //printf(" %ld", n2);
        numeri--;
    }
}
/* 
APPRODONDIMENTO: 
si acquisiscono al massimo 10 numeri, l ultimo ha 7 cifre 

128 bit: 618970019642690137449562112 (12 numeri)

double: 1.307993905256674e+297 (17 numeri)

long double: 1.18667703531283012186e+3295 (22 numeri)
*/

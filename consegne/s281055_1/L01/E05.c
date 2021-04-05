#include <stdio.h>

int main(){
    float op1, op2, result;
    char operation;

    printf("Inserisci l'operatore e i due operandi separati da uno spazio:\n");
    operation = getchar();
    scanf("%f %f", &op1, &op2);

    if(operation=='+')          
        result=op1+op2;
    else if(operation=='-') 
        result=op1-op2;
    else if(operation=='*')
        result=op1*op2;
    else if(operation=='/'){
        if(op2==0){
            printf("E' impossibile dividere per zero!\n\n");
            return 1;
        }
        else
            result=op1/op2;
    }
    else return 1;

    printf("%c %.2f\n",operation, result);
    return 0;
}

/* 

Approfondimento: Cosa succede quando op2 è uguale a 0?

viene restituito inf quindi bisogna gestire separatamente il caso.

*/
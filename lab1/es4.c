#include <stdio.h>

#define Pi 3.14

int main(){
    char forma, dato;
    int numero, area;
    printf("Calcolo Area quadrato(Q) o cerchio(C)?\n");
    scanf("%c", &forma);
    switch(forma){
        case 'Q':
            printf("Calcolo Area quadrato da lato(L) o diagonale(D)\n");
            break;
        case 'C':
            printf("Calcolo Area cerchio da raggio(R) o diametro(D)\n");
            break;
        default:
            printf("errore inserimento\n");
            return(1);
            break;
    }

    scanf(" %c", &dato);
    printf("Inserire valore: ");   scanf("%d", &numero);

    switch(forma){
        case 'Q':
            if(dato=='L')   area=numero*numero;
            if(dato=='D')   area=numero*numero/2;
            break;
        case 'C':
            if(dato=='R')   area=Pi*numero*numero;
            if(dato=='D')   area=Pi*numero*numero/4;
            break;
        default:
            printf("errore inserimento\n");
            return(2);
            break;
    }
    printf("area: %d\n", area);
    return 0;
}

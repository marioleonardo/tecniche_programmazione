#include <stdio.h>

int main(){
    FILE *input;
    FILE *output;
    float op1, op2, result;
    char operation;

    input = fopen("./Operations.txt", "r");
    output= fopen("./Output.txt", "w");

    if(input==NULL || output==NULL)     return 1;


    while(!feof(input)){
        
        fscanf(input, "%c%f%f", &operation, &op1, &op2);
        while(!feof(input) && fgetc(input)!='\n');
        if(!feof(input)){
            if(operation=='+')          
                result=op1+op2;
            else if(operation=='-') 
                result=op1-op2;
            else if(operation=='*')
                result=op1*op2;
            else if(operation=='/')
                result=op1/op2;
            else return 1;
            fprintf(output, "%c %.2f\n", operation, result);
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}

/* 

Approfondimento: Cosa succede quando op2 è uguale a 0?

viene restituito inf quindi essendo corretto il risultato non dobbiamo verificare che sia corretta

*/
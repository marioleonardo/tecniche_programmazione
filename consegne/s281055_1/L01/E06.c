#include <stdio.h>

int main(){
    FILE *input;
    FILE *output;
    float op1, op2, result;
    char operation;

    input = fopen("Operations.txt", "r");
    output= fopen("Output.txt", "w");

    if(input==NULL || output==NULL)     return 1;

    
    while( fscanf(input, "%c%f%f", &operation, &op1, &op2) > 2 ){

        //Rimuoviamo eventuali spazi, \n e caratteri erronei dopo l'ultimo operando
        while(!feof(input) && fgetc(input)!='\n');

        if(operation=='+')          
            result=op1+op2;
        else if(operation=='-') 
            result=op1-op2;
        else if(operation=='*')
            result=op1*op2;
        else if(operation=='/'){
            if(op2==0){
                fprintf(output, "E' impossibile dividere per zero!\t");
                result=0;
            }
            else
                result=op1/op2;
        }
        fprintf(output, "%c %.2f\n", operation, result);
        
    }
    fclose(input);
    fclose(output);
    return 0;
}

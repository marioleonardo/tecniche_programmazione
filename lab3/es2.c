#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isinstring(char *string, char character);

int main(){
    FILE *fp_read, *fp_write;
    char character, lastSignificantChar, oldCharacter;
    int parenthesis=0, errorFound, indexExpression=0;


    

     if((fp_read=fopen("input.txt", "r"))==NULL ||  (fp_write=fopen("text.txt", "w"))==NULL){
        printf("Error opening file\n");
        return 1;
    }
    
    while(!feof(fp_read)){
        character=fgetc(fp_read);

        if(character=='(')
            parenthesis++;
        if(character==')')
            parenthesis--;
        if(!isspace(character) && character !='\n' && character!=EOF){
            if(isdigit(lastSignificantChar) && isdigit(character) && isspace(oldCharacter))
                errorFound=1;
            if(lastSignificantChar == '(' && !isdigit(character) && character!='(')
                errorFound=1;
            if(lastSignificantChar == ')' && !isinstring("%/+-*", character) && character!=')')
                errorFound=1;
        }

        if(character == '\n' || character == EOF || errorFound){
            if(character != '\n' && character != EOF)
                for(char i=fgetc(fp_read); i != '\n' && i!= EOF; i=fgetc(fp_read));
            if(lastSignificantChar != ')' && !isdigit(lastSignificantChar))
                errorFound=1;
            if(!(parenthesis==0))
                errorFound=1;
            if(errorFound){
                if(isdigit(character))
                    printf("Errore nella lettura di un numero (espressione %d)\n", indexExpression + 1);
                else
                    printf("Errore nella lettura di un operatore (espressione %d)\n", indexExpression + 1);
            }
            errorFound=0;
            parenthesis=0;
            indexExpression++;
            
        }

        if(!isspace(character) )  
            lastSignificantChar=character;
        oldCharacter=character;
    }
    


    fclose(fp_write);   fclose(fp_read);

    return 0;
}

int isinstring(char *string, char character){
    for(int i=0; string[i]!='\0'; i++){
        if(character==string[i])
            return 1;
    }
    return 0;
}
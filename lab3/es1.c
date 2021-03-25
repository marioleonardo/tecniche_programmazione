#include <stdio.h>
#include <ctype.h>

int isPunctuation(char character);

int isSpace(char character);

int main(){
    FILE *fp_read, *fp_write;
    char character;
    int addSpace, capitalize, counterChar;

     if((fp_read=fopen("input.txt", "r"))==NULL ||  (fp_write=fopen("text.txt", "w"))==NULL){
        printf("Error opening file\n");
        return 1;
    }
    
    addSpace = 0;   capitalize=0;
    counterChar = 0;

    while((character=fgetc(fp_read))!=EOF){

        if(addSpace && !isSpace(character) && counterChar != 25)
            counterChar += fprintf(fp_write, "%c", ' ');
        addSpace = 0;

        if(capitalize && isalpha(character)){
            character = toupper(character);
            capitalize = 0;
        }

        if(counterChar == 25 && character != '\n'){
            fprintf(fp_write, " | c:%d\n", 25);
            counterChar = 0;
        }
        
        if(character>='0' && character<='9')    
            character='*';

        if(isPunctuation(character))
            addSpace=1;
            
        if(character=='.' || character=='?' || character=='!')
            capitalize = 1;

        if(character=='\n'){
            for(int remaining = counterChar ; remaining<25; remaining += fprintf(fp_write, "%c", ' '));
            fprintf(fp_write, " | c:%d\n", counterChar + 1);
            counterChar= 0;
        }
        else
            counterChar += fprintf(fp_write, "%c", character);

    }

    if(counterChar>0){
        for(int remaining = counterChar ; remaining<25; remaining += fprintf(fp_write, "%c", ' '));
        fprintf(fp_write, " | c:%d\n", counterChar);
    }

    fclose(fp_write);   fclose(fp_read);

    return 0;
}

int isPunctuation(char character){
    return (character=='.' || character==',' || character==';' || character==':' || character=='!' || character=='?');
}

int isSpace(char character){
    return (character==' ' || character=='\n');
}


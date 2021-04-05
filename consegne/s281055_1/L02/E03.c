#include <stdio.h>
#include <string.h>

int comprimi(FILE *fin, FILE *fout);
int decomprimi(FILE *fin, FILE *fout);

int main(){
    FILE *fp_read, *fp_write;
    char scelta[20], file_read[20], file_write[20];

    printf("FORMATO CODIFICA: codifica input output\nFORMATO DECODIFICA: decodifica input output \n\n");
    scanf("%s %s %s", scelta, file_read, file_write);

    if((fp_read=fopen(file_read, "r"))==NULL ||  (fp_write=fopen(file_write, "w"))==NULL){
        printf("Error opening file\n");
        return 1;
    }
    
    if(strcmp(scelta, "codifica")==0)
        printf("Sono stati stampati: %d caratteri\n\n", comprimi(fp_read, fp_write));
    if(strcmp(scelta, "decodifica")==0)
        printf("Sono stati stampati: %d caratteri\n\n", decomprimi(fp_read, fp_write));

    fclose(fp_read); fclose(fp_write);
    return 0;
}

int comprimi(FILE *fin, FILE *fout){
    int numRepetitions, printedCount;
    char nextCharacter, character;
    
    numRepetitions=0; printedCount=0;
    character=fgetc(fin);
    while(!feof(fin)){
        nextCharacter=fgetc(fin);
        if(nextCharacter==character && numRepetitions<9)
            numRepetitions++;
        else{
            if(numRepetitions>1)
                printedCount += fprintf(fout, "%c$%d", character, numRepetitions);
            else if(numRepetitions==1)
                printedCount += fprintf(fout, "%c%c", character, character);
            else
                printedCount += fprintf(fout, "%c", character);
            numRepetitions=0;
        }
        character=nextCharacter;
    }
    return printedCount;
}

int decomprimi(FILE *fin, FILE *fout){
    int numRepetitions, printedCount;
    char oldCharacter, character;
    
    numRepetitions=0; printedCount=0;
    while((character=fgetc(fin)) != EOF ){
        if(character=='$'){  
            fscanf(fin, "%1d", &numRepetitions);
            if(numRepetitions<2)    return 0;
            for(int j=0 ; j<numRepetitions; j++)  
                printedCount += fprintf(fout, "%c", oldCharacter);
        } else{
            printedCount += fprintf(fout, "%c", character);
        }
        oldCharacter=character;
    }
    return printedCount;
}


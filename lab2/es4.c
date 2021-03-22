#include <stdio.h>
#include <ctype.h>  
#include <string.h>

int codifica(FILE *fin, FILE *fout);
int decodifica(FILE *fin, FILE *fout);

int main(){
    FILE *fp_read, *fp_write;
     char scelta[20], file_read[20], file_write[20];
    
    printf("FORMATO: codifica input output\nFORMATO: decodifica input output \n\n");
    scanf("%s %s %s", scelta, file_read, file_write);

    if((fp_read=fopen(file_read, "r"))==NULL ||  (fp_write=fopen(file_write, "w"))==NULL){
        printf("Error opening file\n");
        return 1;
    }

    if(strcmp(scelta, "codifica")==0)
        printf("Sono stati stampati: %d caratteri\n\n", codifica(fp_read, fp_write));
    if(strcmp(scelta, "decodifica")==0)
        printf("Sono stati stampati: %d caratteri\n\n", decodifica(fp_read, fp_write));
        
    fclose(fp_read); fclose(fp_write);
    return 0;
}

int decodifica(FILE *fin, FILE *fout){
    int k, printedCount, temp_character;
    char c0, character;
    k=0;

    while((character=fgetc(fin)) != EOF){
        temp_character=character;
        if(character>='0' && character<='9'){
            character= '0' + ((character-'0') - k + 10 ) % 10;
            k=(k+1)%10;
        } else if(islower(character) && isalpha(c0)){
            c0= c0<'a' ? c0 + ('a' - 'A') : c0 ;   
            character=  'a' + (character - c0 + 26 ) % 26;  
        } else if(isupper(character) && isalpha(c0)){
            c0= c0<'a' ? c0 : c0 + ('a' - 'A');
            character=  'A' + (character - c0 + 26 ) % 26;
        }
        fputc(character, fout);
        printedCount++;
        c0=temp_character;
    }
    return printedCount; 
}

int codifica(FILE *fin, FILE *fout){
    int k, printedCount;
    char c0, character;
    k=0;
    while((character=fgetc(fin)) != EOF){
        if(character>='0' && character<='9'){
            character= '0' + ((character-'0') + k ) % 10;
            k=(k+1)%10;
        } else if(islower(character) && isalpha(c0)){
            c0= c0<'a' ? c0 + ('a' - 'A') : c0 ;
            character=  'a' + (character + c0 - 2*'a' ) % 26;
        } else if(isupper(character) && isalpha(c0)){
            c0= c0<'a' ? c0 : c0 + ('a' - 'A');
            character=  'A' + (character + c0 - 2*'A' ) % 26;
        }
        fputc(character, fout);
        printedCount++;
        c0=character;
    }
    return printedCount;
}
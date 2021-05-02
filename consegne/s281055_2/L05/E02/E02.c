#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define file_dict "..\\text\\dizionario.txt"
#define file_source "..\\text\\sorgente.txt"
#define file_write "..\\text\\ricodificato.txt"
#define MAX_CHAR_LINE 200
#define MAX_SUB_DICT 30
#define MAX_CHAR_WORD_DICT 10

typedef struct {
    char input[MAX_CHAR_WORD_DICT+1];
    char output[MAX_CHAR_WORD_DICT+1];
} Rule;

int readDict(FILE *fp, Rule dict[]);

int findWord(char line[], int indexMain, Rule dict[], int lenDict, char compressedWord[]);

void encodeLine(char line[], char newLine[], Rule dict[], int lenDict);

int main(){
    int index;
    char line[MAX_CHAR_LINE+1], newLine[MAX_CHAR_LINE+1], lenDict;
    Rule dict[MAX_SUB_DICT];
    FILE *fp_read_dict, *fp_read_source, *fp_write;

    if((fp_read_dict=fopen(file_dict, "r"))==NULL || (fp_read_source=fopen(file_source, "r"))==NULL || 
       (fp_write=fopen(file_write, "w"))==NULL){
            printf("Errore file input");
            return 1;
    }

    // readDict() inserts the dictionary in dict array and returns the length of the array 
    lenDict=readDict(fp_read_dict, dict);
    fclose(fp_read_dict);

    // it gets a line, encodes it in newline which is written in fp_write
    while( fgets(line, MAX_CHAR_LINE, fp_read_source) != NULL ){
        encodeLine(line, newLine, dict, lenDict);
        fputs(newLine, fp_write);
    }
    
    fclose(fp_read_source);     fclose(fp_write);
    return 0;
}

int readDict(FILE *fp, Rule dict[]){
    int counter, index;
    fscanf(fp, "%d ", &counter);
    for(index=0 ; index<counter; index++)
        fscanf(fp, "%s %s", dict[index].output, dict[index].input);

    return counter;
}

void encodeLine(char line[], char newLine[], Rule dict[], int lenDict){
    char chr, compressedWord[MAX_CHAR_WORD_DICT+1];
    int indexMain, indexNewLine, lenReplacedWord;
    
    indexNewLine=0;
    for(indexMain=0, chr=line[indexMain]; chr != '\0' && indexMain<MAX_CHAR_LINE+1;
        indexMain++, chr=line[indexMain]){
        
        lenReplacedWord=0;
        if(isalpha(chr)){
            lenReplacedWord = findWord(line, indexMain, dict, lenDict, compressedWord);
        }
        if(lenReplacedWord>0){
            strcat(newLine, compressedWord);
            indexNewLine+=strlen(compressedWord);
            indexMain+=lenReplacedWord;
        }
        else{
            newLine[indexNewLine]=chr;
            indexNewLine++;
            newLine[indexNewLine]='\0';
        }
    }
    
}

int findWord(char line[], int indexMain, Rule dict[], int lenDict, char compressedWord[]){
    char lineChar, dictChar;
    int  searchIndex, word, match, finito, matchFound;

    matchFound=0;
    for(word=0; word<lenDict && !matchFound; word++){
        searchIndex=-1;
        do{
            searchIndex++;
            lineChar=line[indexMain+searchIndex];
            dictChar=dict[word].input[searchIndex];

            match=lineChar==dictChar;
            finito = (!isalpha(lineChar)||(dictChar=='\0'));
        } while(match && !finito);

        if(dictChar=='\0'){
            strcpy(compressedWord,dict[word].output);
            matchFound=1;
        } else{
            searchIndex=0;
        }
    }
    return --searchIndex;
}
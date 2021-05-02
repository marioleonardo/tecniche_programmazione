#include <stdio.h>
#define filetext ".\\text\\sequenze.txt"
#define filedict ".\\text\\testo.txt"
#define MAX_CHAR_WORD 20
#define MAX_CHAR_LINE 200
#define SIZE_DICT 20

int firstSubStr(char str[], char word[], int start);

int main(){
    FILE *fp_dict, *fp_read;
    int indexWord, lenDict, lastFound, counter;
    char line[MAX_CHAR_LINE+1], dict[SIZE_DICT][MAX_CHAR_WORD+1];

    if((fp_read=fopen(filetext,"r"))==NULL || (fp_dict=fopen(filedict, "r"))==NULL){
        printf("Errore file");
    }

    for(indexWord=0; fscanf(fp_dict, "%s", dict[indexWord]); indexWord++);
    lenDict=indexWord;

    while(fgets(fp_read, MAX_CHAR_LINE, line)!=NULL){
        for(indexWord=0 ; indexWord < lenDict ; indexWord++){  
            for(counter=0, lastFound=-1 ; counter <= 10 && lastFound!=-1; counter++){
                lastFound = firstSubStr(line , dict[indexWord], lastFound+1);
                if(lastFound != -1 && counter == 0)     printf("La sequenza %s è contenuta in:", dict[indexWord]);
                if(lastFound != -1 )                    printf(" posizione %d,", indexWord);
            }
        }   
    }
    
    
    return 0;
}

int firstSubStr(char str[], char word[], int start){

    
}
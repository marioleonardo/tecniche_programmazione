#include <stdio.h>
#define filetext "..\\text\\testo.txt"
#define filedict "..\\text\\sequenze.txt"
#define MAX_CHAR_WORD 20
#define MAX_CHAR_LINE 200
#define SIZE_DICT 20

int firstSubStr(char str[], char word[], int start);

int main(){
    FILE *fp_dict, *fp_read;
    int indexWord, lenDict, lastFound, counter, numLine, empty;
    char line[MAX_CHAR_LINE+1], dict[SIZE_DICT][MAX_CHAR_WORD+1];

    if((fp_read=fopen(filetext,"r"))==NULL || (fp_dict=fopen(filedict, "r"))==NULL){
        printf("Errore file");
    }

    for(indexWord=0; fscanf(fp_dict, "%s", dict[indexWord])!=EOF; indexWord++);
    lenDict = indexWord;
    numLine=0;

    while(fgets(line, MAX_CHAR_LINE, fp_read)!=NULL){
        for(indexWord=0 ; indexWord < lenDict ; indexWord++){  
            counter=0;
            for(counter=0, lastFound=-1, empty=0 ; counter <= 10 && !empty; counter++){
                lastFound = firstSubStr(line , dict[indexWord], lastFound+1);
                if(lastFound > -1 && counter == 0)     printf("[RIGA : %d] La sequenza %s è contenuta in:", numLine, dict[indexWord]);
                if(lastFound > -1 )                    
                    printf(" posizione %d,", lastFound);
                if(lastFound==-1)   empty=1;
            }
            if(counter > 1)     printf("\b.\n");
        }   
        numLine++;
    }
    
    
    return 0;
}

int firstSubStr(char str[], char word[], int start){
    int i, j, finito, valid;

    for(i=start ; str[i]!='\0' ; i++){
        valid=1;
        for(j=0 ; valid && word[j]!='\0' ; j++){
            if(str[i+j] != word[j])     valid=0;
        }
        if(valid)   
            return i;
    }

    return -1;
}
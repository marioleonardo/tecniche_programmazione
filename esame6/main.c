#include <stdio.h>
#include <string.h>
#include <ctype.h>

void changeWord(FILE *fp, FILE *fpw, char word1[],char word2[]){
    int i,j, len;
    char line[201], newLine[201];
    char *start;
    
    while(fgets(line, 200, fp)!=NULL){
        len=strlen(word1);


        while((start=strstr(line, word1))!=NULL){
            for(i=0;i<len && word2[i]!='\0'; i++){
                *(start+i)= word2[i];
            }
            if(len<strlen(word2)) {
                insertStr(start+len, &word2[len]);
            }
            if(len>strlen(word2)){
                shortStr(start+strlen(word2), len-strlen(word2));
            }
            
        }

        fputs(line, fpw);
    }
    
}

void insertStr(char *line, char * word){
    int i,j,l1, l2;
    char newLine[200];

    l1=strlen(word);
    l2=strlen(line);

    strcpy(newLine, word);
    strcat(newLine, line);
    strcpy(line, newLine);
}

void shortStr(char *start, int len){
    int i;

    *start='\0';
    strcat(start, start+len);
}

int main(){
    char word[20], rep[20];
    FILE *fpr, *fpw;

    fpw=fopen("out.txt", "w");
    fpr=fopen("text.txt", "r");
    printf("Enter word to change: ");
    scanf("%s %s", word, rep);
    changeWord(fpr, fpw, word, rep);
}

//errori
//virgola posto ;
//strlen posizione \0
// ++ al posto di --
// elemento dichiarato al posto del vettore
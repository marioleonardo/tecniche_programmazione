#include <stdio.h>
#include <string.h>

char* removeSpaces(char text[200]);

int main() {

    char fileName[100]="//home//mario//OneDrive//code//C//Tecniche programmazione//input.txt";
    char text[200], *newText;
    char tmp;
    int index;
    FILE *fp;
    fp= fopen(fileName, "r");
    tmp=fgetc(fp);
    ungetc(tmp, fp);
    while(tmp!=EOF && index<200){
        tmp= fgetc(fp);
        text[index]=tmp;
        index++;
    }
    printf("%c\n", text[strlen(text)-4]);
    newText=removeSpaces(text);
    printf("%s", newText);
    fclose(fp);
    



    return 0;
}

char* removeSpaces(char text[200]){
    int index=0;
    int indexRemover;
    int length =strlen(text);
    while(text[index]!='\0' && index<=length){

        if(text[index]=='\n' || text[index]==' '){
            
            indexRemover=index;
            while(text[indexRemover]!='\0'  && indexRemover<=length){
                text[indexRemover]=text[indexRemover+1];
                indexRemover++;
            }
            index--;
        }
        index++;
    } 

    return text;
}

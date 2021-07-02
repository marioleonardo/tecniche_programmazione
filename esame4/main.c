#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include "help.h"

void censure(FILE *fpr, FILE *fpw, FILE *fpd){
int i,j,found,ldict,lword;
char dict[50][50], input[200];
char * start;

i=0;
while(fscanf(fpd," %s ",dict[i])!=EOF){
i++;
}
ldict=i;

while(fgets(input, 199, fpr)!=NULL){




for(i=0;i<ldict && !feof(fpr);i++){
start=strstr(input, dict[i]);

while(start!=NULL){
lword=strlen(dict[i]);
for(j=0;j<lword-2;j++){
*(start+j+1)='*';
}
start=strstr(input, dict[i]);

}
}

fputs(input,fpw);
}

}
int main(){

    FILE *fpr; fpr=fopen("text.txt", "r");
    FILE *fpd; fpd= fopen("dict.txt", "r");
    FILE *fpw; fpw= fopen("output.txt", "w");

    censure(fpr, fpw, fpd);
    fclose(fpw);
}
//errori
//fclose
// r or w inf FILE
//1 al posto di i
//strstr sscanf bisogna starci attenti

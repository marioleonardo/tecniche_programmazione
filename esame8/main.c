#include <stdio.h>
#include <ctype.h>

int main(){
    int i;
    char chr, vec[201];
    while(gets(vec) && vec[0]!='\n'){
        i=0;
    while((chr=vec[i])!='.' && vec[i]!='\0'){
        if(isalpha(chr))
            chr= (chr-'A')%('A'-'a')+'a';
        vec[i]=chr;
        i++;
    }
        puts(vec);
    }
    
}
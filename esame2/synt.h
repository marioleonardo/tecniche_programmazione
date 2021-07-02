#include <stdio.h>

void achr(char target[], char chr){
    int len;

    len=strlen(target);
    target[len]=chr;
    target[len+1]='\0';
}

int in(char str[], char target){
    int i;

    for(i=0;str[i]!='\0';i++){
        if(target == str[i]){
            return 1;
        }
    }

    return 0;
}

void autoFormat(FILE *fpr, FILE *fpw){
    int i,j, len,inW, inFor,level, inString,singleSpace=0,inPrep;
    char c, cout, word[20], spacer[20], sentenceIn[201], sentenceOut[201];

    level=0;
    inString=0;
    while(fgets(sentenceIn, 200 ,fpr)!=NULL){
        sentenceOut[0]='\0';
        inW=0;
        inFor=0;
        singleSpace=0;
        
        if(sentenceIn[0]=='#')
            inPrep=1;
        else
            inPrep=0;
        
        for(i=0;sentenceIn[i]!='\n'  && sentenceIn[i]!= '\0';i++){
            c=sentenceIn[i];

            if(inW>0  && !inString  && isalnum(c)){
                word[inW]=c;
                word[inW+1]='\0';
                inW++;
            }

            if(inW==0  && !inString  && isalnum(c)){
                inW=1;          
                word[0]=c;	word[1]='\0';
            }
            
            if(inW>0 && !inString && !(isalnum(c) || isdigit(c) || in("_[]();,",c))){
                inW=0;
                word[inW]='\0';
                if(!singleSpace)
                    achr(sentenceOut, ' ');
                singleSpace=1;
            }
            
            if(strncmp(word, "for", 3)==0){
                inFor=2;
            }
            
            if(!isspace(c) && c!='}' && !inString && !inPrep && !feof(fpr)) {
                achr(sentenceOut, c);
                singleSpace=0;
            }

            if(inString && !in("\"\'", c)){
                achr(sentenceOut, c);
                c='\0';
            }

            if(inPrep){
                achr(sentenceOut, c);
                c='\0';
            }

            if(c==';' && inFor<1){
                strcat(sentenceOut, "\n");
                strcat(sentenceOut, spacer);
                singleSpace=1;
            }   else if(c=='{'){
                inFor=0;
                level++;
                for(j=0;j<level;j++){
                    spacer[j]='\t';
                }
                spacer[j]='\0';
                strcat(sentenceOut, "\n");
                strcat(sentenceOut, spacer);
            }   else if(c=='}'){
                level--;
                for(j=0;j<level;j++){
                    spacer[j]='\t';
                }
                spacer[j]='\0';
                strcat(sentenceOut, "\n");
                strcat(sentenceOut, spacer);
                strcat(sentenceOut, "}");
                strcat(sentenceOut, "\n");
                strcat(sentenceOut, spacer);
            }
            else if(c=='\"' || c=='\''){
                inString = !inString;
                if(!inString){
                    achr(sentenceOut, c);
                    achr(sentenceOut, ' ');
                }
            }
            else if(in("+-*/=&<>|\'\"",c) && !in("=+-*/&|",sentenceIn[i+1])){

                strcat(sentenceOut, " ");
            }
            else if(c==','){
                if(!singleSpace)
                    strcat(sentenceOut, " ");
                singleSpace=1;
            }

        }
	
	//fine while

    fprintf( fpw, "%s",sentenceOut);
    sentenceOut[0]='\0';
    if(inPrep){
        fprintf(fpw, "%s", "\n");
    }
    }

}


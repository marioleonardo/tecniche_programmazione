// Raccolgo in un secondo file i prototipi
#include <stdio.h>
#include <string.h>
#include <ctype.h>

prototypeCopy(FILE *fpr,FILE *fpw){
	int i,j,graffe,tonde,inWord, prep, proto,fun,var, args;
	char vec[500][40], line[200], function[60], variable[30], chr, word[30];
	char types[2][20]={"int", "char"};
	
	
	graffe=0;	inWord=0;	prep=0;
	while((chr=fgetc(fpr)) && !feof(fpr) && graffe=0){
	
	
	switch(chr){
	case '{':
	graffe++;
	break;
	case '}':
	graffe--;
	break;
	case ')':
	tonde--;
	break;
	case '(':
	tonde++;
	break;
	case '#':
	prep=1;
	break;
	}
	
	if(inWord<1 && isalpha(chr)){
		word[0]=chr;
		inWord=1;
	}
	if(inWord && (isalnum(chr) || chr=='_')){
		word[inWord]=chr;
		inWord++;
	}
	else if(inWord){
		word[inWord]='\0';
		if(in(word, types) && tonde=0){
			strcat(function, word);
			strcat(function, " ");
			fun=1;
			prep=0;
		}
		if(fun==1){
			strcat(function, word);
			fun=0;
			args=1;
		}
		if(tonde>0 && args==1){
			strcat(function, "(");
			strcat(function, word);
			args++;
		}
		if(tonde==0 && args>0){
			strcat(function, ')');
			fun=0;
		}
		if(tonde>0 && args>0){
			strcat(function, word);
			args++;
		}
		if(in(word, types) && graffe>0){
			fun=0;
			prep=0;
			var=1;
		}
		inWord=0;
	}
	
	}
}

int main(){
    char vec[300][20];
    FILE *fpr, *fpw;

    fpr=fopen("text.txt", "r");
    fpw=fopen("out.txt", "w");

    prototypeCopy(fpr,fpw);

}
void censure(FILE *fpr, FILE *fpw, FILE *fpd){
int i,j,found,ldict,lword;
char dict[50][50], input[200];
char * start;

i=0;
while(fscanf(fpd,"%s",dict[i])){
i++;
}
ldict=i;

while(fgets(input, 199, fpr)!=NULL){



for(i=0;i<ldict;i++){
start=strstr(input, dict[i]);

if(start!=NULL){
lword=strlen(dict[i]);
for(j=0;j<lword-2;j++){
*(start+j+1)='*';
}
}
}

fputs(input,fpw);
}

}
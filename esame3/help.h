int wordsInLine(char v[]){

int i,j,ctr=0,s=0;

char c;



for(i=0;v[i] != '\0';i++){

    c=v[i];

    if(isalpha(c) && s=0){

s=1;

ctr++;

}

if(!isalnum(c) && s==1){

s=0;

}

        

       //fine for

}

    return ctr;

}

int maxWordsInLine(char v[]){

int i,j,dim=0,max,maxPos,ctr=0,s=0;

char c;



for(i=0;v[i] != '\0';i++){

    c=v[i];

    if(isalpha(c) && s=0){

s=1;

dim++;

ctr++;

}

if(isalnum(c) && s==1){

dim++;

}



if(!isalnum(c) && s==1){

max= max<dim ? dim : max;

maxPos= max<dim? ctr : maxPos ;

s=0;

dim=0;

}

        if(s=1){

max= max<dim?dim:max;

maxPos=max<dim ? ctr:maxPos;

}

       //fine for

}

    return --maxPos;

}

void printMax(char v[]){

int i,j,dim=0,max,maxPos,ctr=0,s=0;

char c, temp;



for(i=0;v[i] != '\0';i++){

    c=v[i];

    if(isalpha(c) && s=0){

s=1;

dim++;

ctr++;

}

if(isalnum(c) && s==1){

dim++;

}



if(!isalnum(c) && s==1){

max= max<dim ? dim : max;

maxPos= max<dim? ctr : maxPos ;

s=0;

dim=0;

}

        if(s=1){

max= max<dim?dim:max;

maxPos=max<dim ? ctr:maxPos;

}

       //fine for

}

s=0;    dim=0;
for(i=0;v[i]!='\0';i++){
c=v[i];
if(isalpha(c) && s==0){
ctr++;
s=1;
j=i;
}
if(isalnum(c) && s==1){
dim++;
}
if(!isalnum(c) && s==1){
if(dim==max){
temp=v[i];
v[i]='\0';
printf("%s",&(v[j]));
v[i]=temp;
}
s=0;
dim=0;
}

}
if(s==1){
if(dim==max){
temp=v[i];
v[i]='\0';
printf("%s", &(v[j]));
v[i]=temp;
}
}


}
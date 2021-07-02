#define DEBUG 1
#define TOLL 0.000001
#include <stdio.h>

typedef float  vec3[3];
typedef float  vec4[4];
typedef float  mat4[4][4];
typedef float  mat3[3][3];
typedef enum{
fun,
arg
} stateRead;

void vec4Cl(vec4 v1){
	int i;

	for(i=0;i<4;i++){
		v1[i]=0;
	}

}



void vec4Sum(vec4 v1, vec4 v2, vec4 r){

	int i,j;



	for(i=0;i<4;i++){

   		r[i]=v1[i]+v2[i];
	}


	if(DEBUG){

		printf("%f%f%f%f", r[0], r[1], r[2], r[3]);
	}
}

void vec3Sum(vec3 v1, vec3 v2, vec3 r){

	int i,j;



	for(i=0;i<3;i++){

   		r[i]=v1[i]+v2[i];
	}


	if(DEBUG){

		printf("%f%f%f%f", r[0], r[1], r[2], r[3]);
	}
}


void vec4Scale(vec4 v1, float mult){

	int i;



	for(i=0;i<4;i++){

		v1[i]=v1[i]*mult;

	}



}

void vec3Scale(vec3 v1, int mult){

	int i;



	for(i=0;i<3;i++){

		v1[i]=v1[i]*mult;

	}



}


float vec4Dot(vec4 v1, vec4 v2){

	int i,res;
	


	res=0;

	for(i=0;i<4;i++){

		res+=v1[i]*v2[i];

	}



	return res;

}


float vec3Dot(vec3 v1, vec3 v2){

	int i,res;
	


	res=0;

	for(i=0;i<3;i++){

		res+=v1[i]*v2[i];

	}



	return res;

}

void vec3Mult(vec3 v1,vec3 v2,vec3 r){

int i;



r[0]=v1[1]*v2[2]-v1[2]*v2[1];

r[1]=-v1[0]*v2[2]+v1[2]*v2[0];

r[2]=v1[0]*v2[1]-v1[1]*v2[0];

}

float det(float *m1, int dimr, int dimc){
int i,j,k,m;
float result;

	for(i=0;i<dimr-1;i++){
		for(j=i+1;j<dimr;j++){
			m=*(m1+j*dimc+i) / *(m1+i*dimc+i);
			for(k=i;k<dimc;k++){
				*(m1+j*dimc+k)-=(*(m1+i*dimc+k))*m;
			}
		}
	}
	
	result=1;

	for(i=0;i<dimr;i++){
		result=result * (*(m1+i*dimc+i));
	}
	return result;
}

void menuScelta(){
int i,j,argctr,stopPos;
float argvec[10],result;
char command[51], action[20],arg1[20], chr,len;
stateRead state;
action[0]='\0';
state=fun;
argctr=0;

printf("\nInserisci la funzione: ");
while(fgets(command, 50, stdin)!=NULL){

for(i=0;i<strlen(command);i++){
if(!isspace(command[i])){

if(isalpha(command[i]) && state==fun){
len=strlen(action);
action[len]=command[i];
action[len+1]='\0';
}
if(command[i]=='(' && state==fun){
state=arg;
}
if(command[i]==')' && state==arg){
sscanf(arg1,"%f", &argvec[argctr]);
state=fun;
}
if(command[i]==',' && state==arg){
sscanf(arg1,"%f", &argvec[argctr]);
argctr++;
arg1[0]='\0';
}
if((isdigit(command[i]) || command[i]=='.' || command[i]=='E' || command[i]=='+' || command[i]=='-') && state==arg){
len=(strlen(arg1));
arg1[len+1]='\0';
arg1[len]=command[i];
}

//for e if
}
}

if(strcmp(action, "vecSum") == 0)	result=argvec[0] + argvec[1];

printf("\nIl risultato e' %f\n", result);

printf("\nInserisci la funzione: ");
//while e fine
}

}


int solveMB(float *mat, int r, int c, float *b, float *x){
int i,j,k;

//mat rxc X cx1 = rx1

if(det(mat,r,c)==0.0){
return 1;
}

if(istriu(mat,r,c)){
printf("triungular upper");
}

if(istril(mat,r,c)){
printf("triangular lower");
}

if(isdiag(mat,r,c)){
printf("diagonal")
}


}

int istriu(float *mat, int r, int c){
int i,j;

for(i=1;i<r;i++){
for(j=0;j<i && j<c;j++){
if(*(mat+i*c+j)>TOLL || *(mat+i*c+j)<-TOLL){
return 0;
}
}
}

return 1;
}

int istril(float *mat, int r, int c){
int i,j;

for(i=0;i<r;i++){
for(j=i+1;j<c;j++){
if(*(mat+i*c+j)>TOLL || *(mat+i*c+j)<-TOLL){
return 0;
}
}
}

return 1;
}


int isdiag(float *mat, int r, int c){
int i,j;

for(i=0;i<r;i++){
for(j=0;j<c;j++){
if(i!=j && (*(mat+c*i+j)>TOLL || *(mat+c*i+j)<-TOLL) ){
return 0;
}
}
}

return 1;
}




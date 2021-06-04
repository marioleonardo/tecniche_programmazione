#include <stdio.h>
#include <string.h>




void stampaCodifica(void *n, int size, int bigEndian);
void bitsToStr(unsigned char * n, int first, int last, char str[]);
void textToNumber(char sign[], char exp[], char mx[], int signBits, int expBits, int mxBits, char number[]);
void textToIntText(char *str, char *result, int len);

int main(){
    unsigned char * t1; 
    void *t;
    int bigEndian, test;
    float af;
    double ad;

    test=1;
    t1=(unsigned char *)&test;
    bigEndian = *(t1+3)>0;

    af = 23.45E12;
    ad = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

    stampaCodifica((void *)&af,sizeof(af),bigEndian);
    stampaCodifica((void *)&ad,sizeof(ad),bigEndian);

}

void stampaCodifica(void *n, int size, int bigEndian){
    int signBits, expBits, mxBits, index;
    char sign[2], exp[12], mx[53], text[65], temp[9], number[200];
    char *textPos;

    signBits=1;
    if(size==4){
        expBits = 8;
        mxBits  = 23;
    }
    if(size==8){
        expBits = 11;
        mxBits  = 52;
    }

    text[0]='\0';
    for(index = (size-1) - ((size-1) * bigEndian) ;index != bigEndian*(size)-1; index += bigEndian*2 -1){
        bitsToStr(n+index, 0, 7, temp);
        strcat(text, temp);
    }

    textPos=text;
    for(index=0 ;index<signBits; index++, textPos++){
        sign[index] = *textPos;
        sign[index+1] = '\0';
    }
    for(index=0 ;index<expBits; index++, textPos++){
        exp[index] = *textPos;
        exp[index+1] = '\0';
    }
    for(index=0 ;index<mxBits; index++, textPos++){
        mx[index] = *textPos;
        mx[index+1] = '\0';
    }
        

    printf("The sign bit is: %s\n", sign);
    printf("The exp bit is: %s\n", exp);
    printf("The mantissa bit is: %s\n", mx);

    textToNumber(sign, exp, mx, signBits, expBits, mxBits, number);

    printf("The number is %s", number);
}

void bitsToStr(unsigned char * n, int first, int last, char str[]){
    int index, ctr, resto;
    unsigned char num;

    num = *n;

    for(index=7, ctr=(last - first), str[ctr+1]='\0' ;index>-1; index--){
        resto = num%2;
        num=num/2;
        if(index>=first && index<=last){
            str[ctr] = resto == 1 ? '1' : '0';
            ctr--;
        }
    }
}

void textToNumber(char sign[], char exp[], char mx[], int signBits, int expBits, int mxBits, char * number){
    char *textPos;
    char temp[200];

    *number= *sign=='0' ? '+' : '-';
    number++;       *number='\0';


    strcat(number, " ");
    textToIntText(mx, temp, mxBits);
    strcat(number, temp);

    strcat(number, "E");
    textToIntText(exp, temp, expBits);
    strcat(number, temp);

}

void textToIntText(char *str, char *result, int len){
    int sign, num, bit, index;
    char *pos;

    *result = *str=='0' ? '+' : '-';
    str++;      result++;

    for(index=1, num=0 ;index<len && *str!='\0'; index++, str++){
        bit = *str == '0' ? 0 : 1;
        num *= 2;
        num +=bit;
    }

    *result='\0';
    sprintf(result, "%d", num);
}
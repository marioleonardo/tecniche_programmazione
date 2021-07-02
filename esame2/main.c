#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include ".\synt.h"

int main(){
    FILE * fp_read, * fp_write;
    fp_read=fopen(".\\input.txt","r");
    fp_write=fopen(".\\output.txt", "w");

    autoFormat(fp_read,fp_write);


}
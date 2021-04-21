#include <ctype.h>

void lower(char str[], int max){
    for(int j=0; j<max && str[j]!= '\0'; j++)    
           str[j] = tolower(str[j]);
}
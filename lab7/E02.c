#include <stdio.h>
#define filein "../text/sort.txt"
#define MAX_NUMS 100


void manageSort(int array[], int len);
void insertionSort(int arr[], int len);
void selectionSort(int arr[], int len);
void shellSort(int arr[], int len);

int main(){
    int S, length, list[MAX_NUMS], indexSeq, indexNum;
    FILE *fp_read;

    if((fp_read=fopen(filein, "r"))==NULL){
        printf("File error read");
    }

    fscanf(fp_read, "%d", &S);
    for(indexSeq=0 ;indexSeq<S; indexSeq++){
        fscanf(fp_read, "%d", &length);
        for(indexNum=0 ;indexNum<length; indexNum++){
            fscanf(fp_read, "%d", list[indexNum]);
        }
        manageSort(list, length);
    }
}

void manageSort(int array[], int len){
    int newArray[MAX_NUMS];
    int  
}

void insertionSort(int arr[], int len);
void selectionSort(int arr[], int len);
void shellSort(int arr[], int len);
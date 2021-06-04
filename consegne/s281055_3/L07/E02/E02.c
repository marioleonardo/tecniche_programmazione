#include <stdio.h>
#define filein "../text/sort.txt"
#define MAX_NUMS 100


void manageSort(int array[], int len);
void copyArr(int arrA[], int arrB[], int len);
void insertionSort(int arr[], int len);
void selectionSort(int arr[], int len);
void shellSort(int arr[], int len);
void printCounters(int main, int total, int shift, int list[]);

int main(){
    int S, length, indexSeq, indexNum, nums[MAX_NUMS];
    FILE *fp_read;

    if((fp_read=fopen(filein, "r"))==NULL){
        printf("File error read");
        return 1;
    }

    fscanf(fp_read, "%d", &S);
    for(indexSeq=0 ;indexSeq<S; indexSeq++){
        fscanf(fp_read, "%d", &length);
        for(indexNum=0 ;indexNum<length; indexNum++){
            fscanf(fp_read, "%d", &nums[indexNum]);
        }
        printf("Sorting sequenza %d: \n", indexSeq+1);
        manageSort(nums, length);
    }

    return 0;
}

void manageSort(int array[], int len){
    int index, newArray[MAX_NUMS];
    
    printf("[insertion sort]: ");
    copyArr(array, newArray, len);
    insertionSort(newArray, len);

    printf("[selection sort]: ");
    copyArr(array, newArray, len);
    selectionSort(newArray, len);

    printf("[shell sort]: ");
    copyArr(array, newArray, len);
    shellSort(newArray, len);

    printf("\n\n");
}

void copyArr(int arrA[], int arrB[], int len){
    int i;

    for(i=0 ;i<len; i++){
        arrB[i] = arrA[i];
    }
}

void insertionSort(int arr[], int len){
    int main, inner, foundPos;
    int counterMain=0, counterInner=0, counterShift=0, total=0, counterList[MAX_NUMS];
    int temp, i;

    for(main=1 ;main<len; main++){
        temp=arr[main];
        foundPos=0;
        for(inner=main ;inner>0 && !foundPos; inner--){
            if(temp>=arr[inner-1]){
                arr[inner]=temp;
                foundPos=1;
                counterShift++;
            }
            else{
                arr[inner]=arr[inner-1];
                counterShift++;
            }            
            counterInner++;
        }
        if(!foundPos){
            arr[0]=temp;
            counterShift++;
        }

        total+=counterInner;
        counterList[counterMain]=counterInner;
        counterMain++;
        counterInner=0;
    }

    printCounters(counterMain, total, counterShift, counterList);
}

void selectionSort(int arr[], int len){
    int main, inner, min, temp;
    int counterMain=0, counterInner=0, counterShift=0, total=0, counterList[MAX_NUMS];

    for(main=0 ;main<len; main++){
        min=main;
        for(inner=main ;inner<len; inner++){
            if(arr[inner]<arr[min]){
                min=inner;
            }
            counterInner++;
        }
        temp=arr[main];
        arr[main]=arr[min];
        arr[min]=temp;
        counterShift++;

        total+=counterInner;
        counterMain++;
        counterList[main]=counterInner;
        counterInner=0;
    } 

    printCounters(counterMain, total, counterShift, counterList);
}

void shellSort(int arr[], int len){
    int mainIndex, listIndex, innerIndex, temp, foundPos, height;
    int counterMain=0, counterInner=0, counterShift=0, total=0, counterList[MAX_NUMS];

    //sequenza di knuth O(N^3/2)
    for(height=1 ;height<len/3; height=3*height+1);
    for( ;height>=1; height = height/3){
        for(mainIndex=0 ;mainIndex<height && mainIndex<(len-height); mainIndex++){
            //insertion sort start 
            for(listIndex=mainIndex+height ;listIndex<len; listIndex+=height){
                temp=arr[listIndex];
                foundPos=0;
                for(innerIndex=listIndex ;innerIndex>height-1 && !foundPos; innerIndex-=height){
                    if(temp>=arr[innerIndex-height]){
                        arr[innerIndex]=temp;
                        foundPos=1;
                        counterShift++;
                    }
                    else{
                        arr[innerIndex]=arr[innerIndex-height];
                        counterShift++;
                    }            
                    counterInner++;
                }
                if(!foundPos){
                    arr[mainIndex]=temp;
                    counterShift++;
                }
            }

            total+=counterInner;
            counterList[counterMain]=counterInner;
            counterMain++;
            counterInner=0; 
        }
    }

    printCounters(counterMain, total, counterShift, counterList);
}

void printCounters(int main, int total, int shift, int list[]){
    int j;
    
    printf("iterazioni esterne: %5d\t", main);
    printf("iterazioni totali: %5d\t", total);
    printf("scambi: %5d\t", shift);
    printf("iterazioni interne: [ ", total);
    for(j=0;j<main;j++)  
        printf("%d ", list[j]);
    printf("]");
    printf("\n");
}
#include<stdio.h>
void swap(int *arr, int i, int j){
    if(i==j) return;
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void printArr(int *arr, int len){
    printf("\n");
    for(int i = 0; i< len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void selectionSort(int *arr, int len){

    for(int i=0; i<len-1; i++){
        int min_index = i;
        for(int j = i+1; j<len; j++){
            if(arr[j]<arr[min_index]){
                min_index = j;
            }
        }
        swap(arr,i,min_index);
        // printArr(arr,len);
    }
}

void insertionSort(int *arr, int len){
    for(int i = 1;i<len; i++){
        int j=i;
        while(j>=1 && arr[j-1]>arr[j]){
            swap(arr, j, j-1);
            j--;
        }
        // printArr(arr, len);

    }
}

void bubbleSort(int *arr, int len){
    for(int i=0; i<len-1; i++){
        int swapped = 0;
        for(int j = 0; j<len-1-i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr, j, j+1);
                swapped = 1;
            }
        }
        if(!swapped) break;
        // printArr(arr, len);

    }

}

int main(int argc, char* argv[]){
    int arr[10] = {5,3,7,1,8,4,6,0,9,2};
    int len = 10;
    printArr(arr, len);
    
    // selectionSort(arr, len);
    // insertionSort(arr, len);
    // bubbleSort(arr,len);

    printArr(arr, len);
}
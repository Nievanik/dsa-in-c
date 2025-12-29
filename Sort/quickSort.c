#include<stdio.h>

int partition(int *arr, int start, int end){
    int pivot = arr[end];
    int i = start-1;
    int temp;
    
    for(int j = start; j<end ; j++){
        if(arr[j] <= pivot){
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

        }
    }

    i++;
    temp = arr[i];
    arr[i] = arr[end];
    arr[end] = temp;
    return i;

}

void quickSort(int *arr, int start, int end){ //(arr, 0, 7)
    if(end <= start) return;

    int pivotIndex = partition(arr, start, end);

    quickSort(arr, start, pivotIndex-1);
    quickSort(arr, pivotIndex+1, end);




}


int main(){
    int arr[] = {8,2,5,3,9,6,1,7};
    int n = sizeof(arr)/sizeof(arr[0]); // n = 8

    quickSort(arr,0,n-1); 

    printf("Sorted array: ");
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}


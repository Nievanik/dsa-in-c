#include<stdio.h>


void countSort(int *arr, int n, int maxCount){ //(arr, 0, 7)
    int i;
    int count[maxCount+1];
    int firstPosition[maxCount+1];
    int output[n];


    //Count occurance
    for(i = 0; i<=maxCount; i++){
        count[i]=0;
    }
    //Count occurance
    for(i = 0; i<n; i++){
        count[arr[i]]++;
    }

    //find first Position;
    firstPosition[0] = 0;
    for(i = 1; i<=maxCount; i++){
        firstPosition[i] = firstPosition[i-1] + count[i-1];
    }

    //place elements in output array in correct order
    for(i = 0; i<n; i++){
        output[firstPosition[arr[i]]] = arr[i];
        firstPosition[arr[i]]++;
    }

    //copy back to original array
     for(i = 0; i<n; i++){
        arr[i] = output[i];
    }

}


int main(){
    int arr[] = {8,2,5,3,9,6,1,7};
    int n = sizeof(arr)/sizeof(arr[0]); // n = 8
    int maxCount = 9;

    countSort(arr,n,9); 

    printf("Sorted array: ");
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}


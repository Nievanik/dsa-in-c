#include<stdio.h>
#include<stdlib.h>


int binarySearchLast(int *a, int n, int key){
    int low = 0; 
    int high = n-1;
    int mid;

    while(low<=high){
        mid = (low+high)/2;
        
        if(a[mid]<=key){
            low = mid+1;
        }else{
            high = mid-1;
        }
    }
    return high;
}


int main(){

    int n = 5;                                  // number of elements in input array
    int y[] = {0,3,1,2,1,8};                    // input array (0th index is dummy) 


    int *C = malloc((n+1)*sizeof(int));         // array to store the length of LIS ending at each index
    int *j = malloc((n+1)*sizeof(int));         // array to store the previous index in the LIS
    int *bsTabC =   malloc((n+1)*sizeof(int));  // bsTabC[len] = smallest tail of LIS of length len
    int *bsTabI =   malloc((n+1)*sizeof(int));  // bsTabI[len] = index in y[] of LIS that tail
    int i, k, LISlen;

    if(!C || !j || !bsTabC || !bsTabI){
        printf("Memory allocation fail");
        return 1;
    }




    //Initialization
    bsTabC[0] = -99999;
    bsTabI[0] = 0;

    for(i = 1; i<=n; i++){
        bsTabC[i] = 99999;
    };

    C[0] = 0;
    j[0] = 0;

    //Main DP loop

    for(i = 1; i<=n; i++){
        k = binarySearchLast(bsTabC, n+1, y[i]); //end of longest LIS that y[i] can extend;

        //NON decreasing
        // C[i] = k+1;
        // j[i] = bsTabI[k]; 
        // bsTabC[k+1] = y[i];
        // bsTabI[k+1] = i;

        // STRICTLY increasing condition 
        if(bsTabC[k]<y[i]){
            C[i] = k+1;
            j[i] = bsTabI[k]; 
            bsTabC[k+1] = y[i];
            bsTabI[k+1] = i;
        }else{
            C[i] = -1;
            j[i] = -1; 

        }
    }

    // Output table

    printf("  i   y   C   j\n");
    printf("----------------\n");
    for (i = 1; i <= n; i++){
        printf("%3d %3d %3d %3d\n", i, y[i], C[i], j[i]);
    }


    // Find LSI length

    for(LISlen = n; bsTabC[LISlen] == 99999; LISlen--);
    
    printf("\nLength of LIS = %d\n", LISlen);

    //Printing LIS

    printf("LIS (reversed):\n");
    for(i = bsTabI[LISlen]; i>0; i = j[i]){
                printf("%d ", y[i]);
    }

    //cleanup

    free(C);
    free(j);
    free(bsTabC);
    free(bsTabI);


    return 0;
}
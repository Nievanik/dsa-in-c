#include<stdio.h>

int main(){
    int n;          //number of elements
    int m;          //target sum
    scanf("%d",&n);
    scanf("%d",&m);

    int s[n+1];     //array of elements
    int c[n+1];     //array of sum

    s[0]=0;
    c[0]=0;

    for(int i = 1; i<=n; i++){
        scanf("%d", &s[i]);
    }
    
    int potentialSum;
    int i,j;
    int leftover;

    for(potentialSum = 1; potentialSum<=m; potentialSum++){
        for(j=1; j<=n; j++){
            leftover = potentialSum - s[j];
            
            if(leftover>=0 && c[leftover] <j){
                break;
            }
        }

        c[potentialSum] = j; // j<=n -> achiveable
    }


    // Print input set
    printf("\nInput Set:\n");
    printf("  i   S\n");
    printf("-------\n");
    for (i = 0; i <= n; i++){
        printf("%3d %3d\n", i, s[i]);
    }

    // Print DP table
    printf("\nDP Table:\n");
    printf("  i   C\n");
    printf("-------\n");
    for (i = 0; i <= m; i++){
        printf("%3d %3d\n", i, c[i]);
    }
    

    //print Solution
    if(c[m]==n+1){
        printf("\nNo solution exists for sum %d\n", m);
    }else{
        printf("\nSolution (index, value):\n");
        printf("  i   S\n");
        printf("-------\n");
        for(int i = m; i>0; i-= s[c[i]] ){
            printf("%3d %3d\n", c[i], s[c[i]]);
        }
    }

    return 0;
}
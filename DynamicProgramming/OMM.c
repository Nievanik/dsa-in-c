#include<stdio.h>


int p[10];
int n;
int c[10][10];
int trace[10][10];

int main(int argc, char *argv[]){
    int i,j,k, work;
    scanf("%d", &n);

    for(int i = 0; i<=n; i++){
        scanf("%d", &p[i]);
    }

    //Base case
    for(i = 1;i<=n;i++){
        c[i][i] = 0;
        trace[i][i]=0;
    }

    //Dp Table
    for(i=1; i<n;i++){          //chain length
        for(j=1; j<=n-i; j++){   //left index
            c[j][j+i] = 99999; //max value;
            for(k = j; k<j+i; k++){
                work = c[j][k] + c[k+1][j+i] + p[j-1]*p[k]*p[j+i];
                if(c[j][j+i]>work){
                    c[j][j+i] = work;
                    trace[j][j+i] = k;
                }
            }

        } 
    }

    // print DP table
    for(int i = 1; i<=n; i++){
        for(j=1;j<=n;j++){
            if(i>j){
                printf(" ------ ");
            }else{
                printf("(%-2d %2d) ", c[i][j], trace[i][j]);
            }
        }
        printf("\n");
    }

}
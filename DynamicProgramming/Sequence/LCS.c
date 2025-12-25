#include<stdio.h>
#include<string.h>

#define MAXSIZE 50

int len1, len2;
char str1[MAXSIZE], str2[MAXSIZE];
int dp[MAXSIZE+1][MAXSIZE+1];
char LCSstring[MAXSIZE];

int main(){
    int i,j;

    printf("Enter first string: ");
    scanf("%s", str1);
    printf("Enter second string: ");
    scanf("%s", str2);

    len1 = strlen(str1);
    len2 = strlen(str2);


    //settng first row and columnn to 0;
    for(i = 0; i<=len1; i++){
        dp[i][0] = 0;
    }
    for(i = 0; i<=len2; i++){
        dp[0][i] = 0;
    }

    for(i=1; i<=len1; i++){
        for(j=1; j<=len2; j++){
            if(str1[i-1]==str2[j-1]){
                dp[i][j] = dp[i-1][j-1]+1;
            }else{
                dp[i][j] = (dp[i-1][j]>dp[i][j-1]) ? dp[i-1][j]: dp[i][j-1];
            }
        }
    }


    //backtrace
    int index = dp[len1][len2];
    LCSstring[index] = '\0';

    i = len1;
    j = len2;

    while(i>0 && j>0){
        if(str1[i-1] == str2[j-1]){
            LCSstring[index-1] = str1[i-1];
            index--;
            i--;
            j--;
        } else if(dp[i-1][j] > dp[i][j-1]){
            i--;
        } else{
            j--;
        }
    }
    printf("Longest Common Subsequence: %s\n", LCSstring);
    printf("Length of LCS: %d\n\n", dp[len1][len2]);

    printf("\n DP table...\n");

    printf("      ");
    for(int i = 0; i<len2; i++){
        printf("%2c ", str2[i]);
    }
    printf("\n");
    
    printf("   ");
    for(int i = 0; i<=len2; i++){
        printf("%2d ", dp[0][i]);
    }
    printf("\n");
    for(int i = 1; i<=len1; i++){
        printf("%2c ", str1[i-1]);
        for(int j = 0; j<=len2; j++){
            printf("%2d ",dp[i][j]);
        }
        printf("\n");
    }


    return 0;

}

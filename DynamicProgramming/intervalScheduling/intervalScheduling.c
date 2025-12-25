#include<stdio.h>


#define TABSIZE (100)

int n;
int s[TABSIZE], f[TABSIZE], v[TABSIZE];
int p[TABSIZE], M[TABSIZE];

int max(int x,int y)
{
  if (x>y) return x;
  return y;
}

int binSearchLast(int *a, int n, int key)
{
    int low = 0, high = n - 1, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (a[mid] <= key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return high;
}
int main(int argc, char* argv[]){

        int i;
    int sum = 0;

    // Read number of intervals
    scanf("%d", &n);

    // Sentinel value for binary search
    f[0] = -999999;

    // Read intervals: start, finish, value
    for (i = 1; i <= n; i++)
        scanf("%d %d %d", &s[i], &f[i], &v[i]);

    // // Check if intervals are sorted by finish time
    // for (i = 2; i <= n && f[i - 1] <= f[i]; i++)
    //     ;

    // if (i <= n)
    // {
    //     printf("Intervals not ordered by finish time\n");
    //     exit(0);
    // }


    for(int i = 1; i<=n; i++){
        p[i] = binSearchLast(f, n+1, s[i]);
    }


    M[0] = 0;
    for(int i = 1; i<=n; i++){
        M[i] = max(M[i-1], v[i] + M[p[i]]);
    }

    // Print DP table
    printf("  i   s   f   v   p   M\n");
    for (i = 1; i <= n; i++)
        printf("%3d %3d %3d %3d %3d %3d\n",
               i, s[i], f[i], v[i], p[i], M[i]);


    //Backtracing
    i = n;
    while(i>0){
        if(v[i] + M[p[i]] >= M[i-1]){
            printf("Include interval %d\n", i);
            sum += v[i];
            i = p[i];
        }else{
            i--;
        }
    }

    // Print maximum value
    printf("sum is %d\n", sum);

    return 0;
}
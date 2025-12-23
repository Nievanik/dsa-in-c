#include<stdio.h>

int ud[7] = {0, 9, 9, 3, 4, 8, 7};   // Upper → Upper
int ld[7] = {0, 12, 5, 6, 4, 5, 9};  // Lower → Lower
int ul[7] = {0, 2, 3, 1, 3, 4, 999}; // Upper → Lower
int lu[7] = {0, 2, 1, 2, 2, 1, 999}; // Lower → Upper

int u[7], l[7];         // DP arrays
char uTrace[7], lTrace[7];



void printDP(){
    printf("Stage:  ");
    for (int i = 0; i <= 6; i++) printf("%3d  ", i);
    printf("\nU[i]:   ");
    for (int i = 0; i <= 6; i++) printf("%3d(%c) ", u[i], uTrace[i]);
    printf("\nL[i]:   ");
    for (int i = 0; i <= 6; i++) printf("%3d(%c) ", l[i], lTrace[i]);
    printf("\n");
}

void explicitTraceBack(){
    int i = 6;
    char uORL = (u[6]<l[6])? 'u' : 'l';

    while(i>0){
        if(uORL == 'u'){
            printf("u[%d] = %d\n", i, u[i]);
            if(uTrace[i]=='s'){
                uORL = 'l';
            }else{
                i--;
            }
        }else{
            printf("l[%d] = %d\n", i, l[i]);
            if(lTrace[i]=='s'){
                uORL = 'u';
            }else{
                i--;
            }
        }
    }
}

void implicitTraceBack(){
    int i = 6;
    char uORL = (u[6]<l[6])? 'u' : 'l';

    while(i>0){
        if(uORL == 'u'){
            printf("u[%d] = %d\n", i, u[i]);
            if(u[i] == u[i-1]+ ud[i]){
                i--;
            }else{
                uORL = 'l';
            }
        }else{
            printf("l[%d] = %d\n", i, l[i]);
            if(l[i] == l[i-1]+ ld[i]){
                i--;
            }else{
                uORL = 'u';
            }
        }
    }
}


int main(int argc, char* argv[]){
    u[0] = 0;
    l[0] = 0;
    uTrace[0] = 'x';
    lTrace[0] = 'x';
   


    for(int i = 1; i<=6; i++){
        if(u[i-1]+ud[i] < l[i-1]+ld[i]+lu[i]){
            u[i] = u[i-1]+ud[i];
            uTrace[i] = 'c';
        }else{
            u[i] = l[i-1]+ld[i]+lu[i];
            uTrace[i] = 's';
        }

        if(l[i-1]+ld[i] < u[i-1]+ud[i]+ul[i]){
            l[i] = l[i-1]+ld[i];
            lTrace[i] = 'c';
        }else{
            l[i] = u[i-1]+ud[i]+ul[i];
            lTrace[i] = 's';
        }
    }

    // printDP();

    // explicitTraceBack();
    implicitTraceBack();

    return 0;
}
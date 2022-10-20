#include <stdio.h>
#include <stdlib.h>

int main(){
    int p[] = {7,12,10,8,9,4,3,6,11,1,2,5};

    int k = 60;

    int pprev[12];

    for(int j = 0; j < 12; j ++)
        pprev[j] = p[j];


    for(int i = 0; i < 60; i++){
        int ptemp[12];
        for(int j = 0; j < 12; j++)
            ptemp[j] = pprev[p[j] - 1];

        printf("\n\n%d:\n", i+2);
        for(int j = 0; j < 12; j++){
            printf("%d ", j+1);
        }
        printf("\n");
        for(int j = 0; j < 12; j++){
            printf("%d ", ptemp[j]);
        }
        

        
        for(int j = 0; j < 12; j ++)
            pprev[j] = ptemp[j];

    }

    
}
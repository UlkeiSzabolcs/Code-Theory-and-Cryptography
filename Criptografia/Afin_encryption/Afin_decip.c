#include <stdio.h>
#include <stdlib.h>

int mi(int ci){
    int citemp = (ci - 5 >= 0) ? (ci - 5) : (27 + ci - 5);
    return (16 * (citemp - 5)) % 27;
}

int main(){
    FILE* f;
    char ci;

    f = fopen("Afin_Cypher.txt", "r");

    do{
        ci = fgetc(f);
        printf("%c", 'A' + mi(ci - 'A'));
    }
    while(ci != EOF);


}
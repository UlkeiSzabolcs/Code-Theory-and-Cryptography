#include <stdio.h>
#include <stdlib.h>

int** mul_matrix(int** mat_A, int n_A, int m_A,  int** mat_B, int n_B, int m_B){
    int n_res = n_A;
    int m_res = m_B;

    int** mat_res;
    mat_res = (int**)malloc(n_res * sizeof(int*));
    for(int i = 0; i < n_res; i++){
        mat_res[i] = (int*)calloc(m_res, sizeof(int));
    }

    for(int i_A = 0; i_A < n_A; i_A++){
        for(int j_B = 0; j_B < m_B; j_B++){
            for(int j_A = 0; j_A < m_A; j_A++){
                    //printf("\n\n%d   *   %d\n\n",mat_A[i_A][j_A], mat_B[j_B][j_A]);
                    mat_res[i_A][j_B] += mat_A[i_A][j_A] * mat_B[j_A][j_B] ;
            }
        }
    }
    return mat_res;
}

int main(){
    int a[4][4] = {
        {6, 20, 25, 6},
        {5, 4, 17, 9},
        {23, 3, 18, 1},
        {13, 7, 21, 0}
        };

    int** a_mat;
    int** b_mat;
    a_mat = (int**)malloc(4 * sizeof(int*));
    b_mat = (int**)malloc(4 * sizeof(int*));

    for(int i = 0; i < 4; i++){
        a_mat[i] = (int*)malloc(4 * sizeof(int));
        b_mat[i] = (int*)malloc(sizeof(int));
        for(int j = 0; j < 4; j++)
            a_mat[i][j] = a[i][j];
    }

    FILE* f;
    char ch;

    f = fopen("Hill_Cypher.txt", "r");
    do{
        for(int i = 0; i < 4; i++){
            ch = fgetc(f);
            b_mat[i][0] = ch - 'A';
        }
        for(int i = 0; i < 4; i++){
            ch = fgetc(f);
        }

        int** res;
        res = mul_matrix(a_mat, 4, 4, b_mat, 4, 1);

        for(int i = 0; i < 4; i++)
            printf("%c", ((res[i][0]) % 26) + 'A');

    }
    while (ch != EOF);
}
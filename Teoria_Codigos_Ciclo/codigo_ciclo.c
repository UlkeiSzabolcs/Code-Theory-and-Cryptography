#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct 
{
    int grado;
    int* polinom;
}generador_codigo;

typedef struct 
{
    int n, k, nr_palabras;
    generador_codigo generador;
    int* cociente_de_dividir;
    int** palabras;
    int** matriz_generador;
    int** matriz_comprobacion_paridad;
}cod_ciclic;


generador_codigo inicio_generador(int n, int k, int* polinom){
    generador_codigo generador;
    generador.grado = n - k;
    generador.polinom = (int*)calloc(generador.grado + 1, sizeof(int));

    for(int i = 0; i <= generador.grado; i++){
        generador.polinom[i] = polinom[i];
    }
    
    return generador;
}

int** inicio_generador_matriz(cod_ciclic cod){
    int** generador_matriz;
    generador_matriz = (int**)malloc(cod.k * sizeof(int*));
    for(int i = 0; i < cod.k; i++){
        generador_matriz[i] = (int*)malloc(cod.n * sizeof(int));
        for(int j = 0; j < cod.n; j++){
            if(i == 0){
                if(j < cod.generador.grado)
                    generador_matriz[i][j] = cod.generador.polinom[j];
                else
                    generador_matriz[i][j] = 0;
            }
            else{
                if(j == 0)
                    generador_matriz[i][j] = 0;
                else
                    generador_matriz[i][j] = generador_matriz[i - 1][j - 1];
            }
        }
    }
    return generador_matriz;
}

int** inicio_comp_par_matriz(cod_ciclic cod){
    int** matriz_comprobacion_paridad;
    matriz_comprobacion_paridad = (int**)malloc(cod.generador.grado * sizeof(int*));
    for(int i = 0; i < cod.generador.grado; i++){
        matriz_comprobacion_paridad[i] = (int*)malloc(cod.n * sizeof(int));
        for(int j = 0; j < cod.n; j++){
            if(i == 0){
                if(j < cod.generador.grado)
                    matriz_comprobacion_paridad[i][j] = cod.cociente_de_dividir[j];
                else
                    matriz_comprobacion_paridad[i][j] = 0;
            }
            else{
                if(j == 0)
                    matriz_comprobacion_paridad[i][j] = 0;
                else
                    matriz_comprobacion_paridad[i][j] = matriz_comprobacion_paridad[i - 1][j - 1];
            }
        }
    }
    return matriz_comprobacion_paridad;
}

int** generador_polinomios(int k){
    int** polinomios;
    int nr_polinomios = 1;

    for(int i = 0; i < k; i++)
        nr_polinomios *= 2;

    polinomios = (int**)malloc(nr_polinomios * sizeof(int));
    
    polinomios[0] = (int*)calloc(k, sizeof(int));
    for(int i = 1; i < nr_polinomios; i++){
        polinomios[i] = (int*)malloc(k * sizeof(int));
        int carry = 1;
        for(int j = 0; j < k; j++){
            if(
                (polinomios[i - 1][j] == 1 && carry == 0) ||
                (polinomios[i - 1][j] == 0 && carry == 1)
            ){
                polinomios[i][j] = 1;
                carry = 0;
            }
            else if(
                polinomios[i - 1][j] == 0 && carry == 0
            ){
                polinomios[i][j] = 0;
                carry = 0;
            }
            else{
                polinomios[i][j] = 0;
                carry = 1;
            }
        }
    }

    return polinomios;
}


int* multiplicador_polinomios(int* pol1, int grad1, int* pol2, int grad2){
    int* res;
    int grad_res = grad1 + grad2;
    res = (int*)calloc(grad_res, sizeof(int));

    for(int i = 0; i < grad1; i++){
        for(int j = 0; j <= grad2; j++){
            res[i + j] = (pol1[i] * pol2[j] == res[i + j]) ? 0 : 1;
        }
    }

    return res;
}

int** generador_palabras(generador_codigo generador, int k){
    int** polinomios = generador_polinomios(k);
    int nr_polinomios = 1;

    for(int i = 0; i < k; i++)
        nr_polinomios *= 2;

    int** palabras = (int**)malloc(nr_polinomios * sizeof(int*));

    for(int i = 0; i < nr_polinomios; i++){
        int* res = multiplicador_polinomios(polinomios[i], k, generador.polinom, generador.grado);

        for(int j = 0; j <= k-1; j++){
            printf("%d", polinomios[i][j]);
        }
        printf("  *  ");
        for(int j = 0; j <= generador.grado; j++){
            printf("%d", generador.polinom[j]);
        }
        printf("  --->>  ");
        for(int j = 0; j < generador.grado + k; j++){
            printf("%d ", res[j]);
        }
        printf("\n");
        palabras[i] = res;
    }
    return palabras;
}

cod_ciclic inicio_cod(int n, int k, int* polinom, int* hx){
    cod_ciclic cod;
    int nr_palabras = 1;

    for(int i = 0; i < k; i++)
        nr_palabras *= 2;

    cod.n = n;
    cod.k = k;
    cod.nr_palabras = nr_palabras;
    cod.cociente_de_dividir = hx;


    cod.generador = inicio_generador(n, k, polinom);

    cod.matriz_generador = inicio_generador_matriz(cod);

    cod.matriz_comprobacion_paridad = inicio_comp_par_matriz(cod);

    cod.palabras = generador_palabras(cod.generador, k);


    
    return cod;
}

int main(){
    FILE *f;
    f = fopen("codigo_ciclo_resueltas.txt", "w");


    int n = 15, k = 7;
    int polinom[] = {1, 0, 0, 0, 1, 0, 1, 1, 1};
    /*int n = 6, k = 4;
    int polinom[] = {1, 1, 1};*/

    //h(x) = x^7 + x^6 + x^4 + 1
    int* hx;
    hx = (int*)calloc(7, sizeof(int));
    hx[0] = hx[3] = hx[5] = hx[6] = 1;
    cod_ciclic cod;
    cod = inicio_cod(n, k, polinom, hx);

    printf("\n\n\nn: %d\nk: %d\ngenerador grado: %d\nnr palabras: %d\n\nParablas:{", n, k, cod.generador.grado, cod.nr_palabras);
    fprintf(f, "\n\n\nn: %d\nk: %d\ngenerador grado: %d\nnr palabras: %d\n\nParablas:{", n, k, cod.generador.grado, cod.nr_palabras);

    for(int i = 0; i < cod.nr_palabras; i++){
        for(int j = 0; j < n; j++){
            printf("%d", cod.palabras[i][j]);
            fprintf(f, "%d", cod.palabras[i][j]);
        }
        if(i != cod.nr_palabras - 1){
            printf(", ");
            fprintf(f, ", ");
        }
        else{
            printf("}\n\n");
            fprintf(f, "}\n\n");
        }
    }

    printf("Matriz Generador Codigo:\n");
    fprintf(f, "Matriz Generador Codigo:\n");
    for(int i = 0; i < cod.k; i++){
        for(int j = 0; j < cod.n; j++){
            printf("%d ", cod.matriz_generador[i][j]);
            fprintf(f, "%d ", cod.matriz_generador[i][j]);
        }
        printf("\n");
        fprintf(f, "\n");
    }

    printf("\nMatriz Comprobacion Paridad:\n");
    fprintf(f, "\nMatriz Comprobacion Paridad:\n");
    for(int i = 0; i < cod.generador.grado; i++){
        for(int j = 0; j < cod.n; j++){
            printf("%d ", cod.matriz_comprobacion_paridad[i][j]);
            fprintf(f, "%d ", cod.matriz_comprobacion_paridad[i][j]);
        }
        printf("\n");
        fprintf(f, "\n");
    }
    fclose(f);
}
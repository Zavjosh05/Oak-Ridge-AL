#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float **mtx;
    int m;
    int n;
} Matriz;

void initMatrix(Matriz *);
void consMtx(Matriz *, int, int);
void destMtx(Matriz *);
void fill(Matriz);
void imp(Matriz);
void fillZero(Matriz);
void fillRand(Matriz);
void mtxIn(Matriz, Matriz *);
int mtxInv(Matriz, Matriz *);
void swap(Matriz, int, int);
void mult(Matriz, Matriz, Matriz);
void comp(Matriz, Matriz);
void copy(Matriz, Matriz *);

int main(int argv, char **argc){
    int m= 3, n=3, ret;
    Matriz a, b;
    consMtx(&a, m, n);

    ret = mtxInv(a, &b);
    if(ret == 1){
        imp(b);
        puts("===========================");
        comp(a, b);
    }else if(ret == 0){
        printf("La matriz es no inversible. \n");
    }

    destMtx(&a);
    return 0;
}

//construcción de Matriz
void consMtx(Matriz *a, int m, int n){
    a->m = m;
    (*a).n = n;
    char c;
    initMatrix(a);
    puts("Matriz construida");
    puts("Deseas Llenar la matriz manualmente o generar sus datos aleatoreamente?");
    puts("1. Llenar manualmente");
    puts("2. Generar datos");
    while(0==0){
        scanf("%s", &c);
        if(c=='1'){
            printf("Llena la matriz %d x %d: \n", m, n);
            fill(*a);
            break;
        }else if(c=='2'){
            fillRand(*a);
            break;
        }
        else
            puts("opción no válida");
    }
    puts("==========");
    imp(*a);
    puts("==========");
}

//inicializacion de matriz
void initMatrix(Matriz *x){
    x->mtx = malloc(x->m * sizeof(float *));
    for(int i=0; i < x->m; i++)
        x->mtx[i] = malloc(x->n * sizeof(float));
}

//liberacion de matriz
void destMtx(Matriz *a){
    int i;
    for(i = 0; i<(*a).m; i++)
        free((*a).mtx[i]);
    free((*a).mtx);
    (*a).mtx = NULL;
}

//impresion de matriz
void imp(Matriz a){
    int i, j;
    for(i=0; i<a.m; i++){
        printf("| ");
        for(j=0; j<a.n; j++){
            printf("%.2f ", a.mtx[i][j]);
        }
        printf(" | \n");
    }
}

//llenado de matriz
void fill(Matriz a){
    int i, j;
    for(i=0; i<a.m; i++){
        for(j=0; j<a.n; j++){
            scanf("%f", &a.mtx[i][j]);
        }
    }
}

//inicializacion con 0 de matriz
void fillZero(Matriz a){
    int i, j;
    for(i=0; i<a.m; i++){
        for(j=0; j<a.n; j++){
            a.mtx[i][j] = 0;
        }
    }
}

void fillRand(Matriz a){
    int i, j, ranInt;
    for(i=0; i<a.m; i++)
        for(j=0; j<a.n; j++){
            ranInt = rand()%2;
            if (ranInt == 0)
                a.mtx[i][j] = rand()*(-10);
            else
                a.mtx[i][j] = rand()*50;
        }
}

//Construccion de matriz identidad
void mtxIn(Matriz a, Matriz *b){
    if(a.m == a.n){
        b->m = a.m;
        b->n = a.m;
        initMatrix(b);
        int i, j;
        for(i = 0; i < b->m; i++){
            for(j=0; j < b->n; j++){
                if(i == j){
                    b->mtx[i][j] = 1;
                }else{
                    b->mtx[i][j] = 0;
                }
            }
        }
    }else{
        printf("(!) Esta funcion requiere una matriz cuadrada \n");
    }
}

void swap(Matriz a, int i, int j){
    float *aux = a.mtx[i];
    a.mtx[i] = a.mtx[j];
    a.mtx[j] = aux;
}

void mult(Matriz a, Matriz b, Matriz c){
    if(a.n == b.m){
        int i, j, k;
        fillZero(c);
        if(c.m != a.m || c.n != b.m){
            c.m = a.m;
            c.n = b.n;
        }
        for(i=0; i<b.n; i++){
            for(j=0; j<a.m; j++){
                for(k=0; k<a.n; k++){
                    c.mtx[j][i] += (a.mtx[j][k])*(b.mtx[k][i]);
                }
            }
        }
    }else{
        printf("(!) El numero de columnas de la primera matriz debe de ser igual al numero de filas de la segunda matriz.");
    }
}

void comp(Matriz a, Matriz b){
    Matriz c;
    c.m = a.m;
    c.n = a.n;
    initMatrix(&c);
    mult(a, b, c);
    printf("A(A^-1) = \n");
    imp(c);
    puts("***************************");
    mult(b, a, c);
    printf("(A^-1)A = \n");
    imp(c);
}

void copy(Matriz orgnal, Matriz *cpy){
    if(orgnal.m == cpy->m && orgnal.n == cpy->n){
        int i, j;
        for(i = 0; i < orgnal.m; i++){
            for(j = 0; j < orgnal.n; j++){
                cpy->mtx[i][j] = orgnal.mtx[i][j];
            }
        }

    }else{
        printf("La matriz destino tiene que ser del mismo tamaño. \n");
    }
}

int mtxInv(Matriz aOr, Matriz *aInv){
    if(aOr.m == aOr.n){
        int i, j, k, flg = 0, simp = 0;
        float x, y;
        Matriz a; a.m = aOr.m; a.n = aOr.n;
        initMatrix(&a);
        copy(aOr, &a);
        mtxIn(a, aInv);

        if(a.mtx[0][0] == 0){
            for(i=1; i<a.m; i++){
                if(a.mtx[i][0] != 0){
                    swap(a, 0, i);
                    swap(*aInv, 0, i);
                    break;
                }
            }
            if(i == a.m){
                return 0;
            }
        }

        for(i=0; i<a.m; i++){
            x = a.mtx[i][i];
            for(j=0; j<a.m; j++){
                y = a.mtx[j][i];
                if(i!=j){
                    for(k=0; k<a.m; k++){
                        if(!simp && x != 1){
                            a.mtx[i][k] = a.mtx[i][k]/x;
                            aInv->mtx[i][k] = aInv->mtx[i][k]/x;
                            if(k == a.m-1){
                                simp = 1;
                            }
                        }

                        a.mtx[j][k] = a.mtx[j][k] - y*a.mtx[i][k];
                        aInv->mtx[j][k] = aInv->mtx[j][k] - y*aInv->mtx[i][k];

                        if(a.mtx[j][k] != 0){
                                flg = 1;
                        }
                    }
                }else{
                    flg = 1;
                }

                if(!flg){
                    return 0;
                }else{
                    flg = 0;
                }
            }
            simp = 0;
        }

        destMtx(&a);
        return 1;
    }else{
        printf("(!) Esta funcion requiere de una matriz de orden n. \n");
        return -1;
    }
}

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
void mtxIn(Matriz, Matriz *);
void mtxAum(Matriz, Matriz, Matriz *);
int mtxInv(Matriz, Matriz *);
void swap(Matriz, int, int);
void mult(Matriz, Matriz, Matriz);
void comp(Matriz, Matriz);

int main(int argv, char **argc){
    int m= 2, n=2, ret;
    Matriz a, b;
    consMtx(&a, m, n);

    ret = mtxInv(a, &b);
    if(ret == 1){
        imp(b);
        puts("=====================");
        comp(a, b);
    }else if(ret == 0){
        printf("La matriz es no inversible. \n");
    }

    destMtx(&a);
    return 0;
}

void consMtx(Matriz *a, int m, int n){
    a->m = m;
    (*a).n = n;
    initMatrix(a);
    puts("Matriz construida");
    printf("Llena la matriz %d x %d: \n", m, n);
    fill(*a);
    puts("==========");
    imp(*a);
    puts("==========");

}

void initMatrix(Matriz *x){
    x->mtx = malloc(x->m * sizeof(float *));
    for(int i=0; i < x->m; i++)
        x->mtx[i] = malloc(x->n * sizeof(float));
}

void destMtx(Matriz *a){
    int i;
    for(i = 0; i<(*a).m; i++)
        free((*a).mtx[i]);
    free((*a).mtx);
    (*a).mtx = NULL;
}

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

void fill(Matriz a){
    int i, j;
    for(i=0; i<a.m; i++){
        for(j=0; j<a.n; j++){
            scanf("%f", &a.mtx[i][j]);
        }
    }
}

void fillZero(Matriz a){
    int i, j;
    for(i=0; i<a.m; i++){
        for(j=0; j<a.n; j++){
            a.mtx[i][j] = 0;
        }
    }
}

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

void mtxAum(Matriz a, Matriz b, Matriz *aum){
    if(a.m == b.m){
        int i, j, p= a.n+b.n;
        aum->m = a.m;
        aum->n = p;
        initMatrix(aum);
        for(i=0; i<aum->m; i++){
            for(j=0; j<a.n; j++){
                aum->mtx[i][j] = a.mtx[i][j];
                if(j < b.n){

                    aum->mtx[i][a.n+j] = b.mtx[i][j];
                }
            }
        }
    }else{
        printf("Las matrices deben tener el mismo numero de filas. \n");
    }
}

void ladoDer(Matriz aum, Matriz b){
    int i, j, k;
    for(i = 0; i < aum.m; i++){
        for(j = aum.m, k=0; j < aum.n; j++, k++){
            b.mtx[i][k] = aum.mtx[i][j];
        }
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
    mult(a, b, c);
    printf("(A^-1)A = \n");
    imp(c);
}

int mtxInv(Matriz a, Matriz *aInv){
    if(a.m == a.n){
        Matriz aum;
        int i, j, k, flg = 0, simp = 0;
        float x, y;
        mtxIn(a, aInv);
        mtxAum(a, *aInv, &aum);

        if(aum.mtx[0][0] == 0){
            for(i=1; i<aum.m; i++){
                if(aum.mtx[i][0] != 0){
                    swap(aum, 0, i);
                    break;
                }
            }
            if(i == aum.m){
                return 0;
            }
        }

        for(i=0; i<aum.m; i++){
            x = aum.mtx[i][i];
            for(j=0; j<aum.m; j++){
                y = aum.mtx[j][i];
                if(i!=j){
                    for(k=0; k<aum.m; k++){
                        if(!simp && x != 1){
                            aum.mtx[i][k] = aum.mtx[i][k]/x;
                            aum.mtx[i][aum.m+k] = aum.mtx[i][aum.m+k]/x;
                            if(k == aum.m-1){
                                simp = 1;
                            }
                        }

                        aum.mtx[j][k] = aum.mtx[j][k] - y*aum.mtx[i][k];
                        aum.mtx[j][aum.m+k] = aum.mtx[j][aum.m+k] - y*aum.mtx[i][aum.m+k];

                        if(aum.mtx[j][k] != 0){
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

        ladoDer(aum, *aInv);
        destMtx(&aum);
        return 1;
    }else{
        printf("(!) Esta funcion requiere de una matriz de orden n. \n");
        return -1;
    }
}

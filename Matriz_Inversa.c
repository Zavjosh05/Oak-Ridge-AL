#include <stdio.h>
#include <stdlib.h>
//#include <ctype.h>
#include <string.h>

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
void OrMtx(int*, int*);
int isdigitJ(char);
int verDim(char*,char*);
int verInt(char*);
int StrToInt(char*);
int ChrToInt(char);
int powJ(int,int);
int verFltJ(char*);
int verSign(char*);
int isFloat(char*);
int CountDot(char*);
int checkFloat(char);
float StrToFlt(char*);
float ChrToFlt(char);
void NotNegZero(Matriz*);


int main(int argc, char **argv){
    int m, n, ret;
    Matriz a, b;
    OrMtx(&m,&n);
    printf("m = %d, n = %d\n",m,n);
    consMtx(&a, m, n);

    ret = mtxInv(a, &b);
    NotNegZero(&b);
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
    char c;
    int d = 1;

    a->m = m;
    (*a).n = n;
    
    initMatrix(a);
    puts("Menu :v");
    puts("Deseas Llenar la matriz manualmente o generar sus datos aleatoreamente?");
    puts("1. Llenar manualmente");
    puts("2. Generar datos");
    while(d==1){
        scanf("%s", &c);
        switch(c){
            case '1':
                printf("Llena la matriz %d x %d: \n", m, n);
                fill(*a);
                d = 0;
                break;
            case '2':
                fillRand(*a);
                d = 0;
                break;
            default:
                puts("Opción no existente\n");
                d = 1;
                fflush(stdin);
                break;
                //consMtx(a,m,n);
        }
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
    char x[100];
    for(i=0; i<a.m; i++){
        for(j=0; j<a.n; j++){
            printf("[A]%dx%d = ",i+1,j+1);
            scanf("%s", x);
            //
            if(verFltJ(x))
            {
                a.mtx[i][j] = StrToFlt(x);
                printf("[a]%dx%d = %.2f\n\n",i+1,j+1,a.mtx[i][j]);
            }
            else
            {
                puts("(!) Ingrese un flotante valido (!)");
                j--;
            }
        }
    }
}

//inicializacion de matriz con 0
void fillZero(Matriz a){
    int i, j;
    for(i=0; i<a.m; i++){
        for(j=0; j<a.n; j++){
            a.mtx[i][j] = 0;
        }
    }
}

//Llenado aleatorio de matriz
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

//intercambio de filas
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

//Asignación del orden de la matriz
void OrMtx(int *m, int *n)
{
    char ms[5], ns[5];

    puts("Ingrese las dimensiones de la matriz\n");
    printf("m = ");
    scanf("%s", ms);
    putchar('\n');
    printf("n = ");
    scanf("%s", ns);
    putchar('\n');

    if(verDim(ms,ns))
    {
        *m = StrToInt(ms);
        *n = StrToInt(ns);

        if(*m == *n)
            printf("Orden de la matriz: %d\n",*m);
        else
            {
                puts("\n(!) La matriz debe de ser cuadrada (!)");
                OrMtx(m,n);
            }
        
    }else
        {
            puts("\n(!) Inserte enteros positivos validos (!)\n");
            OrMtx(m,n);
        }
}

//funcion que verifica si los numeros si son numeros :v
int verDim(char *m, char *n)
{
    if(verInt(m)&&verInt(n))
        return 1;
    else
        return 0;
}

int isdigitJ(char x)
{
    if(x >= '0'  && x <= '9')
        return 1;
    else
        return 0;
}

//predicado para verificar si la cadena de caracteres solo contiene nums :v
int verInt(char *x)
{
    int i;

    for(i = 0; i < strlen(x); i++)
        if(!isdigitJ(*(x+i)))
            return 0;
    
    return 1;
}

int ChrToInt(char c){return c - '0';}

int powJ(int b, int e)
{
    int n;

    if(e == 0)
        return 1;

    for(n = 1; e > 0; e--)
        n  *= b;

    return n;
}

int StrToInt(char *ch)
{
    int i,j, res = 0;

    for(i = strlen(ch)-1, j = 0; i >= 0; i--,j++)
        res += ChrToInt(*(ch+j))*powJ(10,i);

    return res;
}

int verFltJ(char *fl)
{
    int ver = verSign(fl);

    if(ver)
        if(ver == 1)
        {
            if(isFloat(fl+1))
                return 1;
            else return 0;
        }
        else
        {
            if(isFloat(fl))
                return 1;
            else return 0;
        }

    else return 0;

}

int verSign(char *fl)
{
    if(*fl == '-')
        return 1;
    else if(*fl == '.' || isdigitJ(*fl))
            return 2;
        else return 0;
}

int isFloat(char *x)
{
    int i;

    if(strlen(x)==1 && *x == '.')
        return 0;
    else
    {
        if(CountDot(x) == 0 || CountDot(x) == 1)
        {
        for(i = 0; i < strlen(x); i++)
        {
            if(!checkFloat(*(x + i)))
                return 0;
        }
        return 1;
        }
        else 
            return 0;
    }
    
}

int CountDot(char *x)
{
    int count = 0,i;

    for(i = 0; i < strlen(x); i ++)
    {
        if(*(x + i) == '.')
            count++;
    }

    return count;
}

int checkFloat(char x)
{
    if(isdigitJ(x) || x == '.')
        return 1;
    else
        return 0;
}

float powJFlt(float b, int e)
{
    int i;
    float res = 1;
    
    if(e >= 0)
    {
        for(i = 1; i <= e; i++)
            res *= b;
        return res;
    }
    else
    {
        e *= -1;
        for(i = 0; i < e; i++)
            res *= b;
        return 1/res;
    }
}

int DotLoc(char *x)
{
    int i, count = 0;

    for(i = 0; i < strlen(x); i++)
    {
        if(*(x + i) == '.')
            return count;
        else count++;
    }

    return -1;
}

float StrToFlt(char *x)
{
    int i,j, dotcount;
    float res = 0;

    dotcount = DotLoc(x);

    if(dotcount == -1)
    {
        if(*x == '-')
        {
            x += 1;

            for(i = strlen(x)-1, j = 0; i >= 0; i--,j++)
                res += ChrToFlt(*(x+j))*powJFlt(10,i);
            res = -res;
        }
        else
        {
            for(i = strlen(x)-1, j = 0; i >= 0; i--,j++)
                res += ChrToFlt(*(x+j))*powJFlt(10,i);
        }
    }
    else if(dotcount == 0)
        {
            x += 1;

            for(i = -strlen(x), j = 0; i <= 0; i++, j++)
            res += ChrToFlt(*(x+j))*powJFlt(10,i);
        }
        else if(dotcount == 1)
            {
                if(*x == '-')
                {
                    for(i = -1, j=2; j < strlen(x); i--,j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                    res = -res;
                }
                else
                {
                    for(i = dotcount-1, j = 0; i >= 0; i--, j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                    for(i = -1, j=dotcount+1; j < strlen(x); i--,j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                }
            }
            else
            {
                if(*x == '-')
                {
                    x += 1;

                    for(i = dotcount, j = 0; i >= 0; i--, j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                    for(i = -1, j=dotcount; j < strlen(x); i--,j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);

                    res = -res;
                }
                else
                {
                    for(i = dotcount-1, j = 0; i >= 0; i--, j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                    for(i = -1, j=dotcount+1; j < strlen(x); i--,j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                }
                
            }

    return res;
}

float ChrToFlt(char x)
{
    if(x >= '0' && x<= '9')
        return x - 48;
}

void NotNegZero(Matriz *x)
{
    int i,j;

    for(i = 0; i < x->m; i++)
        for(j = 0; j < x->n; j++)
            if(x->mtx[i][j] == -0)
                x->mtx[i][j] *= -0;
}
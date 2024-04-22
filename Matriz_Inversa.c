#include <stdio.h>
#include <stdlib.h>
//#include <ctype.h>
#include <string.h>

//Definición de la estructura Matriz
typedef struct{
    float **mtx; //Puntero a un array 2D para almacenar los elementos de la matriz
    int m; //Número de filas de la matriz
    int n; //Número de columnas de la matriz
} Matriz;
//Prototipos de las funciones
void initMatrix(Matriz *); //Se inicializa la matriz
void consMtx(Matriz *, int, int); //Construye la matriz
void destMtx(Matriz *); //Destruye la matriz
void fill(Matriz); //Llena la matriz con valores ingresados por el usuario
void imp(Matriz); //Imprime/despliega la matriz
void fillZero(Matriz); //Llena la matriz de ceros
void fillRand(Matriz); //Llena la matriz con datos aleatorios
void mtxIn(Matriz, Matriz *); //Crea la matiz identidad
int mtxInv(Matriz, Matriz *); //Calcula la inversa de la matriz
void swap(Matriz, int, int); //Intercambia dos filas de la matriz
void mult(Matriz, Matriz, Matriz); //Multiplica dos matrices
void comp(Matriz, Matriz); //Compara dos matrices
void copy(Matriz, Matriz *); //Copia una matriz a otra 
void OrMtx(int*, int*); //Asigna el orden de la matriz
int isdigitJ(char); //Verifica si un carácter es un dígito
int verDim(char*,char*); //Verifica las dimensiones de la matriz
int verInt(char*); //Verifica si una cadena de caracteres es un número entero
int StrToInt(char*); //Convierte una cadena de caracteres a un número entero
int ChrToInt(char); //Convierte un carácter a un número entero 
int powJ(int,int); //Calcula la potencia de número
int verFltJ(char*); //Verifica si una cadena de caractres es un número flotante
int verSign(char*); //Verifica el signo de un número
int isFloat(char*); //Verifica si una cadena de caracteres es un número flotante
int CountDot(char*); //Cuenta el número de puntos en una cadena de caracteres
int checkFloat(char); //Verifica si un carácter es un número flotante
float StrToFlt(char*); //Convierte una cadena de caracteres a un número flotante
float ChrToFlt(char); //Convierte un carácter a un número flotante
void NotNegZero(Matriz*); //Cambia los -0 en la matriz a 0
void Menu(Matriz*,int,int); //Muestra un menú para llenar la matriz

//Función principal
int main(int argc, char **argv){
    int m, n, ret; //Se declaran las variables
    Matriz a, b; //Se declaran las matrices
    OrMtx(&m,&n); //Asignamos el orden de las matrices
    printf("m = %d, n = %d\n",m,n); //Impresión de las dimensiones de la matriz
    consMtx(&a, m, n); //Construye la matriz

    ret = mtxInv(a, &b); //Calcula la inversa de la matriz
    NotNegZero(&b); //Cambia los -0 a 0 en la matriz
    if(ret == 1){ //Si la matriz es invertible
        imp(b); //se imprime la matriz
        puts("===========================");
        comp(a, b); //Compara las matrices
    }else if(ret == 0){ //Si la matriz no es invertible
        printf("La matriz es no inversible. \n");
    }

    destMtx(&a); //Se libera la memoria destruyendo la matriz
    return 0; //Se termina la ejecución
}
//Construcción de Matriz
void consMtx(Matriz *a, int m, int n){
    char c; //Se declaran las variables
    int d = 1;

    a->m = m; //Se asigna un número de filas
    (*a).n = n; //Se asigna el número de columnas 
    
    initMatrix(a); //Inicialización de la matriz
    Menu(a,m,n); //Menú para llenado de matriz
    puts("=========="); 
    imp(*a); //Se imprime la matriz
    puts("==========");
}
//Menú que se muestra para llenar la matriz 
void Menu(Matriz *a, int m, int n)
{
    int d=1;
    char c;

    while(d==1){
        puts("Menu");
        puts("Desea llenar la matriz manualmente o generar sus datos aleatoreamente?");
        puts("1. Llenar manualmente");
        puts("2. Generar datos");
        fseek(stdin,0,SEEK_END);
        c = getchar();
        switch(c){
            case '1': //En caso de que la opción sea 1
                printf("Llene la matriz %d x %d: \n", m, n);
                fill(*a); //Se llena la matriz con valores ingresados por el usuario
                d = 0;
                break; //Se termina el proceso
            case '2': //En caso de que la opción sea 2
                fillRand(*a); //Llena la matriz con valores aleatorios
                d = 0;
                break; //Se termina el proceso
            default:
                puts("Opción no existente\n\n");
                fflush(stdin);
                break;
        }
    }
}
//Inicializacion de matriz
void initMatrix(Matriz *x){
    x->mtx = malloc(x->m * sizeof(float *)); //Asigna memoria para las filas de la matriz
    for(int i=0; i < x->m; i++)
        x->mtx[i] = malloc(x->n * sizeof(float)); //Asigna memoria para las columnas de la matriz
}
//Liberacion de matriz
void destMtx(Matriz *a){
    int i;
    for(i = 0; i<(*a).m; i++)
        free((*a).mtx[i]); //Libera la memoria asignada a cada fila de la matriz
    free((*a).mtx); //Libera la memoria asignada al array de punteros
    (*a).mtx = NULL; //Asigna NULL al puntero para evitar referencias a memoria liberada
}
//Impresion de matriz
void imp(Matriz a){
    int i, j;
    for(i=0; i<a.m; i++){
        printf("| ");
        for(j=0; j<a.n; j++){
            printf("%.2f ", a.mtx[i][j]); //Imprime cada elemento de la matriz
        }
        printf(" | \n");
    }
}
//Llenado de matriz
void fill(Matriz a){
    int i, j;
    char x[100];
    for(i=0; i<a.m; i++){
        for(j=0; j<a.n; j++){
            printf("[A]%dx%d = ",i+1,j+1);
            scanf("%s", x); //Lee el valor ingresado por el usuario
            if(verFltJ(x)){ //Verifica si el valor ingresado es un número flotante válido
                a.mtx[i][j] = StrToFlt(x); //Convierte la cadena de caracteres a un número flotante y lo asigna a la matriz
                printf("[a]%dx%d = %.2f\n\n",i+1,j+1,a.mtx[i][j]);
            }else{
                puts("(!) Ingrese un flotante valido (!)");
                j--; //Si el valor no es válido, se repite la iteración para el mismo elemento de la matriz
            }
        }
    }
}
//Inicializacion de matriz con 0
void fillZero(Matriz a){
    int i, j;
    for(i=0; i<a.m; i++){
        for(j=0; j<a.n; j++){
            a.mtx[i][j] = 0; //Asigna el valor 0 a cada elemento de la matriz
        }
    }
}
//Llenado aleatorio de matriz
void fillRand(Matriz a){
    int i, j, ranInt;
    for(i=0; i<a.m; i++)
        for(j=0; j<a.n; j++){
            ranInt = rand()%2; //Genera un número aleatorio, 0 o 1
            if (ranInt == 0)
                a.mtx[i][j] = rand()*(-10); //Si el número aleatorio es 0, asigna un número aleatorio negativo a la matriz
            else
                a.mtx[i][j] = rand()*50; //Si el número aleatorio es 1, asigna un número aleatorio positivo a la matriz
        }
}
//Construccion de matriz identidad
void mtxIn(Matriz a, Matriz *b){
    if(a.m == a.n){ //Verifica si la matriz es cuadrada
        b->m = a.m; //Asigna el número de filas de la matriz original a la matriz identidad
        b->n = a.m; //Asigna el número de columnas de la matriz original a la matriz identidad
        initMatrix(b); //Inicializa la matriz identidad
        int i, j;
        for(i = 0; i < b->m; i++){ //Recorre las filas de la matriz identidad
            for(j=0; j < b->n; j++){ //Recorre las columnas de la matriz identidad
                if(i == j){ //Si la fila es igual a la columna (diagonal principal)
                    b->mtx[i][j] = 1; //Asigna el valor 1 a la posición [i][j] de la matriz identidad 
                }else{
                    b->mtx[i][j] = 0; //Asigna el valor 0 a la posición [i][j] de la matriz identidad 
                }
            }
        }
    }else{
        printf("(!) Esta funcion requiere una matriz cuadrada \n"); //Imprime un mensaje de error si la matriz no es cuadrada
    }
}

void swap(Matriz a, int i, int j){ //Intercambio de filas
    float *aux = a.mtx[i]; //Guarda la dirección de memoria de la fila i en aux
    a.mtx[i] = a.mtx[j]; //Asigna la dirección de memoria de la fila j a la fila i
    a.mtx[j] = aux; //Asigna la dirección de memoria guardada en aux (fila i original) a la fila j
}
//Multiplicación de matrices
void mult(Matriz a, Matriz b, Matriz c){
    if(a.n == b.m){ //Verifica si el número de columnas de la matriz a es igual al número de filas de la matriz b
        int i, j, k;
        fillZero(c); //Llena la matriz c con ceros 
        if(c.m != a.m || c.n != b.m){ //Si las dimensiones de la matriz c no son correctas, las ajusta
            c.m = a.m;
            c.n = b.n;
        }
        for(i=0; i<b.n; i++){ //Recorre las columnas de la matriz b
            for(j=0; j<a.m; j++){ //Recorre las filas de la matriz a
                for(k=0; k<a.n; k++){ //Recorre las columnas de la matriz a
                    c.mtx[j][i] += (a.mtx[j][k])*(b.mtx[k][i]); //Realiza la multiplicación de matrices y acumula el resultado en la matriz c
                }
            }
        }
    }else{
        printf("(!) El numero de columnas de la primera matriz debe de ser igual al numero de filas de la segunda matriz.");
    }
}
//Comparación de matrices
void comp(Matriz a, Matriz b){
    Matriz c;
    c.m = a.m;
    c.n = a.n;
    initMatrix(&c); //Inicializa la matriz c
    mult(a, b, c); //Multiplica las matrices a y b, guardando el resultado en la matriz c
    printf("A(A^-1) = \n");
    imp(c); //Imprime la mariz c 
    puts("***************************");
    mult(b, a, c); //Multiplica las matrices b y a, y guarda el resultado en c
    printf("(A^-1)A = \n");
    imp(c); //Imprime la matriz c
}
//Copia de matriz
void copy(Matriz orgnal, Matriz *cpy){
    if(orgnal.m == cpy->m && orgnal.n == cpy->n){ //Verifica si las dimensiones de las matrices son iguales
        int i, j;
        for(i = 0; i < orgnal.m; i++){ //Recorre las filas 
            for(j = 0; j < orgnal.n; j++){ //Recorre las columnas
                cpy->mtx[i][j] = orgnal.mtx[i][j]; //Copia cada elemento de la matriz original a la matriz copia
            }
        }
    }else{
        printf("La matriz destino tiene que ser del mismo tamaño. \n");
    }
}
//Cálculo de la inversa de la matriz
int mtxInv(Matriz aOr, Matriz *aInv){
    if(aOr.m == aOr.n){ //Verifica si la matriz es cuadrada
        int i, j, k, flg = 0, simp = 0;
        float x, y;
        Matriz a; a.m = aOr.m; a.n = aOr.n;
        initMatrix(&a); //Inicializa la matriz a
        copy(aOr, &a); //Copia la matriz original a la matriz a 
        mtxIn(a, aInv); //Crea una matriz identidad del mismo tamaño que a y la guarda en aInv
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
void OrMtx(int *m, int *n){
    char ms[5], ns[5];
    puts("Ingrese las dimensiones de la matriz\n");
    printf("m = ");
    scanf("%s", ms);
    putchar('\n');
    printf("n = ");
    scanf("%s", ns);
    putchar('\n');
    if(verDim(ms,ns)){
        *m = StrToInt(ms);
        *n = StrToInt(ns);

        if(*m == *n)
            printf("Orden de la matriz: %d\n",*m);
        else{
                puts("\n(!) La matriz debe de ser cuadrada (!)");
                OrMtx(m,n);
            }
        
    }else{
            puts("\n(!) Inserte enteros positivos validos (!)\n");
            OrMtx(m,n);
        }
}

//funcion que verifica si los numeros si son numeros :v
int verDim(char *m, char *n){
    if(verInt(m)&&verInt(n))
        return 1;
    else
        return 0;
}

int isdigitJ(char x){
    if(x >= '0'  && x <= '9')
        return 1;
    else
        return 0;
}

//predicado para verificar si la cadena de caracteres solo contiene nums :v
int verInt(char *x){
    int i;
    for(i = 0; i < strlen(x); i++)
        if(!isdigitJ(*(x+i)))
            return 0;
    return 1;
}

int ChrToInt(char c){return c - '0';}

int powJ(int b, int e){
    int n;
    if(e == 0)
        return 1;
    for(n = 1; e > 0; e--)
        n  *= b;
    return n;
}

int StrToInt(char *ch){
    int i,j, res = 0;
    for(i = strlen(ch)-1, j = 0; i >= 0; i--,j++)
        res += ChrToInt(*(ch+j))*powJ(10,i);
    return res;
}

int verFltJ(char *fl){
    int ver = verSign(fl);
    if(ver)
        if(ver == 1){
            if(isFloat(fl+1))
                return 1;
            else return 0;
        }
        else{
            if(isFloat(fl))
                return 1;
            else return 0;
        }
    else return 0;
}

int verSign(char *fl){
    if(*fl == '-')
        return 1;
    else if(*fl == '.' || isdigitJ(*fl))
            return 2;
        else return 0;
}

int isFloat(char *x){
    int i;
    if(strlen(x)==1 && *x == '.')
        return 0;
    else{
        if(CountDot(x) == 0 || CountDot(x) == 1) {
            for(i = 0; i < strlen(x); i++){
                if(!checkFloat(*(x + i)))
                    return 0;
            }
            return 1;
        }
        else 
            return 0;
    }
}

int CountDot(char *x){
    int count = 0,i;
    for(i = 0; i < strlen(x); i ++){
        if(*(x + i) == '.')
            count++;
    }

    return count;
}

int checkFloat(char x){
    if(isdigitJ(x) || x == '.')
        return 1;
    else
        return 0;
}

float powJFlt(float b, int e){
    int i;
    float res = 1; 
    if(e >= 0){
        for(i = 1; i <= e; i++)
            res *= b;
        return res;
    }
    else{
        e *= -1;
        for(i = 0; i < e; i++)
            res *= b;
        return 1/res;
    }
}

int DotLoc(char *x){
    int i, count = 0;
    for(i = 0; i < strlen(x); i++){
        if(*(x + i) == '.')
            return count;
        else count++;
    }
    return -1;
}

float StrToFlt(char *x){
    int i,j, dotcount;
    float res = 0;
    dotcount = DotLoc(x);
    if(dotcount == -1){
        if(*x == '-'){
            x += 1;
            for(i = strlen(x)-1, j = 0; i >= 0; i--,j++)
                res += ChrToFlt(*(x+j))*powJFlt(10,i);
            res = -res;
        }
        else{
            for(i = strlen(x)-1, j = 0; i >= 0; i--,j++)
                res += ChrToFlt(*(x+j))*powJFlt(10,i);
        }
    }
    else if(dotcount == 0){
            x += 1;
            for(i = -strlen(x), j = 0; i <= 0; i++, j++)
            res += ChrToFlt(*(x+j))*powJFlt(10,i);
        }
        else if(dotcount == 1) {
                if(*x == '-'){
                    for(i = -1, j=2; j < strlen(x); i--,j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                    res = -res;
                }
                else{
                    for(i = dotcount-1, j = 0; i >= 0; i--, j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                    for(i = -1, j=dotcount+1; j < strlen(x); i--,j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                }
            }
            else{
                if(*x == '-'){
                    x += 1;
                    for(i = dotcount, j = 0; i >= 0; i--, j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                    for(i = -1, j=dotcount; j < strlen(x); i--,j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                    res = -res;
                }
                else{
                    for(i = dotcount-1, j = 0; i >= 0; i--, j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                    for(i = -1, j=dotcount+1; j < strlen(x); i--,j++)
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i);
                }
            }
    return res;
}

float ChrToFlt(char x){
    if(x >= '0' && x<= '9')
        return x - 48;
}

void NotNegZero(Matriz *x){
    int i,j;
    for(i = 0; i < x->m; i++)
        for(j = 0; j < x->n; j++)
            if(x->mtx[i][j] == -0)
                x->mtx[i][j] *= -0;
}

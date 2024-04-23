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
        if(a.mtx[0][0] == 0){ //Cuando el primer elemento de la matriz a es 0
            for(i=1; i<a.m; i++){ //recorre las filas de la matriz a
                if(a.mtx[i][0] != 0){ //si encuentra una fila cuyo primer elemento no es 0
                    swap(a, 0, i); //intercambia la fila i con la fila 0
                    swap(*aInv, 0, i); //Hace lo mismo con la matriz aInv
                    break; //Termina el proceso
                }
            }
            if(i == a.m){ //Si todas las filas tienen 0 en la primera columna, la matriz no es invertible 
                return 0;
            }
        }

        for(i=0; i<a.m; i++){ //Recorre las filas de la matriz a
            x = a.mtx[i][i]; //Guarda el elemento en la diagonal 
            for(j=0; j<a.m; j++){ //Recorre las filas de la matriz a
                y = a.mtx[j][i]; //Guarda el elemento en la columna i
                if(i!=j){ //Si no estamos en la diagonal 
                    for(k=0; k<a.m; k++){ //Recorre las columnas de la matriz a
                        if(!simp && x != 1){ //Si el elemento en la diagonal no es 1, divide toda la fila por el elemento en la diagonal
                            a.mtx[i][k] = a.mtx[i][k]/x; //Se divide la fila por el elemento en la diagonal
                            aInv->mtx[i][k] = aInv->mtx[i][k]/x;
                            if(k == a.m-1){
                                simp = 1;
                            }
                        }
                        a.mtx[j][k] = a.mtx[j][k] - y*a.mtx[i][k]; //Resta a la fila j la fila i multiplicada por y
                        aInv->mtx[j][k] = aInv->mtx[j][k] - y*aInv->mtx[i][k]; //Hace lo mismo en la matriz aInv

                        if(a.mtx[j][k] != 0){
                                flg = 1;
                        }
                    }
                }else{
                    flg = 1;
                }
                if(!flg){ //Si una fila se convierte en 0, la matriz no es inversible
                    return 0;
                }else{
                    flg = 0;
                }
            }
            simp = 0;
        }
        destMtx(&a); //Libera la memoria de la matriz a
        return 1; //La matriz es invertible 
    }else{
        printf("(!) Esta funcion requiere de una matriz de orden n. \n");
        return -1; //La matriz no es cuadrada
    }
}
//Asignación del orden de la matriz
void OrMtx(int *m, int *n){
    char ms[5], ns[5];
    puts("Ingrese las dimensiones de la matriz\n"); //Solicita al usuario que ingrese las dimensiones de la matriz
    printf("m = ");
    scanf("%s", ms); //Lee el número de filas de la matriz
    putchar('\n');
    printf("n = ");
    scanf("%s", ns); //Lee el número de columnas de la matriz
    putchar('\n');
    //Verifica si las dimensiones ingresadas son números enteros válidos
    if(verDim(ms,ns)){
        *m = StrToInt(ms); //Convierte la cadena de caracteres a un número entero para el número de filas
        *n = StrToInt(ns); //Convierte la cadena de caracteres a un número entero para el número de columnas
        //Verifica si la matriz es cuadrada (que el número de filas sea igual al número de columnas)
        if(*m == *n)
            printf("Orden de la matriz: %d\n",*m); //Imprime el orden de la matriz si es cuadrada
        else{
                puts("\n(!) La matriz debe de ser cuadrada (!)"); //Imprime un mensaje de error si la matriz no es cuadrada
                OrMtx(m,n); //Llama a la función de nuevo para solicitar dimensiones válidas
            }
        
    }else{
            puts("\n(!) Inserte enteros positivos validos (!)\n"); //Imprime un mensaje de error si las dimensiones ingresadas no son números enteros válidos
            OrMtx(m,n); //Llama a la función de nuevo para solicitar dimensiones válidas
        }
}
//Verifica las dimensiones de la matriz
int verDim(char *m, char *n){ 
    if(verInt(m)&&verInt(n)) //Si ambas cadenas son números enteros
        return 1; //Regresa verdadero
    else //Si no
        return 0; //Regresa falso 
}
//Verifica si un carácter es un dígito
int isdigitJ(char x){
    if(x >= '0'  && x <= '9') //Si el carácter está en el rango de '0' a '9'
        return 1; //Regresa verdadero
    else
        return 0; //Regresa falso
}
//Verifica si una cadena de caracteres es un número entero
int verInt(char *x){
    int i;
    for(i = 0; i < strlen(x); i++) //Recorre cada carácter de la cadena
        if(!isdigitJ(*(x+i))) //Si el carácter no es un dígito
            return 0; //Regresa falso
    return 1; //Regresa verdadero
}
//Convierte un carácter a un número entero
int ChrToInt(char c){return c - '0';}
//Calcula la potencia de un número
int powJ(int b, int e){
    int n;
    if(e == 0) //Si el exponente es 0
        return 1; //Regresa 1
    for(n = 1; e > 0; e--) //Mientras el exponente sea mayor que 0
        n  *= b; //Multiplica el número base por si mismo
    return n; //Retorna el resultado
}
//Convierte una cadena de caracteres a un número entero
int StrToInt(char *ch){
    int i,j, res = 0;
    for(i = strlen(ch)-1, j = 0; i >= 0; i--,j++) //Recorre cada carácter de la cadena
        res += ChrToInt(*(ch+j))*powJ(10,i); //Convierte el carácter a entero y lo multiplica por la potenciade 10 correspondiente
    return res; //Regresa el resultado
}
//Verifica si una cadena de caracteres es un número flotante
int verFltJ(char *fl){
    int ver = verSign(fl);
    if(ver)
        if(ver == 1){
            if(isFloat(fl+1)) //Si la cadena sin el signo es un flotante
                return 1; //Regresa verdadero
            else return 0; //Regresa falso
        }else{
            if(isFloat(fl)) //Si la cadena es un flotante
                return 1; //Retorna verdadero
            else return 0; //Retorna falso
        }
    else return 0; //Retorna falso
}
//Verificación del signo de una cadena.
int verSign(char *fl){
    if(*fl == '-') //Si el primer carácter es un signo negativo
        return 1; //Regresa 1
    else if(*fl == '.' || isdigitJ(*fl)) //Si el primer carácter es un punto o un dígito
            return 2; //Regresa 2
        else return 0; //Regresa 0
}

//Verificacion si una cadena de caracteres es un número flotante.
int isFloat(char *x){
    int i;
    if(strlen(x)==1 && *x == '.') //Si la cadena solo contienen un punto
        return 0; //Regresa falso
    else{
        if(CountDot(x) == 0 || CountDot(x) == 1) { //Si la cadena no contiene puntos o solo contiene un punto
            for(i = 0; i < strlen(x); i++){ //Recorre cada carácter de la cadena
                if(!checkFloat(*(x + i))) //Si el carácter no es un dígito ni un punto
                    return 0; //Regresa falso
            }
            return 1; //Regresa verdadero 
        }
        else 
            return 0; //Regresa falso
    }
}
//Cuenta el número de puntos en una cadena de caracteres
int CountDot(char *x){
    int count = 0,i;
    for(i = 0; i < strlen(x); i ++){ //Recorre cada carácter de la cadena
        if(*(x + i) == '.') //Si el carácter es un punto
            count++; //Incrementa el contador
    }
    return count; //Regresa el contador
}
//Verifica si un carácter es un número flotante
int checkFloat(char x){
    if(isdigitJ(x) || x == '.') //Si el carácter es un dígitoo un punto
        return 1; //Regresa verdadero
    else
        return 0; //Regresa falso
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
//Convierte una cadena de caracteres a un número flotante
float StrToFlt(char *x){
    int i,j, dotcount;
    float res = 0;
    dotcount = DotLoc(x); //Encuentra la ubicación del punto en la cadena
    if(dotcount == -1){ //Si no hay un punto en la cadena 
        if(*x == '-'){ //Si el número es negativo
            x += 1; //Avanza un caracter en la cadena para ignorar el signo negativo
            for(i = strlen(x)-1, j = 0; i >= 0; i--,j++) //Itera sobre cada carácter de la cadena
                res += ChrToFlt(*(x+j))*powJFlt(10,i); //Convierte el carácter a flotante y lo multiplica por la potencia de 10 correspondiente 
            res = -res; //Cambia el signo del resultado a negativo
        }else{ //Si es número es positivo
            for(i = strlen(x)-1, j = 0; i >= 0; i--,j++) //Itera sobre cada carácter de la cadena
                res += ChrToFlt(*(x+j))*powJFlt(10,i); //Convierte el caácter a flotante y lo multiplica por la potencia de 10 correspondiente
        }
    }else if(dotcount == 0){ //Si el punto está al principio de la cadena
            x += 1; //Avanza un carácter en la cadena para ignorar el punto
            for(i = -strlen(x), j = 0; i <= 0; i++, j++) //Itera sobre cada carácter de la cadena
            res += ChrToFlt(*(x+j))*powJFlt(10,i); //Convierte el carácter a flotante y lo multiplica por la potencia de 10 correspondiente
        }else if(dotcount == 1) { //Si el punto está en la segunda posición 
                if(*x == '-'){ //Si el número es negativo
                    for(i = -1, j=2; j < strlen(x); i--,j++) //Itera sobre cada carácter de la cadena, ignorando el signo negativo y el punto
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i); //Convierte el carácter a flotante y lo multiplica por la potencia de 10 correspondiente
                    res = -res; //Cambia el signo del resultado a negativo
                }else{ //Si el número es positivo
                    for(i = dotcount-1, j = 0; i >= 0; i--, j++) //Itera sobre cada carácter de la cadena hasta el punto
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i); //Convierte el carácter a flotante y lo multiplica por la potencia de 10 correspondiente
                    for(i = -1, j=dotcount+1; j < strlen(x); i--,j++) //Itera sobre cada carácter de la cadena después del punto
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i); //Convierte el carácter a flotante y lo multiplica por la potencia de 10 correspondiente
                }
            }else{ //Si el punto está en cualquier otra posición de la cadena
                if(*x == '-'){ //Si el número es negativo
                    x += 1; //Avanza un carácter en la cadena para ignorar el signo negativo
                    for(i = dotcount, j = 0; i >= 0; i--, j++) //Itera sobre cada carácter de la cadena hasta el punto
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i); //Convierte el carácter a flotante y lo multiplica por la potencia de 10 correspondiente
                    for(i = -1, j=dotcount; j < strlen(x); i--,j++) //Itera sobre cada carácter de la cadena después del punto
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i); //Convierte el carácter a flotante y lo multiplica por la potencia de 10 correspondiente
                    res = -res; //Cambia el signo del resultado a negativo
                }else{ //Si el número es positivo
                    for(i = dotcount-1, j = 0; i >= 0; i--, j++) //Itera sobre cada carácter de la cadena hasta el punto
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i); //Convierte el carácter a flotante y lo multiplica por la potencia de 10 correspondiente
                    for(i = -1, j=dotcount+1; j < strlen(x); i--,j++) //Itera sobre cada carácter de la cadena después del punto
                        res =+ ChrToFlt(*(x+j))*powJFlt(10,i); //Convierte el carácter a flotante y lo multiplica por la potencia de 10 correspondiente
                }
            }
    return res; //Devuelve el resultado
}
//Convierte un carácter a un número flotante
float ChrToFlt(char x){
    if(x >= '0' && x<= '9') //Si el carácter es un dígito
        return x - 48; //Convierte el carácter a flotante restando el valor ASCIIde '0'
}
//Cambia los -0 en la matriz a 0
void NotNegZero(Matriz *x){
    int i,j;
    for(i = 0; i < x->m; i++) //Itera sobre las filas de la matriz
        for(j = 0; j < x->n; j++) //Itera sobre las columnas de la matriz
            if(x->mtx[i][j] == -0) //Si el elemento de la matriz es -0
                x->mtx[i][j] *= -0; //Cambia el elemento a 0
}

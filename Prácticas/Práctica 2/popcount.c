/*
 * PROGRAMA POPCOUNT
 *   ESTRUCTURA DE COMPUTADORES
 *   Alumno: Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 *   Fecha:  2 de diciembre, 2018
 *   Curso:  2º Doble Grado en Ingeniería Informática y Matemáticas, 2018/19
 */

#include <stdio.h>      // printf()
#include <stdlib.h>     // exit()
#include <sys/time.h>	// gettimeofday(), struct timeval
#include <math.h>

#define WSIZE 8*sizeof(int)

#define SIZE 1<<20
unsigned lista[SIZE];

int total=0;


// VERSIÓN 1
int popcount_v1(unsigned *array, int longitud) {
    int i, j, resultado = 0;
    for ( i=0; i<longitud; i++ )
        for ( j=0; j<WSIZE; j++ ) {   // WSIZE es 8*sizeof(int)
            unsigned mask = 0x1 << j;
            resultado += (array[i] & mask) != 0;
        }
    return resultado;
}

// VERSIÓN 2
int popcount_v2(unsigned *array, int longitud) {
    int i, j, resultado = 0;
    for ( i=0; i<longitud; i++ ) {
        unsigned x = array[i];
        do {
            resultado += x & 0x1;
            x >>= 1;
        } while (x);
    }
    return resultado;
}

// VERSIÓN 3
int popcount_v3(unsigned *array, int longitud) {
    int i, resultado = 0;
    for ( i=0; i<longitud; i++ ) {
        unsigned x = array[i];
        asm("\n"
           ".ini3:			\n\t"
           "shr %[x]		\n\t"
           "add $0, %[r]	\n\t"
           "cmp $0, %[x]	\n\t"
           "jne .ini3		\n\t"
           
           : [r] "+r" (resultado)
           : [x] "r" (x));
    }
    return resultado;
}

// VERSIÓN 4
int popcount_v4(unsigned *array, int longitud) {
    int i, j, resultado = 0;
    for ( i=0; i<longitud; i++ ) {
        int aux = 0;
        unsigned x = array[i];
        for ( j=0; j<8; j++ ) {
            aux += x & 0x01010101;
            x >>= 1;
        }
        
        aux += (aux>>16);
        aux += (aux>>8);
        resultado += (aux&0xff);
    }
    return resultado;
}

// VERSIÓN 5
int popcount_v5(unsigned *array, int longitud) {
    int i, aux, resultado=0;
    int SSE_mask[] = { 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f };
	int SSE_LUTb[] = { 0x02010100, 0x03020201, 0x03020201, 0x04030302 };
    
    if ( longitud & 0x3 )
        printf("Leyendo 128 bits, pero longitud no múltiplo de 4\n");
    
    for ( i=0; i<longitud; i+=4 ) {
        asm(
        	"movdqu %[x], %%xmm0	\n\t"
			"movdqu %[m], %%xmm6	\n\t"
			"movdqa %%xmm0, %%xmm1	\n\t"
			"psrlw $4, %%xmm1		\n\t"
			"pand %%xmm6, %%xmm0	\n\t"
			"pand %%xmm6, %%xmm1	\n\t"
			"movdqu %[l], %%xmm2	\n\t"
			"movdqa %%xmm2, %%xmm3	\n\t"
			"pshufb %%xmm0, %%xmm2	\n\t"
			"pshufb %%xmm1, %%xmm3	\n\t"
			"paddb %%xmm2, %%xmm3	\n\t"
			"pxor %%xmm0, %%xmm0	\n\t"
			"psadbw %%xmm0, %%xmm3	\n\t"
			"movhlps %%xmm3, %%xmm0	\n\t"
			"paddd %%xmm3, %%xmm0	\n\t"
			"movd %%xmm0, %[aux]	\n\t"

			: [aux] "=r" (aux)
			: [x] "m" (array[i]),
			[m] "m" (SSE_mask[0]),
			[l] "m" (SSE_LUTb[0])
        );
        resultado += aux;
    }
    return resultado;
}

// VERSIÓN 6
int popcount_v6(unsigned *array, int longitud) {
    int i, aux, resultado = 0;
    unsigned x;
    for ( i=0; i<longitud; i++ ) {
        x = array[i];
        asm(
            "popcnt %[x], %[aux]"
            
            : [aux] "=r" (aux)
            : [x] "r" (x)
        );
        resultado += aux;
    }
    return resultado;
}


// FUNCIÓN CRONO
void crono(int (*func)(), char* msg){
    struct timeval tv1,tv2;	// gettimeofday() secs-usecs
    long           tv_usecs;	// y sus cuentas

    gettimeofday(&tv1,NULL);
    total = func(lista, SIZE);
    gettimeofday(&tv2,NULL);

    tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
             (tv2.tv_usec-tv1.tv_usec);
    printf("total = %d\t", total);
    printf("%s:%9ld us\n", msg, tv_usecs);
}


int main() {
	unsigned i;
	for(i=0; i<SIZE; i++)
        lista[i]=i;
    
    crono(popcount_v1, "popcount (v1)");
    crono(popcount_v2, "popcount (v2)");
    crono(popcount_v3, "popcount (v3)");
    crono(popcount_v4, "popcount (v4)");
    crono(popcount_v5, "popcount (v5)");
    crono(popcount_v6, "popcount (v6)");
    printf("nºbits*tamaño/2 = %d\n", (1<<20)*20/2);

    exit(0);
}
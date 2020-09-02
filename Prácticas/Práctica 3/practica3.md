**`ED`  >  Prácticas  >  Práctica 2**

# :three: Desensamblado

> Alumno: Miguel Ángel Fernández Gutiérrez \<<mianfg@correo.ugr.es>\>
>
> Fecha: 21 de diciembre, 2018
>
> Curso: 2º Doble Grado en Ingeniería Informática y Matemáticas, 2018/19



## Mi bomba

Mi bomba pide dos cosas:

* Una **clave** (numérica), generada **aleatoriamente**.
* Una contraseña (alfanumérica), que tiene como valor `"viva euler manque pierda\n"`.

Además, he implementado diversas funciones de _distracción_.

* `distract()` que devuelve el mismo número que se le ha pasado mediante un contador con un `for` en caso de que el número sea mayor o igual que cero, o devuelve directamente el número en caso contrario. Además, añade confusión adicional que se pase a esta función una variable declarada pero no inicializada (con un valor que se encuentre en memoria). Basta hacer

  ~~~c
  int distraction;
  if ( distract(distraction) == distraction )
  	...
  ~~~

  pues este código siempre devolverá `true`.

* `credits()` que pone información sobre el creador de la bomba.

* `oops()` que muestra un dibujo si la bomba explota, concretamente:

  ~~~
                               ____
                       __,-~~/~    `---.
                     _/_,---(      ,    )
                 __ /        <    /   )  \___
  - ------===;;;'====------------------===;;;===----- -  -
                \/  ~"~"~"~"~"~\~"~)~"/
                (_ (   \  (     >    \)
                 \_( _ <         >_>'
                    ~ `-i' ::>|--"
                        I;|.|.|
                       <|i::|i|`.
                      (` ^'"`-' ")
  
  ¡Oops! Parece que la bomba ha explotado :(
  ~~~

* `yougotit()` que muestra un dibujo si se desactiva la bomba, concretamente:

  ~~~
                ____
              /____ `\
             ||_  _`\ \
       .-.   `|O, O  ||
       | |    (/    -)\
       | |    |`-'` |\`
    __/  |    | _/  |
   (___) \.  _.\__. `\___
   (___)  )\/  \    _/  ~\.
   (___) . \   `--  _   `\
    (__)-    ,/        (   |
         `--~|         |   |
             |         |   |
  
  ¡Genial, acertaste! :)
  ~~~

Por otra parte, el `main()` contiene otro nuevo dibujo, y en él se genera el número aleatorio. Mi código es como sigue.



###### :computer: Código de `bomba_mianfg.c`

~~~c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int distract(int n) {
    int contador = 0;
    if ( n>0 )
        for ( int i = 0; i < n; i++ )
            contador++;
    else
        contador = n;

    return contador;
}

void credits() {
    printf("\nBomba por Miguel Ángel Fernández Gutiérrez\n");
    printf("    @mianfg - github.com/mianfg\n");
    printf("    2º DGIIM 2018/2019, UGR\n");
}

void oops() {
    printf("                             ____\n");
    printf("                     __,-~~/~    `---.\n");
    printf("                   _/_,---(      ,    )\n");
    printf("               __ /        <    /   )  \\___\n");
    printf("- ------===;;;'====------------------===;;;===----- -  -\n");
    printf("              \\/  ~\"~\"~\"~\"~\"~\\~\"~)~\"/\n");
    printf("              (_ (   \\  (     >    \\)\n");
    printf("               \\_( _ <         >_>'\n");
    printf("                  ~ `-i' ::>|--\"\n");
    printf("                      I;|.|.|\n");
    printf("                     <|i::|i|`.\n");
    printf("                    (` ^'\"`-' \")\n");
    printf("\n¡Oops! Parece que la bomba ha explotado :(\n");
    credits();
    exit(0);
}

void yougotit() {
    printf("              ____\n");
    printf("            /____ `\\\n");
    printf("           ||_  _`\\ \\\n");
    printf("     .-.   `|O, O  ||\n");
    printf("     | |    (/    -)\\\n");
    printf("     | |    |`-'` |\\`\n");
    printf("  __/  |    | _/  |\n");
    printf(" (___) \\.  _.\\__. `\\___\n");
    printf(" (___)  )\\/  \\    _/  ~\\.\n");
    printf(" (___) . \\   `--  _   `\\\n");
    printf("  (__)-    ,/        (   |\n");
    printf("       `--~|         |   |\n");
    printf("           |         |   |\n");
    printf("\n¡Genial, acertaste! :)\n");
    credits();
    exit(0);
}

#define MAXSIZE 100

int main() {
    int clave; char contrasenia[] = "viva euler manque pierda\n";
    int entrada_i; char entrada_s[MAXSIZE];
    int distraction;

    printf("                                                         c=====e\n");
    printf("                                                            H\n");
    printf("   ____________                                         _,,_H__\n");
    printf("  (__((__((___()                                       //|     |\n");
    printf(" (__((__((___()()_____________________________________// |DGIIM|\n");
    printf("(__((__((___()()()------------------------------------'  |_____|\n\n");

    srand(time(NULL));
    clave = rand() % 100;
    printf("-- ¡CORRE! Inserta la ");
    if ( distract(distraction) == distraction )
        printf(" clave");
    printf(", ¡seguro que la adivinas! -> ");
    scanf("%i", &entrada_i);
    if ( entrada_i != clave )
        oops();
    
    printf("\nAhora toca adivinar la contraseña\n");
    printf("¿Quieres una pista? (S/N) -> ");
    fgets(entrada_s, MAXSIZE, stdin);
    fgets(entrada_s, MAXSIZE, stdin);
    
    if ( strcmp(entrada_s, "S\n") == 0 || strcmp(entrada_s, "s") == 0 )
        printf("De acuerdo: es el Primer Axioma\n");
    else
        printf("Okayy, sin problema...\n");
    printf("-- Inserta la contraseña -> ");
    fgets(entrada_s, MAXSIZE, stdin);
    if ( strcmp(entrada_s, contrasenia) != 0 )
        oops();

    yougotit();
}
~~~



## Desensamblado de cierta bomba

He desensamblado una bomba cualquiera de las que se encuentran en SWAD, tomando por tanto la bomba `bombaElena`.

Para el desensamblado, he procedido de la siguiente manera:

1. He abierto `ddd` para ver el desensamblado, viendo que se llama a las funciones: `gettimeofday`, `bomba`, `Esternocleidomastoideo`, además de a las funciones para comparar _strings_ y para imprimir en pantalla y captar por entrada estándar.
2. Para evitar el problema que presenta `gettimeofday`, simplemente modificamos en `ddd` el registro `%eax` cuando se realizan comprobaciones de salto (`jle`) para no caer en la llamada a `bomba`. Para ello simplemente me he dado cuenta de que, antes de llamar a `jle` se llama a `cmp`, luego inserto en `%eax` un valor menor que `0x5`, por ejemplo `0x1`. De este modo evitamos los saltos.
3. Abriendo el editor hexadecimal podemos ver que la contraseña es `holacaracola`. De hecho, podemos comprobar que en la ejecución de la bomba insertar otra contraseña hace que explota, mientras que si se inserta esa continúa la ejecución.
4. Nos basta por tanto encontrar la clave. Para ello, nos basta darnos cuenta de un cierto detalle: es claro que la comparación con la clave se realiza al llamar a la instrucción de ensamblador `cmp %eax, 0x34(esp)`. Analizando las instrucciones de ensamblador anteriores, vemos que en `0x34(esp)` se almacena el resultado de sumar `10` al valor que hemos introducido. Haciendo un simple volcado de memoria vemos que, antes de ejecutar esta instrucción, el valor del registro `%eax` es de `1010`, por lo que la clave que estamos buscando es `1000`.

En efecto, nos basta comprobarlo en la ejecución del programa: introduciendo los valores en al menos 5 segundos conseguiremos desactivar la bomba.

~~~
Introduce la contraseÃ±a: holacaracola
Introduce el cÃ³digo: 1000
***********************************
****** me has desactivado :) ******
***********************************
~~~
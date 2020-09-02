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
    printf("-- ¡CORRE! Inserta la [%i] ", clave);
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
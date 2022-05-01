// io.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Číta jedno slovo zo suboru f oddelene isspace znaky

#include "io.h"

int read_word(char *s, int max, FILE *f){
    int c; //nacitavany char
    int i; //pocet nacitanych znakov
    for (i = 0; i < max-1; ++i) {
        c = fgetc(f);

        if (isspace(c) && i == 0){ //ak by nasledovalo viacero isspace znakov za sebou
            c = fgetc(f);
            while (isspace(c)){ //najde sa prvy platny znak
                c = fgetc(f);
            }
        }

        if (c == EOF){
            s[i] = '\0';
            return EOF;
        }
        else if (isspace(c)){
            s[i] = '\0';
            return i;
        }

        s[i] = (char) c;
    }
    //nacital sa max pocet znakov
    s[i] = '\0';
    i++; //i == max

    if ((c = fgetc(f)) != EOF && !isspace(c)){ //kontola prekrocenia limitu
        i++;
        while ((c = fgetc(f)) != EOF && !isspace(c)){ //docitaju sa znaky
            ; //prazdny while
        }
    }

    return i; //prekrocil sa limit
}

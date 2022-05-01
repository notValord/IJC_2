// htab_free.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Destruktor tabulky

#include "private.h"

void htab_free(htab_t * t){
    htab_clear(t);
    free(t);
    t = NULL;
}


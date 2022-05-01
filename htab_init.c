// htab_init.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Konstruktor tabulky

#include "private.h"

htab_t *htab_init(size_t n){
    if (n <= 0){ //nevieme inicializovat tabulku
        return NULL;
    }

    htab_t *table = malloc( sizeof(htab_t) + sizeof (struct htab_item *) * n);
    if (table == NULL){
        return NULL;
    }
    table->size = 0;
    table->arr_size = n;

    for (int i = 0; i < (int) n; ++i) {
        table->array[i] = NULL; //nastavenie vsetkych pointerov na NULL
    }

    return table;
}
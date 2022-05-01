// htab_lookup_add.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Vyhledá záznam odpovídající řetězci key, ak ho nenajde vytvori ho

#include "private.h"

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key){
    int length = (int) strlen(key);

    htab_pair_t *ptr = htab_find(t, key);
    if (ptr != NULL){ //nasla sa dana polozka
        return ptr;
    }

    // nenasla sa polozka, vytvori a prida sa do tabulky
    size_t index = (htab_hash_function(key) % t->arr_size);
    struct htab_item *var;
    struct htab_item *adding = malloc(sizeof(struct htab_item));

    if(adding == NULL){ //zlyhal malloc
        return NULL;
    }

    adding->htab_pair.key = malloc(length+1);
    adding->next = NULL;
    strcpy((char *)adding->htab_pair.key, key);
    adding->htab_pair.value = 0; //value sa nastavuje v main, ak by sa chcela dana funkcia pouzit nie na pocitanie slov
    t->size++;

    var = t->array[index];
    if (var == NULL){ //prvy prvok v linked liste
        t->array[index] = adding;
        return &t->array[index]->htab_pair;
    }

    for ( ; var->next != NULL ; var = var->next) {
        //prazdny cyklus, anjde koniec linked listu
    }
    var->next = adding;

    return &var->next->htab_pair;
}

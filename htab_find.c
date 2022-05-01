// htab_find.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Vyhledá záznam odpovídající řetězci key

#include "private.h"

htab_pair_t * htab_find(htab_t * t, htab_key_t key){
    const size_t index = (htab_hash_function(key) % t->arr_size);
    for (struct htab_item * ptr = t->array[index]; ptr != NULL; ptr = ptr->next) {
        if (!strcmp((char *)ptr->htab_pair.key,key)){
            return &ptr->htab_pair;
        }
    }
    return NULL;
}

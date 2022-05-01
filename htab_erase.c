// htab_erase.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Ruší zadaný záznam v tabulke, vracia false ak sa nepodarilo odstranit

#include "private.h"

bool htab_erase(htab_t * t, htab_key_t key){
    const size_t index = (htab_hash_function(key) % t->arr_size);
    bool first_time = true;
    struct htab_item *tmp = NULL;

    for ( struct htab_item *ptr = t->array[index]; ptr != NULL ; ptr = ptr->next) {
        if (ptr->htab_pair.key == key && first_time){ //musi sa upravit pointer v poli array
            free((void*)ptr->htab_pair.key);
            t->array[index] = ptr->next;
            free(ptr);
            t->size--;
            return true;
        }
        else if (ptr->htab_pair.key == key){
            free((void*)ptr->htab_pair.key);
            tmp->next = ptr->next;
            free(ptr);
            return true;
        }
        tmp = ptr;
        first_time = false;
    }
    return false;
}

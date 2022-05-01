// htab_move.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Přesunie data do nové tabulky

#include "private.h"

htab_t *htab_move(size_t n, htab_t *from){
    htab_t *to = htab_init(n);
    if (to == NULL){
        return NULL;
    }

    to->arr_size = n;
    to->size = from->size;

    struct htab_pair* tmp = NULL;
    for (int i = 0; i < (int) from->arr_size; ++i) { //prejde pole array
        for (struct htab_item *ptr = from->array[i]; ptr!= NULL ; ptr = ptr->next) { //prejde linked list
            tmp = htab_lookup_add(to, ptr->htab_pair.key); //prepocita sa key a prida sa do novej tabulky
            if (tmp == NULL){
                return NULL;
            }

            tmp->value = ptr->htab_pair.value;
        }
    }

    htab_clear(from); //odstranenie zaznamov z from tabulky
    return to;
}

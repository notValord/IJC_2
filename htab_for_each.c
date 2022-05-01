// htab_for_each.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Projde všechny záznamy a zavolá na ně funkci f

#include "private.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)){
    for (size_t i = 0; i < t->arr_size; ++i) { //prechadza pole
        for (struct htab_item *ptr = t->array[i]; ptr!= NULL ; ptr = ptr->next) { //prechadza linked list
            f(&ptr->htab_pair);
        }
    }
}
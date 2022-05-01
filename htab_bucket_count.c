// htab_bucket_count.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Funkcia vracia velikost pola ukazatelov, arr_size

#include "private.h"

size_t htab_bucket_count(const htab_t * t){
    return t->arr_size;
}

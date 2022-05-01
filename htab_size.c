// htab_size.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Počet záznamů v tabulce, size

#include "private.h"

size_t htab_size(const htab_t * t){
    return t->size;
}
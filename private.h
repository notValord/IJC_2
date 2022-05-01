// private.h
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Deklaracia privatnych struktur htab a htab_item

#ifndef TAIL_PRIVATE_H
#define TAIL_PRIVATE_H

#include "htab.h"
#include <stdint.h> //pre htab_hash_function
#include <stdlib.h> //malloc a NULL

struct htab{
    size_t size;
    size_t arr_size;
    struct htab_item *array[];
};

struct htab_item{
    struct htab_item *next;
    struct htab_pair htab_pair;
};

#endif //TAIL_PRIVATE_H

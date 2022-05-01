// htab_hash_function.c
// Použitie IJC-DU2, příklad b), 18.4.2021
// Přeloženo: gcc Ubuntu 9.3.0
// Prevzata hashovacia funkcia

#include "private.h"

size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}

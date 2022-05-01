// htab_clear.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Ruší všechny záznamy v tabulke, ktora zostane prazdna a alokovana

#include "private.h"

void htab_clear(htab_t* t){
    struct htab_item *ptr = NULL;
    bool check = false;

    for (int i = 0; i < (int) t->arr_size; ++i) { //iteruje po poli ukazatelov
        ptr = t->array[i];

        while (ptr != NULL){ //pokym sa nevynuluje cely linked list
            check = htab_erase(t, ptr->htab_pair.key);
            ptr = t->array[i]; //vzdy sa odstranuje prvy prvok

            if (!check){ //ak by sa nedokazal uvolnit item, aby nedoslo v zacykleniu
                break; //nemalo byt nastat
            }
        }
    }
}

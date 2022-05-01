// wordcount.c
// Řešení IJC-DU2, příklad b), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Program počítá četnost slov oddelene bielym znakom ve vstupním textu

#include <stdio.h>
#include <string.h>
#include "htab.h"
#include "io.h"

/** Je vhodne mat pocet bucketov ako 1.25 nasobok poctu keys + prvocislo
* Predpokladame, ze dany program bude pouzivany na dlhsie texty alebo clanky,
* mozno okolo 10000-20000 slov. Priblizne okolo 60% slov v texte sa opakuje
* takze pocet unikatnych keys by mal byt okolo 8000.
* Prvotny pocet bucketov = 8000 * 1.25 -> prvocislo = 10007
*/
#define N 10007
#define MAX_LENGTH 127 //cita o jedno menej znakov pre '\0'
#define INPUT stdin

#ifdef HASHTEST
size_t htab_hash_function(const char *str) { //vlastna hash funkcia
    unsigned long hash = 7177;
    const int *p;

    for (p=(const int*)str; *p!='\0'; p++)
        hash = (hash << 3) + *p;
    return hash;
}
#endif

void my_print(htab_pair_t *data){
    printf("%s\t%d\n", data->key, data->value);
}

int main(){
    struct htab* tab = htab_init(N);
    if (tab == NULL){
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }

    bool whole_line = true;
    int check = 0;
    FILE *fptr = INPUT;
    char tmp[MAX_LENGTH] = "";
    struct htab_pair *item = NULL; //na zvysenie value jednotlivych keys

    for (check = read_word(tmp, MAX_LENGTH, fptr); check != EOF ; check = read_word(tmp, MAX_LENGTH, fptr)) {

        if (check > MAX_LENGTH && whole_line){ //prvy warning
            whole_line = false;
            fprintf(stderr, "Error: not the whole line have been read.\n");
        }

        item = htab_lookup_add(tab, tmp);
        if (item == NULL){
            fprintf(stderr, "Error, couldn't allocate a new item\n");
            return 1;
        }
        item->value++; //zvacsi sa pocet vyskytov

        if (htab_size(tab) == htab_bucket_count(tab)*2){ //ak sa dostatovne naplnila tabulka tak ju zvacsime
            struct htab* new_tab = htab_move(2*N, tab);
            if(new_tab == NULL){
                fprintf(stderr, "Error, couldn't move the table\n");
                return 1;
            }
            htab_free(tab);
            tab = new_tab;
        }
    }

    if (strlen(tmp)){ //ak posledne slovo bolo ukoncene EOFom
        item = htab_lookup_add(tab, tmp);
        if (item == NULL){
            fprintf(stderr, "Error, couldn't allocate a new item\n");
            return 1;
        }
        item->value++;
    }

#ifdef MOVETEST //presunie sa tabulka a printne sa
    struct htab* move_test = htab_move(N, tab);
    if(move_test == NULL){
        fprintf(stderr, "Error, couldn't move the table\n");
        return 1;
    }
    htab_for_each(move_test, my_print);
    htab_free(move_test);

#else
    htab_for_each(tab, my_print);

#endif

    htab_free(tab);
    return 0;
}
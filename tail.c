// tail.c
// Řešení IJC-DU2, příklad a), 18.4.2021
// Autor: Veronika Molnárová, xmolna08, FIT-1BIT
// Přeloženo: gcc Ubuntu 9.3.0
// Tiskne posledních  10 řádků zo zadaneho suboru

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LENGTH 511
#define LINES_NMB 10

void error(char *message){
    fprintf(stderr, "%s", message);
    exit (1);
}

void printing(int i, int read_lines, char lines[read_lines][MAX_LENGTH+1]){
    for(int start = i; start < i + read_lines ; start++){
        printf("%s",lines[start % read_lines]); //vypisanie riadkov
    }
}

void over_max(FILE *fptr){
    int useless = '0'; //precita zvysne chary nad moznym maximom, nastavenie na inu hodnotu ako '\n'
    while(useless != '\n'){  //docitanie do konca riadku
        useless = fgetc(fptr);
    }
}

void reading_lines(int read_lines, FILE *fptr){
    char lines[read_lines][MAX_LENGTH + 1]; //MAX_LENGTH-1 znakov + '\n' + '\0'
    int length;
    int i; //iteruje po poli, potrebujeme na zistenie konca
    bool whole_line = true; //ci sa nacital cely riadok

    for (int j = 0; j < read_lines; ++j) { //inicializuje stringy na prazdne
        strcpy(lines[j], "");
    }

    for (i = 0; fgets(lines[i], MAX_LENGTH, fptr) != NULL ; i = (i+1) % read_lines) {

        length = (int) strlen(lines[i]);
        if (lines[i][length-1] != '\n'){ //nebol nacitany cely riadok
            strcat(lines[i], "\n");

            if (whole_line){ //prvy krat warning
                whole_line = false;
                fprintf(stderr, "Warning: Not the whole line have been read\n");
            }

            over_max(fptr); //docita sa zvysok riadku

        }
    }

    printing(i, read_lines, lines);
}

void reading_until_end(int read_lines, FILE *fptr){
    char line[MAX_LENGTH + 1] = "";
    int length;
    bool whole_line = true; //ci sa nacital cely riadok


    for (int i = 1; fgets(line, MAX_LENGTH, fptr) != NULL; i++) {

        length = (int) strlen(line);

        if (line[length-1] != '\n'){ //nebol nacitany cely riadok
            strcat(line, "\n");

            if (whole_line){ //prvy krat warning
                whole_line = false;
                fprintf(stderr, "Warning: Not the whole line have been read\n");
            }

            over_max(fptr); //docita sa zvysok stringu
        }
        if (i >= read_lines){ //printuje sa od zadaneho riadku
            printf("%s", line);
        }
    }
}

void only_number(char *number){
    for (int i = 0; i < (int) strlen(number); ++i) {
        if (i == 0 && number[i] != '+' && number[i] != '-' && !isdigit(number[i])){
            error("Error, wrong type of argument\n");
        }
        else if ( i != 0 && !isdigit(number[i])){
            error("Error, wrong type of argument\n");
        }
    }
}

bool getting_arguments(int *read_lines, FILE **fptr, char *file, char *new_nmbr){
    if (strcmp(file, "stdin") != 0){ //pointer zostava rovnaky

        *fptr = fopen(file, "rb");
        if (*fptr == NULL) {
            error("Error, cannot open the file \n");
        }

    }

    if (strcmp(new_nmbr, "MAX_LENGTH") != 0){ //pocet nacitanych riadkov sa nemeni

        *read_lines = strtol(new_nmbr, NULL, 10);
        (*read_lines < 0)? *read_lines *= -1: *read_lines;

        if (*read_lines == 0){
            error("Error, number of lines cannot be zero\n");
        }

        only_number(new_nmbr); //obsahuje iba cisla
        if (new_nmbr[0] == '+'){
            return true;
        }

    }
    return false;
}

int main(int argc, char *argv[]) {
    
    int read_lines = LINES_NMB; //pocet kolko chceme nacitat riadkov
    FILE *fptr = stdin; //z kade sa cita
    bool plus = false;

    switch(argc){
        case 1:  // cita z sdtin
            break;

        case 2:  //zadany subor
            getting_arguments(&read_lines, &fptr, argv[1], "MAX_LENGTH"); //urcite vracia false
            break;

        case 3: //zadany pocet riadkov
            if (!strcmp(argv[1], "-n")) {
                plus = getting_arguments(&read_lines, &fptr, "stdin", argv[2]);
            } else {
                error("Error, wrong arguments\n");
            }
            break;

        case 4: //zadany subor aj pocet riadkov
            if (!strcmp(argv[1], "-n")) {
                plus = getting_arguments(&read_lines, &fptr, argv[3], argv[2]);
            }
            else if (!strcmp(argv[2], "-n")) {
                plus = getting_arguments(&read_lines, &fptr, argv[1], argv[3]);
            }
            else {
                error("Error, wrong arguments\n");
            }
            break;

        default:
            error("Error, too many arguments\n");
    }
    if (plus){ //vypisuje sa od daneho riadku dokonca
        reading_until_end(read_lines, fptr);
    }
    else{ //vypisuje sa urcity pocer poslednych riadkov
        reading_lines(read_lines, fptr);
    }

    if (fptr != stdin){
        fclose(fptr);
    }
    return 0;
}
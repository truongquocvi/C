/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Truong Quoc Vi
 *
 * Created on September 17, 2016, 4:10 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * 
 */
void saveIndex(char word[]);
void saveMeaning(char word[], char meaning[]);
void search();
void add();
void importDB(char fileIndex[], char fileMeaning[], char wordDB[][100], char transDB[][100], char meaningDB[][100], int *count);
void chooseMenu();

int main(int argc, char** argv) {
    chooseMenu();
    return (EXIT_SUCCESS);
}

void chooseMenu() {
    int choice;
    do {
        printf("1. Search\n");
        printf("2. Add\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                search();
                break;
            case 2:
                add();
                break;
            case 3:
                break;
            default:
                printf("Invalid number\n");
                break;
        }
    } while (choice != 3);
}

void search() {
    char word[10];
    printf("Search: ");
    fpurge(stdin);
    gets(word);
    strlwr(word);
    char fileIndex[10] = "";
    char fileMeaning[10] = "";
    char postfix[] = "_index.dat";
    strncpy(fileIndex, word, 1);
    strcat(fileIndex, "_index.dat");
    strlwr(fileIndex);
    strncpy(fileMeaning, word, 1);
    strcat(fileMeaning, "_meaning.dat");
    strlwr(fileMeaning);
    char wordDB[1000][100];
    char transDB[1000][100];
    char meaningDB[1000][100];
    int count;
    importDB(fileIndex, fileMeaning, wordDB, transDB, meaningDB, &count);
    char searchDB[1000][strlen(word)];
    for (int i = 0; i < count; i++) {
        strncpy(searchDB[i], wordDB[i], strlen(word));
        if (strcmp(word, searchDB[i]) == 0) {
            puts(transDB[i]);
            puts(meaningDB[i]);
        }
    }
}

void importDB(char fileIndex[], char fileMeaning[], char wordDB[][100], char transDB[][100], char meaningDB[][100], int *count) {
    FILE* f = fopen(fileIndex, "r");
    FILE* f1 = fopen(fileMeaning, "r");
    char tmp[1000] = "";
    *count = 0;
    int i = 0;
    while (fscanf(f, "%s\n", &wordDB[i]) == 1 && fscanf(f1, "%[^\n]\n%[^\n]\n", &transDB[i], &meaningDB[i]) == 2) {
        (*count)++;
        i++;
    }
    fclose(f);
    fclose(f1);
}

void add() {
    char word[100];
    char meaning[1000];
    fpurge(stdin);
    gets(word);
    strlwr(word);
    fpurge(stdin);
    gets(meaning);
    saveIndex(word);
    saveMeaning(word, meaning);
}

void saveIndex(char word[]) {
    char postfix[] = "_index.dat";
    char fileName[10] = "";
    strncpy(fileName, word, 1);
    strcat(fileName, postfix);
    FILE* f = fopen(fileName, "a");
    fprintf(f, "%s\n", word);
    fclose(f);
}

void saveMeaning(char word[], char meaning[]) {
    char fileName[10] = "";
    char postfix[] = "_meaning.dat";
    strncpy(fileName, word, 1);
    strcat(fileName, postfix);
    strlwr(word);
    FILE* f = fopen(fileName, "a");
    fprintf(f, "%s\n%s\n", word, meaning);
    fclose(f);
}
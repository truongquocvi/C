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
void search(char word[]);
void importDB(char fileIndex[], char fileMeaning[], char wordDB[][10], char meaningDB[][100], int *count);
int main(int argc, char** argv) {
    char word[10];
    printf("Search: ");
    gets(word);
    printf("Meaning: ");
    search(word);
    return (EXIT_SUCCESS);
}

void search(char word[]) {
    char fileIndex[10] = "";
    char fileMeaning[10] = "";
    char postfix[] = "_index.dat";
    strncpy(fileIndex, word, 1);
    strcat(fileIndex, "_index.dat");
    strlwr(fileIndex);
    strncpy(fileMeaning, word, 1);
    strcat(fileMeaning, "_meaning.dat");
    strlwr(fileMeaning);
    char wordDB[1000][10];
    char meaningDB[1000][100];
    int count;
    importDB(fileIndex, fileMeaning, wordDB, meaningDB, &count);
    for (int i = 0; i < count; i++) {
        if (strcmp(word, wordDB[i]) == 0)
            puts(meaningDB[i]);
    }
}

void importDB(char fileIndex[], char fileMeaning[], char wordDB[][10], char meaningDB[][100], int *count) {
    FILE* f = fopen(fileIndex, "r");
    FILE* f1 = fopen(fileMeaning, "r");
    char tmp[1000] = "";
    *count = 0;
    int i = 0;
    while (fscanf(f, "%s\n", &wordDB[0]) == 1 && fscanf(f1, "%s\n%[^\n]\n", tmp, &meaningDB[0]) == 2) {
        (*count)++;
        i++;
    }
    fclose(f);
    fclose(f1);
}

void add() {
    char word[10];
    char meaning[1000];
    fpurge(stdin);
    gets(word);
    fpurge(stdin);
    gets(meaning);
    saveIndex(word);
    saveMeaning(word, meaning);
}

void saveIndex(char word[]) {
    char postfix[] = "_index.dat";
    char index[10] = "";
    char fileName[10] = "";
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] == ' ')
            break;
        index[i] = word[i];
    }
    strncpy(fileName, index, 1);
    strcat(fileName, postfix);
    strlwr(fileName);
    FILE* f = fopen(fileName, "a");
    fprintf(f, "%s\n", index);
    fclose(f);
}

void saveMeaning(char word[], char meaning[]) {
    char fileName[10] = "";
    char index[10] = "";
    char postfix[] = "_meaning.dat";
    strncpy(fileName, word, 1);
    strcat(fileName, postfix);
    strlwr(fileName);
    FILE* f = fopen(fileName, "a");
    fprintf(f, "%s\n%s\n", word, meaning);
    fclose(f);
}
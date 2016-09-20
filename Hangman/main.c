/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Truong Quoc Vi
 *
 * Created on September 20, 2016, 9:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/*
 * 
 */
char inputChar(char dup[]);
void playGame(char hangman[], int solved[], int length);
void openFile(char hangman[]);
int main(int argc, char** argv) {
    char hangman[100];
    int countLetter;
    openFile(hangman);
    strupr(hangman);
    puts(hangman);
    int length = strlen(hangman);
    int solved[length];
    for (int i = 0; i < length; i++)
        if (hangman[i] != ' ')
            countLetter++;
    printf("This game has %d letters\n", countLetter);
    for (int i = 0; i < strlen(hangman); i++)
        solved[i] = 0;
    playGame(hangman, solved, length);
    return (EXIT_SUCCESS);
}

void openFile(char hangman[]) {
    FILE* f = fopen("hangman.txt", "r");
    fgets(hangman, 1000, f);
    fclose(f);
}

char inputChar(char dup[]) {
    char c, tmp;
    int check = 0;
    do {
        fpurge(stdin);
        if (scanf("%c%c", &c, &tmp) == 2 && (toupper(c) >= 65 && toupper(c) <= 90)&& tmp == '\n') {
            if (dup[toupper(c) - 65] == 1) {
                printf("You have guessed this letter already. ");
                check = 0;
            }
            else {
                dup[toupper(c) - 65] = 1;
                check = 1;
            }
        }
        if (!check)
            printf("Input again: ");
    } while(!check);
    return toupper(c);
}

void playGame(char hangman[], int solved[], int length) {
    int check = 0, count = 1, countLetter;
    char c = ' ', dup[29];
    for (int i = 0; i < 29; i++)
        dup[i] = 0;
    do {
        countLetter = 0;
        for (int i = 0; i < strlen(hangman); i++) {
            if (hangman[i] == c) {
                solved[i] = 1;
                check++;
            }
            if (solved[i] == 1 || hangman[i] == ' ')
                printf("%c ", hangman[i]);
            else
                printf("_ ");
        }
        if(check == length) {
            printf("\nYou win this game\n");
            break;
        }
        printf("\nEnter your letter #%d time: ", count);
        c = inputChar(dup);
        for (int i = 0; i < strlen(hangman); i++)
            if (hangman[i] == c)
                countLetter++;
        printf("There are (is) %d letter %c\n", countLetter, c);
        count++;
    } while (1);
}
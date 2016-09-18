/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Truong Quoc Vi
 *
 * Created on September 17, 2016, 11:39 AM
 */

#include <stdio.h>
#include <stdlib.h>
/*
 * 
 */
void generateNumbers(int out[]);
void inputNumbers(int in[]);
void checkNumbers(int in[], int out[], int *countPerfect, int *countMatch);

int main(int argc, char** argv) {
    int out[4], in[4], countPerfect, countMatch;
    generateNumbers(out);
    for (int i = 0; i < 4; i++)
        printf("%d ", out[i]);
    printf("\n");
    do {
        inputNumbers(in);
        checkNumbers(in, out, &countPerfect, &countMatch);
        printf("You entered %d perfect numbers and %d imperfect numbers\n", countPerfect, countMatch - countPerfect);
    } while (countPerfect < 4);
    return (EXIT_SUCCESS);
}

void generateNumbers(int out[]) {
    srand(time(NULL));
    for (int i = 0; i < 4; i++)
        out[i] = rand() % 9;
}

void inputNumbers(int in[]) {
    printf("Input numbers: ");
    scanf("%d%d%d%d", &in[0], &in[1], &in[2], &in[3]);
}

void checkNumbers(int in[], int out[], int *countPerfect, int *countMatch) {
    int a[10], b[10];
    *countPerfect = 0;
    *countMatch = 0;
    for (int i = 0; i < 10; i++) {
        a[i] = 0;
        b[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        (a[in[i]])++;
        (b[out[i]])++;
        if (in[i] == out[i])
            (*countPerfect)++;
    }
    for (int i = 0; i < 10; i++) {
        if (a[i] <= b[i])
            (*countMatch) += a[i];
        else
            (*countMatch) += b[i];
    }
}
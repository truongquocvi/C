/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Truong Quoc Vi
 *
 * Created on September 16, 2016, 7:48 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
 * 
 */
void import(char id[][14], char pin[][6], char name[][30], int balances[], int* count);
void chooseMenu1(char id[][14], char pin[][6], char name[][30], int balances[], int* count);
void chooseMenu2(char id[][14], char pin[][6], char name[][30], int balances[], int* count, int position);
void login(char id[][14], char pin[][6], char name[][30], int balances[], int* count);
int verify(char id[][14], char pin[][6], int* count, char user[], char pass[]);
void reg(char id[][14], char pin[][6], char name[][30], int balances[], int* count);
void withdraw(char id[][14], int balances[], int position);
int search(char id[][14], char searchID[], int *count);
void transfer(char id[][14], char name[][30], int balances[], int position, int *count);
void saveFile(char id[][14], char pin[][6], char name[][30], int balances[], int* count);
void saveWithdraw(char id[], int n);
void saveTransfer(char id[], char rcvr[], int n);

int main(int argc, char* argv) {
    int count;
    char id[1000][14];
    char pin[1000][6];
    char name[1000][30];
    int balances[1000];
    import(id, pin, name, balances, &count);
    chooseMenu1(id, pin, name, balances, &count);
    saveFile(id, pin, name, balances, &count);
    printf("committed");
    return (EXIT_SUCCESS);
}

void import(char id[][14], char pin[][6], char name[][30], int balances[], int* count) {
    int i = 0;
    char tmp[1000][100];
    FILE *f = fopen("accounts.db", "r");
    while(fscanf(f, "ID: %[^\n]\nPIN: %[^\n]\nName: %[^\n]\nBalances: %d\n\n", id[i], pin[i], name[i], &balances[i]) == 4) {
        printf("User #%d\nID: %s\nPIN: %s\nName: %s\nBalances: %d\n", i + 1, id[i], pin[i], name[i], balances[i]);
        i++;
    }
    *count = i;
    fclose(f);
}

void saveFile(char id[][14], char pin[][6], char name[][30], int balances[], int* count) {
    FILE *f = fopen("accounts.db", "w");
    for (int i = 0; i < *count; i++) {
        fprintf(f, "ID: %s\n", id[i]);
        fprintf(f, "PIN: %s\n", pin[i]);
        fprintf(f, "Name: %s\n", name[i]);
        fprintf(f, "Balances: %d\n\n", balances[i]);
    }
    fclose(f);
}

void saveWithdraw(char id[], int n) {
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    FILE *f = fopen("withdraw.db", "a");
    fprintf(f, "%s", asctime (timeinfo));
    fprintf(f, "ID: %s\n", id);
    fprintf(f, "Amounts: %d\n\n", n);
    fclose(f);
}

void saveTransfer(char id[], char rcvr[], int n) {
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    FILE *f = fopen("transfer.db", "a");
    fprintf(f, "%s", asctime (timeinfo));
    fprintf(f, "Sender: %s\n", id);
    fprintf(f, "Receiver: %s\n", id);
    fprintf(f, "Amounts: %d\n\n", n);
    fclose(f);
}

void chooseMenu1(char id[][14], char pin[][6], char name[][30], int balances[], int* count) {
    int choice;
    do {
        saveFile(id, pin, name, balances, count);
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                login(id, pin, name, balances, count);
                break;
            case 2:
                reg(id, pin, name, balances, count);
                break;
            case 3:
                printf("See you later\n");
                break;
            default:
                printf("Invalid number\n");
                break;
        }
    } while (choice != 3);
}

void chooseMenu2(char id[][14], char pin[][6], char name[][30], int balances[], int* count, int position) {
    int choice;
    printf("Welcome %s\n", name[position]);
    do {
        printf("You have %d in your account\n", balances[position]);
        saveFile(id, pin, name, balances, count);
        printf("1. Withdraw\n");
        printf("2. Transfer\n");
        printf("3. Logout\n");
        printf("Choose: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                withdraw(id, balances, position);
                break;
            case 2:
                transfer(id, name, balances, position, count);
                break;
            case 3:
                chooseMenu1(id, pin, name, balances, count);
                break;
            default:
                printf("Invalid number\n");
                break;
        }
    } while (choice != 3);
}

void login(char id[][14], char pin[][6], char name[][30], int balances[], int* count) {
    char user[14], pass[6];
    printf("Account ID: ");
    fpurge(stdin);
    gets(user);
    printf("PIN code: ");
    fpurge(stdin);
    gets(pass);
    int check = verify(id, pin, count, user, pass);
    if (check == -1) {
        printf("Login failed\n");
        chooseMenu1(id, pin, name, balances, count);
    }
    else {
        printf("Login successfully\n");
        chooseMenu2(id, pin, name, balances, count, check);
    }
}

int verify(char id[][14], char pin[][6], int* count, char user[], char pass[]) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(id[i], user) == 0 && strcmp(pin[i], pass) == 0)
            return i;
    }
    return -1;
}

void reg(char id[][14], char pin[][6], char name[][30], int balances[], int* count) {
    int i = *count;
    fpurge(stdin);
    printf("Input ID %d: ", i + 1);
    fpurge(stdin);
    scanf("%s", &id[i]);
    printf("Input PIN %d: ", i + 1);
    fpurge(stdin);
    scanf("%s", &pin[i]);
    printf("Input name %d: ", i + 1);
    fpurge(stdin);
    gets(name[i]);
    printf("Input balances %d: ", i + 1);
    scanf("%d", &balances[i]);
    (*count)++;
}

void withdraw(char id[][14], int balances[], int position) {
    int n;
    do {
        printf("How much do you want to withdraw: ");
        scanf("%d", &n);
        if (n > balances[position])
            printf("You do not have enough money\n");
        else {
            balances[position] -= n;
            printf("Withdraw successfully\n");
    saveWithdraw(id[position], n);
        }
    } while (n > balances[position]);
}

int search(char id[][14], char searchID[], int *count) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(id[i], searchID) == 0 )
            return i;
    }
    return -1;
}

void transfer(char id[][14], char name[][30], int balances[], int position, int *count) {
    char s[14];
    int rcvrPos;
    int n;
    char q;
    printf("Please enter account ID you want to transfer: ");
    fpurge(stdin);
    gets(s);
    rcvrPos = search(id, s, count);
    if (rcvrPos == -1)
        printf("Wrong account ID, please try again\n");
    else {
        printf("How much do you want to transfer: ");
        scanf("%d", &n);
        if (n > balances[position])
            printf("You do not have enough money\n");
        else {
            printf("You want to transfer %d to %s? ", n, name[rcvrPos]);
            fpurge(stdin);
            scanf("%c", &q);
            if (q == 'y') {
                balances[position] -= n;
                balances[rcvrPos] += n;
                printf("Transfer successfully\n");
                saveTransfer(id[position], id[rcvrPos], n);
            }
        }
    }
}
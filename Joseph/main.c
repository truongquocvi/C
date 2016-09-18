/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Truong Quoc Vi
 *
 * Created on September 15, 2016, 11:18 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int n, k, tmp;
    printf("n = ");
    scanf("%d", &n);
    printf("k = ");
    scanf("%d", &k);
    int a[n + 1], b[k];
    for (int i = 1; i <= n; i++)
        a[i] = i;
    while (n >= k) {
//        printf("\n");
//        for (int i = 1; i <= n; i++)
//            printf("%d ", a[i]);
        for (int i = 1; i <= n; i++)
            if (i % k == 0)
                a[i] = -1;
        tmp = n % k;
        for (int i = 0; i < tmp; i++)
            b[tmp - i] = a[n - i];
        for (int i = n - tmp; i > 0; i--)
            a[i + tmp] = a[i];
        for (int i = 1; i <= tmp; i++)
            a[i] = b[i];
        for (int i = 1; i < n; i++)
            if (a[i] == -1) {
                for (int j = i; j < n; j++)
                    a[j] = a[j + 1];
                i--;
                n--;
            }
        if (a[n] == -1)
            n--;
    }
    printf("\n");
    for (int i = 1; i < k; i++)
        printf("%d ", a[i]);
    return (EXIT_SUCCESS);
}


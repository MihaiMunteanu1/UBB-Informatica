#include <stdio.h>
#include <stdbool.h>

/*
 *Functie care calculeaza x la puterea n
 * x float
 * n int, natural >=0
 * pre: x float, n int numar natural
 * post: returneaza x^n numar float
 */
float power(float x, int n) {
    float result = 1.0;
    while (n > 0) {
        if (n % 2 == 1)
            result = result * x;
        x *= x;
        n = n / 2;
    }
    return result;
}

/*
 * Functie care verifica daca n este numar par si strict mai mare ca 2
 * n -> intreg
 * pre: n int
 * post: retrun 1 daca verifica conditia, 0 altfel
 */
int verifica_n_par_mai_mare_2(int n) {
    if (n % 2 == 1)
        return 0;
    if (n <= 2)
        return 0;
    return 1;
}

/*
 * Functie care verifica daca un numar e prim
 * n int
 * pre: n intreg
 * post: return 1 daca e prim, 0 altfel
 */
int prim(int n) {
    if (n < 2)
        return 0;
    for (int d = 2; d <= n / 2; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

/*
 * Functie care descompune un numar par si mai mare ca 2 in suma de 2 numere prime
 * n int
 * pre: n numar par mai mare ca 2
 * post: afiseaza descompunerea sa in suma de 2 numere prime
 */
void descompune(int n) {
    for (int i = 2; i <= n / 2; i++)
        if (prim(i) == 1 && prim(n - i) == 1)
            printf("%d + %d = %d\n", i, n - i, n);
}

/*
 * Functie care verifica daca n e natural
 * pre: n int
 * post: return 1 daca n este natural, 0 altfel
 */
int verifica_n_natural(int n) {
    if (n < 0)
        return 0;
    return 1;
}

/*
 * Functie care afiseaza meniul
 */
void afis() {
    printf("1. Ridica la putere (ex 12)\n");
    printf("2. Descompune numar (ex 14)\n");
    printf("3. Exit\n");
}

int main() {
    while (true) {
        afis();
        int optiune;
        printf(">>");
        scanf("%d", &optiune);
        if (optiune == 1) {
            float x;
            int n;
            printf("da-ti nr real x: ");
            scanf("%f", &x);
            printf("da-ti nr natural n: ");
            scanf("%d", &n);
            if (verifica_n_natural(n) == 1) {
                float result = power(x, n);
                printf("%.2f ^ %d = %.2f\n", x, n, result);
            } else printf("n nu e natural\n");
        } else if (optiune == 2) {
            int n;
            printf("citeste n: ");
            scanf("%d", &n);
            if (verifica_n_par_mai_mare_2(n) == 1)
                descompune(n);
            else printf("n invalid\n");
        } else if (optiune == 3)
            return 0;
        else printf("Optiune invalida\n");
    }
}
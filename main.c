/* OS_T1_V11: Kvadrat tenglama ax^2 + bx + c = 0
 * 1-masala: C asoslari (natija to'g'ridan-to'g'ri funksiyada chiqariladi)
 * 2-masala: pointerlar (ildizlar pointer orqali qaytariladi)
 * Kompilyatsiya: gcc -Wall -Wextra main.c -o main -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPS 1e-12

/* Xavfsiz o'qish: fgets + strtod. Son bo'lmasa 0 qaytaradi. */
int oqi_son(const char *taklif, double *natija) {
    char buf[100], *oxir;
    printf("%s", taklif);
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 0;
    buf[strcspn(buf, "\n")] = '\0';
    if (buf[0] == '\0') return 0;
    *natija = strtod(buf, &oxir);
    if (*oxir != '\0') return 0;      /* harf yoki ortiqcha belgi bor */
    if (!isfinite(*natija)) return 0; /* inf / nan */
    return 1;
}

/* ---------- 1-MASALA: C asoslari ---------- */
void yech_oddiy(double a, double b, double c) {
    if (fabs(a) < EPS) {                       /* chiziqli tenglama */
        if (fabs(b) < EPS) {
            if (fabs(c) < EPS) printf("Cheksiz ko'p ildiz bor.\n");
            else printf("Ildiz yo'q.\n");
        } else {
            printf("Chiziqli tenglama: x = %.4f\n", -c / b);
        }
        return;
    }
    double d = b * b - 4 * a * c;
    if (d > EPS) {
        printf("Ikkita haqiqiy ildiz: x1 = %.4f, x2 = %.4f\n",
               (-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a));
    } else if (fabs(d) <= EPS) {
        printf("Bitta ildiz: x = %.4f\n", -b / (2 * a));
    } else {
        printf("Kompleks ildizlar: %.4f + %.4fi va %.4f - %.4fi\n",
               -b / (2 * a), sqrt(-d) / fabs(2 * a),
               -b / (2 * a), sqrt(-d) / fabs(2 * a));
    }
}

/* ---------- 2-MASALA: pointerlar ----------
 * Qaytish: 2 yoki 1 - haqiqiy ildizlar soni; 0 - ildiz yo'q;
 * -1 - cheksiz ko'p; -2 - kompleks (*x1 haqiqiy, *x2 mavhum qism)
 */
int ildizlar(double a, double b, double c, double *x1, double *x2) {
    if (fabs(a) < EPS) {
        if (fabs(b) < EPS) return (fabs(c) < EPS) ? -1 : 0;
        *x1 = *x2 = -c / b;
        return 1;
    }
    double d = b * b - 4 * a * c;
    if (d > EPS) {
        *x1 = (-b + sqrt(d)) / (2 * a);
        *x2 = (-b - sqrt(d)) / (2 * a);
        return 2;
    }
    if (fabs(d) <= EPS) {
        *x1 = *x2 = -b / (2 * a);
        return 1;
    }
    *x1 = -b / (2 * a);
    *x2 = sqrt(-d) / fabs(2 * a);
    return -2;
}

int main(void) {
    double a, b, c;
    printf("ax^2 + bx + c = 0 tenglamani yechish\n");
    if (!oqi_son("a = ", &a) || !oqi_son("b = ", &b) || !oqi_son("c = ", &c)) {
        printf("Xato: koeffitsiyent son bo'lishi kerak!\n");
        return 1;
    }

    printf("\n--- 1-masala (oddiy usul) ---\n");
    yech_oddiy(a, b, c);

    printf("\n--- 2-masala (pointerlar) ---\n");
    double x1 = 0, x2 = 0;
    int k = ildizlar(a, b, c, &x1, &x2);
    switch (k) {
        case 2:  printf("Ikki haqiqiy ildiz: x1 = %.4f, x2 = %.4f\n", x1, x2); break;
        case 1:  printf("Bitta ildiz: x = %.4f\n", x1); break;
        case 0:  printf("Ildiz yo'q.\n"); break;
        case -1: printf("Cheksiz ko'p ildiz.\n"); break;
        case -2: printf("Kompleks ildizlar: %.4f + %.4fi va %.4f - %.4fi\n", x1, x2, x1, x2); break;
    }
    /* Manzillarni chiqarish */
    printf("\nx1 manzili: %p (qiymati %.4f)\n", (void *)&x1, x1);
    printf("x2 manzili: %p (qiymati %.4f)\n", (void *)&x2, x2);
    return 0;
}

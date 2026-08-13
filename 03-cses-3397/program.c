#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void get_p(uint64_t n, uint64_t k, uint64_t *p) {
    uint64_t *numbers = malloc(n * sizeof(uint64_t));
    for (uint64_t i = 0; i < n; i++) {
        numbers[i] = i + 1;
    }
    uint64_t count = n;

    uint64_t factorial = 1;
    uint64_t factor = n - 1;
    for (uint64_t i = 1; i <= n - 1; i++) {
        factorial *= i;
    }

    k--;

    for (uint64_t i = 0; i < n - 1; i++) {
        uint64_t k_i = k / factorial;
        p[i] = numbers[k_i];

        for (uint64_t j = k_i; j < count - 1; j++) {
            numbers[j] = numbers[j + 1];
        }
        count--;

        k = k % factorial;
        factorial /= factor;
        factor--;
    }

    p[n - 1] = numbers[0];
    free(numbers);
}

uint64_t get_k(uint64_t n, uint64_t *p) {
    uint64_t *numbers = malloc(n * sizeof(uint64_t));
    for (uint64_t i = 0; i < n; i++) {
        numbers[i] = i + 1;
    }
    uint64_t count = n;

    uint64_t factorial = 1;
    uint64_t factor = n - 1;
    for (uint64_t i = 1; i <= n - 1; i++) {
        factorial *= i;
    }

    uint64_t k = 1;

    for (uint64_t i = 0; i < n - 1; i++) {
        uint64_t idx = 0;
        for (uint64_t j = 0; j < count; j++) {
            if (numbers[j] == p[i]) {
                idx = j;
                break;
            }
        }

        k += idx * factorial;

        for (uint64_t j = idx; j < count - 1; j++) {
            numbers[j] = numbers[j + 1];
        }
        count--;

        factorial /= factor;
        factor--;
    }

    free(numbers);
    return k;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        int type;
        uint64_t n;
        scanf("%d %llu", &type, (unsigned long long *)&n);

        if (type == 1) {
            uint64_t k;
            scanf("%llu", (unsigned long long *)&k);

            uint64_t *p = malloc(n * sizeof(uint64_t));
            get_p(n, k, p);

            for (uint64_t i = 0; i < n; i++) {
                if (i > 0) {
                    printf(" ");
                }
                printf("%llu", (unsigned long long)p[i]);
            }
            printf("\n");
            free(p);
        } else if (type == 2) {
            uint64_t *p = malloc(n * sizeof(uint64_t));
            for (uint64_t i = 0; i < n; i++) {
                scanf("%llu", (unsigned long long *)&p[i]);
            }

            printf("%llu\n", (unsigned long long)get_k(n, p));
            free(p);
        }
    }

    return 0;
}
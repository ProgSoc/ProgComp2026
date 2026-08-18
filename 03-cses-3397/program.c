#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void get_p(uint64_t n, uint64_t k, uint64_t *p) {
    // holds teh values not placed in to the permutation in ascending order
    // as each answer digit gets picked it gets removed from the list
    uint64_t *numbers = malloc(n * sizeof(uint64_t));
    for (uint64_t i = 0; i < n; i++) {
        numbers[i] = i + 1;
    }
    uint64_t count = n;

    // factorial starts at (n-1)! since with n numbers remaining 
    // fixing the first one leaves (n-1)! ways to arrage the rest of the numbers
    uint64_t factorial = 1;
    uint64_t factor = n - 1;
    for (uint64_t i = 1; i <= n - 1; i++) {
        factorial *= i;
    }
    // convert k from 1-indexed to 0-indexed as it is easier to solve as a 0 based rank
    k--;
    
    // building the permutation one position at a times
    for (uint64_t i = 0; i < n - 1; i++) {
        //k_i is the index of the value that belongs at that position
        // as there are factorail ways to arrange the rest after fixing it diving the 
        // k value by the block size will give us how many whole blocks we have skipped past
        uint64_t k_i = k / factorial;
        p[i] = numbers[k_i];

        // remove numbers [k_i] from the pool by shifting everything to the left by one
        for (uint64_t j = k_i; j < count - 1; j++) {
            numbers[j] = numbers[j + 1];
        }
        count--;
        // k is now the rank remaining among the permutations of what is left
        k = k % factorial;
        // shrinking the factorial to match 
        // factorialgoes from (m-1)! to (m-2)! as the block size divides down by factors
        factorial /= factor;
        factor--;
    }
    // only one number is left after n-1 picks so it goes last
    p[n - 1] = numbers[0];
    free(numbers);
}

// computes k such that p(n,k) equals the given permutation p
// gets us the inverse of get_p
uint64_t get_k(uint64_t n, uint64_t *p) {
    uint64_t *numbers = malloc(n * sizeof(uint64_t));
    // tracks values that have not been used yet
    for (uint64_t i = 0; i < n; i++) {
        numbers[i] = i + 1;
    }
    uint64_t count = n;

    uint64_t factorial = 1;
    uint64_t factor = n - 1;
    for (uint64_t i = 1; i <= n - 1; i++) {
        factorial *= i;
    }
    // starting at k =1 sine the final answer is 1 indexed
    uint64_t k = 1;

    for (uint64_t i = 0; i < n - 1; i++) {
        uint64_t idx = 0;
        for (uint64_t j = 0; j < count; j++) {
            // find where p[i] is and this tells us how many canditates we skipped 
            // to reach this value
            if (numbers[j] == p[i]) {
                idx = j;
                break;
            }
        }
        // each skipped candidate accounts for a full block of factorial permutations
        k += idx * factorial;
        //remove p[i] from the remaining pool
        for (uint64_t j = idx; j < count - 1; j++) {
            numbers[j] = numbers[j + 1];
        }
        count--;
        //Shrink the factorial to match the smaller remaining problem.
        factorial /= factor;
        factor--;
    }

    free(numbers);
    return k;
}

int main(void) {
    int t;
    scanf("%d", &t);
    // process each sub question independently 
    while (t--) {
        int type;
        uint64_t n;
        scanf("%d %llu", &type, (unsigned long long *)&n);

        if (type == 1) {
            // type 1: given n and k, output the permutation p(n, k)
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
            // type 2: given n and the permutation itself, output its rank k
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
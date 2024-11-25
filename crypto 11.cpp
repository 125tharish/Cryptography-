#include <stdio.h>
#include <math.h>
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
int main() {
    unsigned long long total_permutations = factorial(25);
    unsigned long long symmetry_factor = factorial(5) * factorial(5) * 8;
    unsigned long long unique_keys = total_permutations / symmetry_factor;
    double log2_total = log2((double)total_permutations);
    double log2_unique = log2((double)unique_keys);
    printf("Total keys (ignoring duplicates): 2^%.2f\n", log2_total);
    printf("Effectively unique keys: 2^%.2f\n", log2_unique);
    return 0;
}

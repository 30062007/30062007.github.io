#include <stdio.h>
#include <math.h>
long long aliquot_sum(long long n) {
    if (n <= 1) return 0;
    long long sum = 1;  // 1 είναι πάντα διαιρέτης
    long long sqrt_n = sqrt(n);

    for (long long i = 2; i <= sqrt_n; i++) {
        if (n % i == 0) {
            long long j = n / i;
            if (i != j) {
                sum += i + j; // διαφορετικοί διαιρέτες
            } else {
                sum += i; // τέλειο τετράγωνο, προσθέτουμε μόνο μία φορά
            }
        }
    }

    return sum;
}

int main(void) {
    long long n;
    int maxl;
    char tos;
    int step = 0;

    printf("Please give the number to start the aliquot sequence from: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    printf("Provide the max aliquot length to look for (0 for unlimited): ");
    if (scanf("%d", &maxl) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    printf("Do you want to print the full sequence ('f') or just the length ('l')? ");
    if (scanf(" %c", &tos) != 1 || (tos != 'f' && tos != 'l')) {
        fprintf(stderr, "Invalid output mode. Use 'f' or 'l'.\n");
        return 1;
    }

    const long long LIMIT = 1000000000000000LL;
    if (n > LIMIT) {
        fprintf(stderr, "Number exceeds maximum supported integer (1000000000000000). Stopping.\n");
        return 1;
    }

    if (tos == 'f')
        printf("%lld\n", n);
    while ((maxl == 0 ? 1 : (step < maxl))) {
        long long sum = aliquot_sum(n);

        if (sum > LIMIT) {
            fprintf(stderr, "Number exceeds maximum supported integer (1000000000000000). Stopping.\n");
            return 1;
        }

        n = sum;
        step++;

        if (tos == 'f')
            printf("%lld\n", n);

        if (n == 0)
            break;
    }

    if (tos == 'l')
        printf("Length of aliquot sequence: %d\n", step);

    return 0;
}

#include "main.h"

int main() {
    int n = 3;
    Vector v1 = {n, (double[]){9, 8, 9}};
    Vector v2 = {n, (double[]){5, 6, 7}};
    Vector v3 = {n, (double[]){7, 8, 9}};

    Vector **longest_vectors = NULL;
    int num_longest;

    if (find_longest_vectors(norm_inf_wrapper, NULL, n, &longest_vectors, &num_longest, &v1, &v2, &v3) != OK) {
        return INVALID_MEMORY;
    }
    printf("Longest vectors for norm 00:\n");
    for (int i = 0; i < num_longest; i++) {
        Vector *v = longest_vectors[i];
        printf("Vector: ");
        for (int j = 0; j < v->n; j++) {
            printf("%.2f ", v->coords[j]);
        }
        printf("\n");
    }
    free(longest_vectors);
    longest_vectors = NULL;

    double p = 2;
    if (find_longest_vectors(norm_p_wrapper, &p, n, &longest_vectors, &num_longest, &v1, &v2, &v3) != OK) {
        return INVALID_MEMORY;
    }
    printf("Longest vectors for norm p (p=%.2f):\n", p);
    for (int i = 0; i < num_longest; i++) {
        Vector *v = longest_vectors[i];
        printf("Vector: ");
        for (int j = 0; j < v->n; j++) {
            printf("%.2f ", v->coords[j]);
        }
        printf("\n");
    }
    free(longest_vectors);
    longest_vectors = NULL;

    double A[] = {
        1, 5, 0,
        0, 5, 0,
        0, 5, 1
    };
    if (find_longest_vectors(norm_A_wrapper, A, n, &longest_vectors, &num_longest, &v1, &v2, &v3) != OK) {
        return INVALID_MEMORY;
    }
    printf("Longest vectors for norm A:\n");
    for (int i = 0; i < num_longest; i++) {
        Vector *v = longest_vectors[i];
        printf("Vector: ");
        for (int j = 0; j < v->n; j++) {
            printf("%.2f ", v->coords[j]);
        }
        printf("\n");
    }
    free(longest_vectors);
    longest_vectors = NULL;

    return 0;
}

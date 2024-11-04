#include "main.h"

int main() {
    int n = 3;
    Vector vectors[] = {
        {n, (double[]){9, 8, 9}},
        {n, (double[]){4, 10, 6}},
        {n, (double[]){7, 9, 9}}
    };
    int num_vectors = sizeof(vectors) / sizeof(vectors[0]);

    Vector *longest_vectors[num_vectors];
    int num_longest;

    find_longest_vectors(n, vectors, num_vectors, (double (*)(Vector *, void *))norm_inf_wrapper, NULL, longest_vectors, &num_longest);
    printf("Longest vectors for norm ∞:\n");
    for (int i = 0; i < num_longest; i++) {
        Vector *v = longest_vectors[i];
        printf("Vector: ");
        for (int j = 0; j < v->n; j++) {
            printf("%.2f ", v->coords[j]);
        }
        printf("\n");
    }

    double p = 4;
    find_longest_vectors(n, vectors, num_vectors, (double (*)(Vector *, void *))norm_p_wrapper, &p, longest_vectors, &num_longest);
    printf("Longest vectors for norm p (p=8):\n");
    for (int i = 0; i < num_longest; i++) {
        Vector *v = longest_vectors[i];
        printf("Vector: ");
        for (int j = 0; j < v->n; j++) {
            printf("%.2f ", v->coords[j]);
        }
        printf("\n");
    }

    double A[] = {
        1, 5, 2,
        1, 8, 0,
        3, 9, 1
    };
    find_longest_vectors(n, vectors, num_vectors, (double (*)(Vector *, void *))norm_A_wrapper, A, longest_vectors, &num_longest);
    printf("Longest vectors for norm A:\n");
    for (int i = 0; i < num_longest; i++) {
        Vector *v = longest_vectors[i];
        printf("Vector: ");
        for (int j = 0; j < v->n; j++) {
            printf("%.2f ", v->coords[j]);
        }
        printf("\n");
    }

    return 0;
}
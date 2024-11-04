#include "main.h"

double norm_inf(Vector *v) {
    double max = 0;
    for (int i = 0; i < v->n; i++) {
        if (fabs(v->coords[i]) > max) {
            max = fabs(v->coords[i]);
        }
    }
    return max;
}

double norm_p(Vector *v, double p) {
    double sum = 0, pow_val = 0;
    for (int i = 0; i < v->n; i++) {
        pow_val = pow(fabs(v->coords[i]), p);
        if (sum > DBL_MAX - pow_val)
            return -1.0;
        sum += pow_val;
    }
    return pow(sum, 1.0 / p);
}


double norm_A(Vector *v, double *A, int n) {
    double *x = v->coords;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sum > DBL_MAX - A[i * n + j] * x[i] * x[j])
                return -1.0;
            sum += A[i * n + j] * x[i] * x[j];
        }
    }
    return sqrt(sum);
}

double norm_inf_wrapper(Vector *v, void *param) {
    (void)param;
    return norm_inf(v);
}

double norm_p_wrapper(Vector *v, void *param) {
    double p = *(double *)param;
    return norm_p(v, p);
}

double norm_A_wrapper(Vector *v, void *param) {
    double *A = (double *)param;
    return norm_A(v, A, v->n);
}


enum Errors find_longest_vectors(int n, Vector *vectors, int num_vectors, double (*norm_func)(Vector *, void *), void *norm_param, Vector **longest_vectors, int *num_longest) {
    if (n <= 0 || vectors == NULL || num_vectors <= 0 || norm_func == NULL || longest_vectors == NULL || num_longest == NULL) {
        return INVALID_INPUT;
    }
    double max_norm = 0, norm = 0;
    *num_longest = 0;

    for (int i = 0; i < num_vectors; i++) {
        norm = norm_func(&vectors[i], norm_param);
        if (norm > max_norm) {
            max_norm = norm;
            *num_longest = 1;
            longest_vectors[0] = &vectors[i];
        } else if (norm == max_norm) {
            longest_vectors[(*num_longest)++] = &vectors[i];
        }
    }
    return OK;
}
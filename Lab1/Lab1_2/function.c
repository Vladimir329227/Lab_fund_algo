#include "main.h"

enum Errors convert_str_to_double(const char *str, double * result)
{
    char *endptr;
    *result = strtod(str, &endptr);
    if (errno == ERANGE && (*result == HUGE_VAL || *result == -HUGE_VAL))
    {
        return INVALID_INPUT;
    } else if (errno == ERANGE && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }
    return OK;
}

enum Errors find_e_by_limit(double eps, double* rez){
    double n = 1, cur = 0, prev = 0;
    do
    {
        prev = cur;
        n++;
        cur = pow(1.0+1.0/n, n);
    } while (fabs(cur - prev) >= eps);
    *rez = cur;
    return OK;
}

enum Errors find_pi_by_limit(double eps, double* rez){
    double n = 1, cur = 0, prev = 0;
    do
    {
        prev = cur;
        n++;
        cur = pow(2,n*4)/n;
        for (int i = 1; i <= n; i++)
            cur *= pow(i,2)/pow(i+n,2);
    } while (fabs(cur - prev) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = cur;
    return OK;
}

enum Errors find_ln_2_by_limit(double eps, double* rez){
    double n = 1, cur = 0, prev = 0;
    do
    {
        prev = cur;
        n++;
        cur = n*(pow(2,1/n)-1);
    } while (fabs(cur - prev) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = cur;
    return OK;
}

enum Errors find_sqrt_2_by_limit(double eps, double* rez){
    double n = 1, cur = 0, prev = 0;
    do
    {
        prev = cur;
        if (n == 1) prev = -0.5;
        n++;
        cur = prev - pow(prev,2)/2 + 1;
        if (n >= pow(10, MAX_POW_TO_DALAY))
            return INVALID_INPUT;
    } while (fabs(cur - prev) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = cur;
    return OK;
}

enum Errors my_factorial(int nam, unsigned long long int* rez){
    if (nam < 0){
        *rez = 0;
        return OK;
    }
    *rez = 1;
    for (long long int i = 2; i <= nam; i++){
        if (ULLONG_MAX / i / (*rez) == 0)
            return INVALID_MEMORY;
        (*rez) *= i;
    }
        
    return OK;
}

enum Errors find_gamma_by_limit(double eps, double* rez){
    double n = 1, cur = 0, prev = 0;
    unsigned long long int rez_1, rez_2;
    do
    {
        prev = cur;
        n++;
        cur = 0;
        for (int i = 2; i <= n; i++)
        {
            if (my_factorial(i,&rez_1) != OK) 
                return INVALID_INPUT;
            if (my_factorial(n - i,&rez_2) != OK) 
                return INVALID_INPUT;
            cur += log(rez_1) * pow(-1,i) / i / rez_1 / rez_2;
        }
        if (my_factorial(n,&rez_1) != OK) 
                return INVALID_INPUT;
        cur *= rez_1;
    } while (fabs(cur - prev) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = cur;
    return OK;
}

enum Errors find_e_by_row(double eps, double* rez){
    double n = 1, cur = 0, prev = 0;
    double fact = 1;
    cur += 2;
    do
    {
        prev = cur;
        n++;
        fact *= n;
        cur += 1/fact;
    } while (fabs(cur - prev) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = cur;
    return OK;
}

enum Errors find_pi_by_row(double eps, double* rez){
    double n = 0, cur = 0, prev = 0;
    do
    {
        prev = cur;
        n++;
        cur += 4 * pow(-1,n - 1) / (2*n-1);
        if (n >= pow(10, MAX_POW_TO_DALAY))
            return INVALID_INPUT;
    } while (fabs(cur - prev) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = cur;
    return OK;
}

enum Errors find_ln_2_by_row(double eps, double* rez){
    double n = 0, cur = 0, prev = 0;
    do
    {
        prev = cur;
        n++;
        cur += pow(-1,n - 1) / n;
        if (n >= pow(10, MAX_POW_TO_DALAY))
            return INVALID_INPUT;
    } while (fabs(cur - prev) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = cur;
    return OK;
}

enum Errors find_sqrt_2_by_row(double eps, double* rez){
    double n = 1, cur = 1, prev = 0;
    do
    {
        prev = cur;
        n++;
        cur *= pow(2, pow(2,-n));
        if (n >= pow(10, MAX_POW_TO_DALAY))
            return INVALID_INPUT;
    } while (fabs(cur - prev) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = cur;
    return OK;
}

enum Errors find_gamma_by_row(double eps, double* rez){
    double n = 2, t = 0, cur = 0.5, prev = 0;
    do
    {
        prev = cur;
        n++;
        t = sqrt(n);
        if (fmod(t,1.0) == 0)
        {
            n++;
            t = sqrt(n);
        }
        cur += 1.0/pow((int)t,2.0)  - 1.0/n;
        if (n >= pow(10, MAX_POW_TO_DALAY))
            return INVALID_INPUT;
    } while (fabs(cur - prev) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = fabs(cur-pow(PI,2.0)/6);
    return OK;
}

enum Errors find_e_by_equations(double eps, double* rez){
    double n = 3, cur = 0, d_cur = 0;
    do
    {
        cur = log(n) - 1;       //метод приближений ньютона 
        d_cur = 1/n;
        n -= cur/d_cur;
        if (n >= pow(10, MAX_POW_TO_DALAY))
            return INVALID_INPUT;
    } while (fabs(cur) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = n;
    return OK;
}

enum Errors find_pi_by_equations(double eps, double* rez){
    double n = 3, cur = 0, d_cur = 0;
    do
    {
        cur = cos(n) + 1;       //метод приближений ньютона 
        d_cur = -sin(n);
        n -= cur/d_cur;
        if (n >= pow(10, MAX_POW_TO_DALAY))
            return INVALID_INPUT;
    } while (fabs(cur) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = n;
    return OK;
}

enum Errors find_ln_2_equations(double eps, double* rez){
    double n = 3, cur = 0, d_cur = 0;
    do
    {
        cur = pow(EKS, n) - 2;       //метод приближений ньютона 
        d_cur = pow(EKS, n);
        n -= cur/d_cur;
        if (n >= pow(10, MAX_POW_TO_DALAY))
            return INVALID_INPUT;
    } while (fabs(cur) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = n;
    return OK;
}

enum Errors find_sqrt_2_equations(double eps, double* rez){
    double n = 3, cur = 0, d_cur = 0;
    do
    {
        cur = pow(n, 2) - 2;       //метод приближений ньютона 
        d_cur = 2 * n;
        n -= cur/d_cur;
        if (n >= pow(10, MAX_POW_TO_DALAY))
            return INVALID_INPUT;
    } while (fabs(cur) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = n;
    return OK;
}

/*
-1 - составное число
0 - не простое и не составное
1 - простое число
*/
enum Errors is_prime_number(int nam, int* rez){
    if (nam <= 1){
        *rez = 0;
        return OK;
    }
    
    for (int i = 2; i*i <= nam; i++) {
        if(nam % i == 0){
            *rez = -1;
            return OK;
        }
    }
    
    *rez = 1;
    return OK;
}

enum Errors find_gamma_equations(double eps, double* rez){
    double n = 3, cur = 0, d_cur = 0;
    double loc_cur = 0,  loc_prev = 0, t = 1, cur_t = 1;
    int rez_is_prime = 0;
    do
    {
        do
        {
            t++;
            loc_prev = loc_cur;
            is_prime_number((int)t, &rez_is_prime);
            if (rez_is_prime == 1)
                cur_t *= (t-1)/t;
            loc_cur = log(t) * cur_t;
            if (t >= pow(10, MAX_POW_TO_DALAY))
                return INVALID_INPUT;
        } while (fabs(loc_cur - loc_prev) >= eps);
        cur = pow(EKS, -n) - loc_cur;       
        d_cur = -pow(EKS, -n);
        n -= cur/d_cur;
        if (n >= pow(10, MAX_POW_TO_DALAY))
            return INVALID_INPUT;
    } while (fabs(cur) >= eps);
    if (cur > ULLONG_MAX)
        return INVALID_INPUT;
    *rez = n;
    return OK;
}
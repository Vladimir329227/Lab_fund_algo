#include "main.h"

int main(int argc, char **argv) { 
    if (argc >= 2){
        double eps;
        switch(convert_str_to_double(argv[1], &eps))
        {
        case INVALID_INPUT:
            printf("INVALID_INPUT");
            return INVALID_INPUT;
        case INVALID_MEMORY:
            printf("INVALID_MEMORY");
            return INVALID_MEMORY;
        default:
            break;
        } 
        double results[15];
        enum Errors err[15];
        int n = 0;
        err[n] = find_e_by_limit(eps, &results[n]);
        ++n;
        err[n] = find_pi_by_limit(eps, &results[n]);
        ++n;
        err[n] = find_ln_2_by_limit(eps, &results[n]);
        ++n;
        err[n] = find_sqrt_2_by_limit(eps, &results[n]);
        ++n;
        err[n] = find_gamma_by_limit(eps, &results[n]);
        ++n;
        err[n] = find_e_by_row(eps, &results[n]);
        ++n;
        err[n] = find_pi_by_row(eps, &results[n]);
        ++n;
        err[n] = find_ln_2_by_row(eps, &results[n]);
        ++n;
        err[n] = find_sqrt_2_by_row(eps, &results[n]);
        ++n;
        err[n] = find_gamma_by_row(eps, &results[n]);
        ++n;
        err[n] = find_e_by_equations(eps, &results[n]);
        ++n;
        err[n] = find_pi_by_equations(eps, &results[n]);
        ++n;
        err[n] = find_ln_2_equations(eps, &results[n]);
        ++n;
        err[n] = find_sqrt_2_equations(eps, &results[n]);
        ++n;
        err[n] = find_gamma_equations(eps, &results[n]);

        printf("\t\t\t\t");
        printf("lim\t\t\t\t");
        printf("row\t\t\t\t");
        printf("equation\t\t\t\n");

        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
            case 0:
                printf("e\t\t\t\t");
                break;
            case 1:
                printf("pi\t\t\t\t");
                break;
            case 2:
                printf("ln(2)\t\t\t\t");
                break;
            case 3:
                printf("sqrt(2)\t\t\t\t");
                break;
            case 4:
                printf("gamma\t\t\t\t");
                break;
            default:
                break;
            }

            for (int o = 0; o < 3; o++)
            {
                switch (err[i+o*5])
                {
                case INVALID_INPUT:
                    printf("INVALID_INPUT\t\t\t");
                    break;
                case INVALID_MEMORY:
                    printf("INVALID_MEMORY\t\t\t");
                    break;
                case OK:
                    printf("%f\t\t\t", results[i+o*5]);
                    break;
                default:
                    break;
                }
            }
            printf("\n");
        }
    }
    else {
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }    
}

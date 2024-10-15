#include "main.h"

enum Errors fill_array(short** result_array, const int size_of_array, const short a, const short b) {
    (*result_array) = (short *) malloc(size_of_array * sizeof(short));
    if (!(*result_array))
        return INVALID_MEMORY;

    for(int i = 0; i < size_of_array; ++i)
    {
        (*result_array)[i] = rand() % labs(b + 1 - a) + a;
    }
    return OK;
}

enum Errors swap_min_max(short** arr, const int size) {
    if (!arr || !(*arr) || size <= 1)
        return INVALID_INPUT;

    int minIdx = 0;
    int maxIdx = 0;

    for (int i = 1; i < size; i++) {
        if ((*arr)[i] < (*arr)[minIdx]) {
            minIdx = i;
        } else if ((*arr)[i] > (*arr)[maxIdx]) {
            maxIdx = i;
        }
    }

    short temp = (*arr)[minIdx];
    (*arr)[minIdx] = (*arr)[maxIdx];
    (*arr)[maxIdx] = temp;
    return OK;
}

void bubbleSort(short* arr, const int size) {
    short temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

enum Errors find_closest(short* arr, const int size, const int target, short* result) {
    if (size == 0)
        return INVALID_INPUT; 

    int left = 0;
    int right = size - 1;
    *result = arr[0];
    int min_diff = abs(arr[0] - target);
    int mid, diff;

    while (left <= right) {
        mid = left + (right - left) / 2;
        diff = abs(arr[mid] - target);

        if (diff < min_diff) {
            min_diff = diff;
            *result = arr[mid];
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else if (arr[mid] > target) {
            right = mid - 1;
        } else {
            *result = arr[mid]; 
            break;
        }
    }


    return OK;
}

enum Errors generate_array_with_find_closest(short * array_a, const int size_of_array_a,
                                            short * array_b, const int size_of_array_b,
                                            short ** array_c)
{
    if (!array_a || !array_b)
        return INVALID_INPUT;
    
    (*array_c) = (short*) malloc(sizeof(short) * size_of_array_a);
    if (!array_c)
        return INVALID_MEMORY;
    bubbleSort(array_b, size_of_array_b);
    short find_namber;
    for(int i = 0; i < size_of_array_a; ++i)
    {
        if (find_closest(array_b, size_of_array_b, array_a[i], &find_namber) != OK){
            free(*array_c);
            return INVALID_INPUT;
        }
        (*array_c)[i] = array_a[i] + find_namber;
    }


    return OK;
}



/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_utils
*/

#include "test_utils.h"
#include <criterion/redirect.h>

int should_malloc_fail = 0;  

void *__real_malloc(size_t size);

void *__wrap_malloc(size_t size) {
    if (should_malloc_fail) {
        return NULL;
    }
    return __real_malloc(size);
}


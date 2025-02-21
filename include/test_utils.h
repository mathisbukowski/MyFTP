/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_utils
*/

#ifndef TEST_UTILS_H_
    #define TEST_UTILS_H_
    #include <stddef.h>

extern int should_malloc_fail;

void *__wrap_malloc(size_t size);


#endif /* !TEST_UTILS_H_ */

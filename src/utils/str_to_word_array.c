/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"

int iscustomalphanum(char letter, char const *delimiters)
{
    while (*delimiters != '\0') {
        if (letter == *delimiters) {
            return 0;
        }
        delimiters++;
    }
    if (letter >= 32 && letter <= 126) {
        return (1);
    }
    return 0;
}

int count_words_in_array(char *tab, const char *delimiters)
{
    int i;
    int count = 0;

    for (i = 0; tab[i] != '\0'; i++) {
        if (iscustomalphanum(tab[i], delimiters) == 1
            && iscustomalphanum(tab[i + 1], delimiters) != 1) {
            count++;
            }
    }
    return count;
}

int word_length(char *str, int i, const char *delimiters)
{
    int z = 0;

    while (iscustomalphanum(str[i], delimiters)) {
        z++;
        i++;
    }
    return z;
}

char **str_to_word_array(char *str, char const *delimiters)
{
    int nb_word = count_words_in_array(str, delimiters);
    char **result = malloc(sizeof(char *) * (nb_word + 1));
    int word_in_str = 0;
    int letter = 0;
    int size_max = strlen(str);

    for (int i = 0; i < size_max; i++) {
        if (iscustomalphanum(str[i], delimiters) == 1) {
            word_in_str = word_length(str, i, delimiters);
            result[letter] = malloc(sizeof(char) * (word_in_str + 1));
            strncpy(result[letter], &str[i], word_in_str);
            result[letter][word_in_str] = '\0';
            letter++;
            i += word_in_str;
        }
    }
    result[nb_word] = NULL;
    return result;
}

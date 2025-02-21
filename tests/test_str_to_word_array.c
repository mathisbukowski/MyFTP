/*
** EPITECH PROJECT, 2025
** tests
** File description:
** strtowordarray
*/

#include <criterion/criterion.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ftp.h"

Test(iscustomalphanum, test_normal_char) {
    cr_assert_eq(iscustomalphanum('a', " ,;"), 1, "Character 'a' should be valid");
}

Test(iscustomalphanum, test_delimiter_char) {
    cr_assert_eq(iscustomalphanum(' ', " ,;"), 0, "Space delimiter should be invalid");
}

Test(iscustomalphanum, test_special_char) {
    cr_assert_eq(iscustomalphanum('\n', " ,;"), 0, "Newline should be invalid");
}

Test(iscustomalphanum, test_number_char) {
    cr_assert_eq(iscustomalphanum('5', " ,;"), 1, "Number '5' should be valid");
}

Test(count_words_in_array, test_simple_sentence) {
    char str[] = "Hello world";
    cr_assert_eq(count_words_in_array(str, " "), 2, "Should count 2 words");
}

Test(count_words_in_array, test_multiple_delimiters) {
    char str[] = "Hello,world;test";
    cr_assert_eq(count_words_in_array(str, " ,;"), 3, "Should count 3 words");
}

Test(count_words_in_array, test_empty_string) {
    char str[] = "";
    cr_assert_eq(count_words_in_array(str, " "), 0, "Empty string should return 0");
}

Test(count_words_in_array, test_only_delimiters) {
    char str[] = "   ,,;;  ";
    cr_assert_eq(count_words_in_array(str, " ,;"), 0, "String with only delimiters should return 0");
}

Test(word_length, test_simple_word) {
    char str[] = "Hello world";
    cr_assert_eq(word_length(str, 0, " "), 5, "Word 'Hello' should be 5 characters");
}

Test(word_length, test_word_with_multiple_delimiters) {
    char str[] = "Test,world";
    cr_assert_eq(word_length(str, 0, " ,;"), 4, "Word 'Test' should be 4 characters");
}

Test(word_length, test_last_word) {
    char str[] = "Hello world";
    cr_assert_eq(word_length(str, 6, " "), 5, "Word 'world' should be 5 characters");
}


Test(str_to_word_array, test_simple_split) {
    char str[] = "Hello world test";
    char **result = str_to_word_array(str, " ");
    
    cr_assert_str_eq(result[0], "Hello", "First word should be 'Hello'");
    cr_assert_str_eq(result[1], "world", "Second word should be 'world'");
    cr_assert_str_eq(result[2], "test", "Third word should be 'test'");
    cr_assert_eq(result[3], NULL, "Array should be NULL-terminated");
    

    for (int i = 0; result[i] != NULL; i++)
        free(result[i]);
    free(result);
}

Test(str_to_word_array, test_multiple_delimiters_split) {
    char str[] = "Hello,world;test";
    char **result = str_to_word_array(str, " ,;");
    
    cr_assert_str_eq(result[0], "Hello", "First word should be 'Hello'");
    cr_assert_str_eq(result[1], "world", "Second word should be 'world'");
    cr_assert_str_eq(result[2], "test", "Third word should be 'test'");
    cr_assert_eq(result[3], NULL, "Array should be NULL-terminated");
    for (int i = 0; result[i] != NULL; i++)
        free(result[i]);
    free(result);
}

Test(str_to_word_array, test_empty_string) {
    char str[] = "";
    char **result = str_to_word_array(str, " ");
    
    cr_assert_eq(result[0], NULL, "Empty string should return NULL-terminated array");
    
    free(result);
}
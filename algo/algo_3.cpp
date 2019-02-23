#include "ctype.h"
#include "stdio.h"
#include "string.h"

void swap_chars(char *sentence, int char_closer_to_word_beginning_index, int char_closer_to_word_ending_index) {
    char tmp = sentence[char_closer_to_word_ending_index];
    sentence[char_closer_to_word_ending_index] = sentence[char_closer_to_word_beginning_index];
    sentence[char_closer_to_word_beginning_index] = tmp;
}

void reverse_word_recursively(char *sentence, int word_beginning_index, int word_ending_index) {
    if (word_beginning_index < word_ending_index) {
        swap_chars(sentence, word_beginning_index, word_ending_index);
        reverse_word_recursively(sentence, word_beginning_index + 1, word_ending_index - 1);
    }
}

int is_not_last_char_in_word_yet(char *sentence, int index) {
    return index > 0 && isspace(sentence[index]) ? 1 :  0;
}

int is_first_char_in_word(char *sentence, int index) {
    return index == 0 || isspace(sentence[index-1]);
}

/**
 * Reverse last word in given sentence recursively.
 * 1. Looking for the beginning and the ending of the last word in a sentence.
 * 2. When found - reversing the last world in the given char array by mutating this array
 * @param sentence - sentence last word of which should be reversed
 * @param potentially_first_char_in_word_index - index of the char which might be the first char in the last word
 * @param potentially_last_char_in_word_index - index of the char which might be the last char in the last word
 */
void reverse_last_word_of_sentence_recursively(
        char *sentence,
        int potentially_first_char_in_word_index,
        int potentially_last_char_in_word_index) {

    // Nothing to reverse
    if (potentially_last_char_in_word_index <= 0) {
        return;
    }
    // Skip whitespaces in the end of the sentence
    if (is_not_last_char_in_word_yet(sentence, potentially_first_char_in_word_index)) {
        reverse_last_word_of_sentence_recursively(sentence, potentially_first_char_in_word_index - 1,
                                                  potentially_last_char_in_word_index - 1);
        return;
    }
    if (is_first_char_in_word(sentence, potentially_first_char_in_word_index)) {
        // Found the word beginning - reverse the last word
        reverse_word_recursively(sentence, potentially_first_char_in_word_index, potentially_last_char_in_word_index);
        return;
    } else {
        // Proceed looking for the word beginning
        reverse_last_word_of_sentence_recursively(sentence, potentially_first_char_in_word_index - 1,
                                                  potentially_last_char_in_word_index);
    }
}

/**
 * Reverse last word in given sentence using cycle.
 * 1. Looking for the beginning and the ending of the last word in a sentence.
 * 2. When found - reversing the last world in the given char array by mutating this array
 * @param sentence - sentence last word of which should be reversed
 * @param length - length of the given sentence
 */
void reverse_last_word_with_cycle(char *sentence, int length) {
    // Nothing to reverse
    if (length <= 0) {
        return;
    }

    int last_word_char_index = length;
    for ( ; is_not_last_char_in_word_yet(sentence, last_word_char_index); last_word_char_index--);

    // Word either doesn't exist or has just one char
    if (last_word_char_index <= 0) {
        return;
    }

    int first_word_char_index = last_word_char_index-1;
    for ( ; !is_first_char_in_word(sentence, first_word_char_index); first_word_char_index--);

    for( ; first_word_char_index < last_word_char_index; first_word_char_index++, last_word_char_index--) {
        swap_chars(sentence, first_word_char_index, last_word_char_index);
    }
}

int main() {
    int max_input_size = 100;
    char input[max_input_size];
    printf("Print sentence\n");

    fgets(input, max_input_size, stdin);
    int length = (int) strlen(input)-1;
    reverse_last_word_with_cycle(input, length);
    printf("Reversed with a cycle:\n");
    printf("%s\n", input);

    reverse_last_word_of_sentence_recursively(input, length, length);
    printf("Reversed back recursively:\n");
    printf("%s\n", input);

    return 0;
}
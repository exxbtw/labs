#include <stdio.h>

#ifndef TRANSLATOR_UTILS_H
#define TRANSLATOR_UTILS_H

#define MAX_LINE 4096
#define MAX_WORD 256

typedef struct {
    char* rus;
    char* eng;
} DictionaryEntry;

DictionaryEntry* load_dictionary(const char* filename, int* size);
const char* find_translation(const char* word, DictionaryEntry* dict, int size);
void translate(char* line, FILE* out, DictionaryEntry* dict, int dict_size);
int is_utf8_letter_start(unsigned char c);
int utf8_char_len(unsigned char c);

#endif

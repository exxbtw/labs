#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 4096
#define MAX_WORD 256

typedef struct {
    char* rus;
    char* eng;
} DictionaryEntry;

DictionaryEntry* load_dictionary(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Не удалось открыть словарь");
        exit(1);
    }

    int capacity = 64;
    *size = 0;
    DictionaryEntry* dict = malloc(capacity * sizeof(DictionaryEntry));
    if (!dict) {
        perror("Ошибка выделения памяти под словарь");
        exit(1);
    }

    char rus[MAX_WORD], eng[MAX_WORD];
    while (fscanf(file, "%s %s", rus, eng) == 2) {
        if (*size >= capacity) {
            capacity *= 2;
            dict = realloc(dict, capacity * sizeof(DictionaryEntry));
        }
        dict[*size].rus = strdup(rus);
        dict[*size].eng = strdup(eng);
        (*size)++;
    }

    fclose(file);
    return dict;
}

const char* find_translation(const char* word, DictionaryEntry* dict, int size) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(word, dict[i].rus) == 0) {
            return dict[i].eng;
        }
    }
    return NULL;
}

//Проверка, является ли байт началом UTF-8 буквы (русские и латинские)
int is_utf8_letter_start(unsigned char c) {
    return (c >= 0xC0) || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

//Возвращает длину UTF-8 символа
int utf8_char_len(unsigned char c) {
    if ((c & 0x80) == 0) return 1;           //ASCII
    else if ((c & 0xE0) == 0xC0) return 2;   //2-byte UTF-8
    else if ((c & 0xF0) == 0xE0) return 3;   //3-byte UTF-8
    else return 1;                           //fallback
}

void process_line(char* line, FILE* out, DictionaryEntry* dict, int dict_size) {
    int i = 0;
    while (line[i]) {
        if (!is_utf8_letter_start((unsigned char)line[i])) {
            fputc(line[i], out);
            i++;
            continue;
        }

        char word[MAX_WORD] = {0};
        int w = 0;

        while (line[i] && is_utf8_letter_start((unsigned char)line[i])) {
            int len = utf8_char_len((unsigned char)line[i]);
            if (w + len >= MAX_WORD) break;
            strncpy(&word[w], &line[i], len);
            i += len;
            w += len;
        }
        word[w] = '\0';

        const char* trans = find_translation(word, dict, dict_size);
        if (trans)
            fputs(trans, out);
        else
            fputs(word, out);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Использование: %s text_rus.txt dictionary.txt text_eng.txt\n", argv[0]);
        return 1;
    }

    const char* input_filename = argv[1];
    const char* dict_filename = argv[2];
    const char* output_filename = argv[3];

    int dict_size = 0;
    DictionaryEntry* dict = load_dictionary(dict_filename, &dict_size);

    FILE* in = fopen(input_filename, "r");
    FILE* out = fopen(output_filename, "w");
    if (!in || !out) {
        perror("Ошибка открытия файлов");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), in)) {
        process_line(line, out, dict, dict_size);
    }

    fclose(in);
    fclose(out);

    for (int i = 0; i < dict_size; ++i) {
        free(dict[i].rus);
        free(dict[i].eng);
    }
    free(dict);

    return 0;
}



// ./translateProg text_rus.txt dictionary.txt text_eng.txt

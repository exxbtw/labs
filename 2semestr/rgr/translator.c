#include <stdio.h>
#include <stdlib.h>
#include "translator_utils.h"

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
    while (fgets(line, sizeof(line), in)) { //Чтение строки
        translate(line, out, dict, dict_size);
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define name "yura"

void ReplaceLongWordToName(char *line) {

    char copy[200]; //сделали копию, чтобы не ломать
    strcpy(copy, line); //копируем строку line в переменную copy

    char thelongestword[200] = ""; //тут будем хранить самое длинное слово    
    int thelongestdlina = 0; //длина самого длинного слова


    char *word = strtok(copy, " ,.!?\n"); //раскладываем строки на слова и получаем первое
    while(word != NULL) {
        int len = strlen(word);
        if(len > thelongestdlina) {
            thelongestdlina = len;
            strcpy(thelongestword, word); //копируем текущее слово в пер. thelongestword
        }
        word = strtok(NULL, " ,.!?\n"); //продолжает с того места, где остановился в прошлый раз.
    }
    
    if (thelongestdlina > 0) {
        char temp[200]; //сюда будем записывать новую строку с замененным словом.
        char *pos = strstr(line, thelongestword); //ищет в строке line то слово, которое мы определили как самое длинное.
        
        if (pos) { //если нашли слово, то pos укажет на него
            int index = pos - line; //вычитаем адрес начала строки из адреса найденного слова и получаем индекс этого слова в строке.
            temp[0] = '\0'; //Очищаем временную строку

            strncat(temp, line, index); //копирует в temp часть строки до найденного слова.
            strcat(temp, name); //добавляет "yura" вместо самого длинного слова.
            strcat(temp, pos + thelongestdlina); //Добавляем текст после слова

            strcpy(line, temp); //Перезаписываем строку
        }

    }

}



int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Usage: ./a.out file.txt out.txt\n");
        exit(1);
    }

    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL) { //открылся ли файл
        perror("Error opening input file");
        exit(1);
    }

    FILE *file_w;
    file_w = fopen(argv[2], "w");
    if (file_w == NULL) { //открылся ли файл
        perror("Error opening output file");
        fclose(file);
        exit(1);
    }
    
    

    printf("Исходное содержимое\n");
    char s[200]; //выводим файл до
    while (fgets(s, sizeof(s), file) != NULL) {
        printf("%s", s);
    }

    rewind(file); //перемещает указатель файла в самое его начало

    printf("\n");
    printf("Содержимое после замены\n");
    while (fgets(s, sizeof(s), file) != NULL) {
        ReplaceLongWordToName(s);
        printf("%s", s);
        fprintf(file_w, "%s", s); //запис изм строку в аутпут файл
    }

    if (fclose(file) != 0){
        perror("Error closing file");
        exit(1);
    }

    if (fclose(file_w) != 0){
        perror("Error closing file");
        exit(1);
    }


    


}


//while (fgets(s, sizeof(s), file) != NULL) {
//Первый параметр — это массив, в который будет сохранена считанная строка (в данном случае, массив s).
//Второй параметр — это максимальное количество символов, которое можно считать (в данном случае, это sizeof(s), что означает размер массива s).
//Третий параметр — это указатель на файл (в данном случае, file).
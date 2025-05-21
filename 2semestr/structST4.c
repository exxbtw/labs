#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int N = 100;


struct Student { //структура переменных
    char name[64];
    int math;
    int physics;
    int infa;
    int total;
};

struct Student addStudent(char name[64], int math, int physics, int infa) { //функция для заполнения структуры данными
    struct Student newStudent; //newStudent - объект структуры student

    strncpy(newStudent.name, name, sizeof(newStudent.name) - 1); //sizeof -1 чтобы оставить место под оканчивающий 0
    newStudent.name[sizeof(newStudent.name) - 1] = '\0';

    newStudent.math = math;
    newStudent.physics = physics;
    newStudent.infa = infa;
    newStudent.total = math + physics + infa;

    return newStudent;
};

void printStudentInfo(struct Student st){ //функция вывод студента
    printf("\n%s, имеет %d баллов по матеше, %d по физике, %d по информатике, Общий рейтинг: %d\n", st.name, st.math, st.physics, st.infa, st.total);
}

void SelectionSort(struct Student students[], int N){ //selection sort
    
    for(int i=0; i<N-1; i++){ //n-1 в конце уже остается мин элемент, внеш проходит по каждому эл массива
        int maxtotalstudent = i; //текущий макс

        for(int j=i+1; j<N; j++){ //макс среди оставшихся ищем
            if(students[j].total>students[maxtotalstudent].total){
                maxtotalstudent = j;
            }
        }
    if(maxtotalstudent!=i){ //фикт
            struct Student temp = students[i];
            students[i] = students[maxtotalstudent];
            students[maxtotalstudent] = temp;
            }
    }

}

void RadixSort(struct Student students[], int N){
    int max = students[0].total; //ищем макс чтоб определить кол-во разрядов(единицы десятки сотни и тд)
    for (int i = 1; i < N; i++) {
        if (students[i].total > max) {
            max = students[i].total;
        }
    }

    for(int razryad = 1; max / razryad > 0; razryad = razryad * 10){ //razryad = 1, 10, 100
        for(int i = 0; i < N-1; i++){ //тк посл эл уже отсортирован будет
            for (int j = 0; j < N - i - 1; j++) { //не трогаем уже отсорт эл, бабл сортом
                int Student_J = (students[j].total / razryad) % 10; //1234 / 10 = 123,4 | 123,4 % 10 = 4
                int Student_J_plus_1 = (students[j+1].total / razryad) % 10;

                if (Student_J < Student_J_plus_1){
                    struct Student temp = students[j];
                    students[j] = students[j+1];
                    students[j+1] = temp;
                }
            }
        }
    }
}
int main(){

    struct Student st; //st - объект структуры student
    struct Student students[N]; //массив студентов

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        char name[64];
        sprintf(name, "Бедолага - %d", i + 1);  

        int math = rand() % 100;
        int physics = rand() % 100;
        int infa = rand() % 100;

        students[i] = addStudent(name, math, physics, infa);
    }

    char choice[10]; //выбираем метод сорта
    printf("Каким методом сортируем?(radix или select):\n");
    scanf("%s", choice);

    printf("Первые 10 студентов до:\n"); //вывод до сортировки
    for (int i = 0; i < 10; i++) {
        printStudentInfo(students[i]); 
    }
printf("---------------------------------------------------------\n");

    if(strcmp(choice, "select") == 0){ //возвр 0 если строки равны
        SelectionSort(students, N);
    }

    else{
        RadixSort(students, N);
    }

    printf("Первые 10 студентов после:\n"); //вывод после сортировки
    for (int i = 0; i < 10; i++) {
        printStudentInfo(students[i]); 
    }

printf("---------------------------------------------------------\n");
    printf("CPU: \n");
    system("sysctl -n machdep.cpu.brand_string");
    system("sysctl -n hw.cpufrequency");
    

    clock_t start = clock();  //время измеряем(фикс нач момент)
    if (strcmp(choice, "select") == 0) { //если choice = select
        SelectionSort(students, N); //измеряем selection
    } else {
        RadixSort(students, N); //измеряем radix
    }

    clock_t end = clock();  //измерили

    double codetime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время, потраченное на сортировку: %f секунд\n", codetime);

    size_t weight = sizeof(students); 
    printf("Размер массива: %zu байт (%f КБ)\n", weight, weight / 1024.0);


}
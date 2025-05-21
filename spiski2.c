#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;

struct node {
    int data; //числа в качестве данных
    struct node *next; //указатель на след узел
    struct node *ALT; //указатель альтернативный
    struct node *back; //указ на пред узел
};

node_t *newNode(int data) {//функция для создания нового узла
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data; //присваиваем значение
    new_node->next = NULL;
    new_node->ALT = NULL;
    new_node->back = NULL;
    return new_node;
}

void printList(node_t *head) {
    node_t* cur = head; //голова - начало списка
    while (cur) { //пока cur != hull
        printf("%d -> ", cur->data); //вводим
        cur = cur->next; //переход на некст узел
    }
    printf("NULL\n");
}

void printListWithALT(node_t *head) {
    node_t* cur = head;
    while (cur) {
        printf("%d ", cur->data);
        if (cur->ALT) { 
            printf("(ALT -> %d) ", cur->ALT->data);
        }
        printf("-> ");
        cur = cur->next;
    }
    printf("NULL\n");
}

//доб. в конец списка
node_t* appendBack(node_t* head, int data) {
    node_t* new_node = newNode(data);
    if (head == NULL) return new_node; //если список пуст то новый узел станет головой
    node_t* cur = head;
    while(cur->next != NULL) cur = cur->next; //находим ласт узел
    cur->next = new_node;
    new_node->back = cur; //новый будет указывать на предыдущий
    return head; //возвр обновл список
}

node_t* appendBackSecond(node_t* head, int data) {
    node_t* new_node = newNode(data);
    if (head == NULL) return new_node;
    node_t* cur = head;
    while(cur->next != NULL) cur = cur->next;
    cur->next = new_node;
    new_node->back = cur;
    return head;
}

void reverseList(node_t **head) { //реверс верхнего списка, меняет указатели next и back
    node_t *prev, *cur, *next; 
    cur = *head;
    prev = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        if (prev) prev->back = cur;
        prev = cur;
        cur = next;
    }
    *head = prev; 
}

void navigateList(node_t *S, node_t *head2) {
    if (!S) return;
    node_t *current = S;
    //Перемещ в самый правый элемент верхнего списка
    while (current->next) {
        current = current->next;
    }

    int WhichList = 1;  //флаг, в каком списке находимся
    char command;

    printf("\n//// мувмент ////\n");
    while (1) {
        printf("Текущий узел: %d\n", current->data);
        printf("Введите команду (WASD - мувмент, Q - выход): ");
        scanf(" %c", &command);
        
        switch (command) {
            //вправо только в нижнем списке
            case 'D':
                if (WhichList == 0 && current->next) {
                    current = current->next;  //вправо только для второго списка
                } else {
                    printf("Незя вправо!\n");
                }
                break;
            //влево только в верхнем списке
            case 'A':
                if (WhichList == 1 && current->back) {
                    current = current->back;  //движение влево
                } else {
                    printf("Незя влево!\n");
                }
                break;
            //вниз через ALT
            case 'S':
                if (current->ALT) {
                    current = current->ALT;
                    WhichList = 0;  //переключ между списками
                } else {
                    printf("Нет альтернативного перехода!\n");
                }
                break;
            case 'W':
                if (WhichList == 1) {
                    printf("Вверх тебе ваще не дано.\n");
                } else {
                    printf("Ты и так внизу!\n");
                }
                break;
            case 'Q':
                return;
            default:
                printf("Неверная команда! Используйте WASD\n");
        }
    }
}

int main() {
    node_t *S = NULL;
    node_t* head2 = NULL;
    int n, m; //переменные сканф
    
    while (1) {
        printf("Введи узел (первый список): ");
        scanf("%d", &n);
        if (n <= 0) break;
        S = appendBack(S, n);
    }
    
    while (1) {
        printf("Введи узел (второй список): ");
        scanf("%d", &m);
        if (m <= 0) break;
        head2 = appendBackSecond(head2, m);
    }
    
    reverseList(&S);
    
    node_t *cur1 = S;
    node_t *cur2 = head2;
    while (cur1 && cur2) { //пока 2 указ не достигнут конца списков
        cur1->ALT = cur2; //верх и низ
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    
    printList(S);
    printList(head2);
    printListWithALT(S);
    navigateList(S, head2);
    return 0;
}
#ifndef ABONENT_H
#define ABONENT_H

#define MAX_NAME 100
#define MAX_PHONE 20
#define MAX_ADDRESS 150

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char address[MAX_ADDRESS];
} Abonent;

void addAbonents(const char *filename, int n);
void printAbonents(const char *filename);
void searchAbonent(const char *filename);

#endif

#include <stdio.h>

int main() {
    printf("dec: ");
  char dec; //вводим число в 10 С.С.
    int bin=1;
    int sum;
    int k=0;
  scanf("%hhd", &dec);
  printf("bin: ");
  for (int i = sizeof(dec)*8-1; i>=0; i--){
    bin=((dec >> i) & 1);
    printf("%d", bin);
    if(bin == 1){
        k=k+1;
    }
  }
  printf("\n");
    printf("Кол-во единиц: %d\n", k);

}
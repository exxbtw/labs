#include <stdio.h>
int main(){
int h;
printf("Высота фигуры: ");
scanf("%d",&h);

printf("\n*******\n");
for(int i=0; i<h-2; i++){
	printf("*     *\n");
}
printf("*******\n");
}

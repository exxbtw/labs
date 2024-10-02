#include <stdio.h>

int main(){
int a=13;
int s=0;
for(int n=2; n<a; n++){
	if (a%n==0){
	s++;
	}
}
	if (s==0){
	puts("Good");
	}
}

// Определяет, является ли число простым

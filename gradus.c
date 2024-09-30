#include <stdio.h>

int main() {
	printf("Enter gradus= ");
	float a;
	char b;
	scanf("%f%c", &a, &b);
	if(b=='c' || b=='C')
		{
		float r = ((a*1.8)+32);
		printf("%.2f°F\n",r);
		}
	if(b=='f' || b=='F')
		{
		float p = ((a-32)/1.8);
		printf("%.2f°C\n", p);
		}

}

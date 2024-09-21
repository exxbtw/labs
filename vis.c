#include <stdio.h>

int main() {
	int y;
	printf("enter year: ");
	scanf("%d", &y);
	if(y % 400 == 0)
	{
	printf("y=YES\n");
	}
	else if(y % 100 ==0)
	{
	printf("y=NO\n");
	}
	else if(y % 4 == 0)
	{
	printf("y=YES\n");
	}
	else
	{
	printf("y=NO\n");
	}
	

}

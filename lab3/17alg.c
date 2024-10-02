#include <stdio.h>
int main(){
int b= 13;
int n=2;
int flag=0;
while (b%n!=0){
n++;
if (n==b) { //если число доходит до себя - значит оно простое
flag=1;
break; }
}
if(flag==1){
	printf("число простое:%d\n",b);
}
else {
	printf("число делится на %d\n", n);
}
}
//находит наименьший общий делитель

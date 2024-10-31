#include <stdio.h>
#include  <string.h>
int main(){
    int cifra[10]={0,1,2,3,4,5,6,7,8,9};
    char text[]="Lorem ipsum dolor sit 5 amet, 6 consectetur 3 adipiscing elit, sed 2 do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    int sum=0;
    for(int i=0; i<strlen(text);i++){ //цикл перебирает буквы из текста
        for(int c=0; c<10;c++){ //цикл перебирает цифры
            if(text[i]=='0'+cifra[c]){ //0+цифра, иначе не выведет :)
                sum=sum+cifra[c]; 
                printf("%d\n",cifra[c]);
                break;  
            }
        }
    }
    if(sum==0){
        printf("Нету цифр\n");
    }
    else{
    printf("Сумма цифр в тексте равняется: %d\n",sum);
    }
}
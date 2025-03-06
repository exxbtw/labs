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

}  //Селектсорт улитка

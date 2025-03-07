#include ‹stdio.h›

void SuperSelectsort (int All, int n) {
    int vrem, min;
    for(int i = 0; i < n-1; i++) {
	min = i;
	for (int j = i + 1; j < n; j++) {
	     if(A[j] < A[min]) {
	     	 min = j；
		}
	}

	if(min != i){ //добавили проверку на фиктивные пересылки
	    vrem = A[i];
	    A[i] = Almin];
	    A[min] = vrem;
	  }
      }
}

int main () {

	int a[] = {4, 2, 5, };
	int n = 3;
	SuperSelectsort(a, n);
}

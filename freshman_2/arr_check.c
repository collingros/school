#include <stdio.h>
int question(int arr[], int size, int val);

int main(){
  int[] arr = {1, 1, 1, 5, 7};
  int size = 5;
  int val = 7;
  
  int num = question(arr, size, val);
  printf("%d\n", num);
  return 0;
}

int question(int arr[], int size, int val){
  int num = 0;
  for(int i = 0; i < size; i++){
    if (arr[i] != val)
      num++;
  }
  return num;
}

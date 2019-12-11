#include <stdio.h>

int eighteen();
int fourteen();
int main(){
  eighteen();
  fourteen();
  return 0;
}

int eighteen(){
  int speed = 75;
  int fee;
  if (speed > 35)
    fee = 20;
  else if (speed > 50)
    fee = 40;
  else if (speed > 75)
    fee = 60;
  printf("%d\n", fee);
  return 0;
}

int fourteen(){
  int n = 0;
  scanf("%d", &n);
  int ev = 0;
  while (ev < n){
    printf("%3d", ev);
    ev = ev+2;
  }
  printf("\n");
  return 0;
}

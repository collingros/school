#include <stdio.h>
 
char pass[] = "abcd";
 
int validate_user() {
   char buff[5];
   printf("Enter your password:\n -> ");
   gets(buff);
   return !strcmp(buff, pass);
}

void failure(){
   printf("Your password was not correct :(\n");
}

void success(){
   printf("Your password was correct :)\n");
}
 
int main(int argc, char *argv[]){
   if(validate_user()){
       success();
   }
   else{
       failure();
   }
   return 0;
}

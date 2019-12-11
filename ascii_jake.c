#include <stdio.h> // bool, char, short, int, long --- all the same to the machine.
int main() { // bool is 1 bit, char is a 1 byte integer, short is 2 bytes, int is 4 bytes, long is 8 bytes. assuming x64 hardware
  char buf[8192] = {0}, letter[1] = {0}, choice[1] = {0}, periodpos[1] = {0}; // assign everything to an array to save a line lololol
  while (1) 
  { // infinite loops are bad oh no
    periodpos[0] = 0; // default period position set to 0 (beginning of string)
    puts("\nMenu:\n1. Encrypt\n2. Decrypt\n3. Exit"); // elite printing
    fgets(buf, 8192, stdin); // fgets takes ("buffer",buffer_length,buffer_source). buffer_source==stdin=="standard input"
    sscanf(buf, "%d", choice); // sscanf takes ("buffer", "format", "where to store found value"), %d is formatting for "decimal" or "int"
    if (choice[0] == 3) // shit. check if its 3 and exit if it is
      return 0; // c programs exit by returning from main
    puts( ((choice[0] > 0) && (choice[0] < 3)) ? "Type message: " : "Invalid input. Try again..."); // google "ternary operator"
    fgets(buf, 8192, stdin); // once again fgets for the second question, store data in our buffer "buf"
    for(int i = 0; buf[i] != '\n'; i++) 
    { // iterates through the buffer until a \n is encountered. \n gets in there when you press enter
      if (choice[0] == 1) // if the user entered 1 as their choice then....
        printf("%d.", buf[i]); // buf[i] stores 1 letter. here we use %d to convert that letter to its int equivalent.
      else if (choice[0] == 2) 
      { // if the user entered 2 as their choice then...
        if (buf[i] == '.') 
        { // if we found a period then...
          sscanf(&buf[periodpos[0]], "%d.", letter); // (&buf[periodpos[0]] == memory address) scan for a letter and put it in our letter variable
          printf("%c", letter[0]); // print our current letter
          periodpos[0] = i+1;
        }
      }
    }
  }
  return 0;
} // set our new period position to the position after the one we just found


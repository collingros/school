
void main(void) begin
  int x[5];
  int i;
   i=0;
  while i < 5 do
   begin
      write "enter X";
      read x[i];
      i = i + 1;
   end
 
   i=0;

  while (i < 5) do
   begin
      write x[i] * x[i];
      i = i + 1;
   end

end

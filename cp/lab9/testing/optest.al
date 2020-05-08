void main(void)
begin
	boolean x;
	int x1;
	boolean y;

	x = true;
	write "x should be 1";
	write x;

	y = false;
	write "y should be 0";
	write y;

	x = not x;
	write "x should be 0";
	write x;

	x1 = ((3 + 5) * 2)/4;
	write "x1 should be 4";
	write x1;

	x = true;
	y = false;
	x = x and y;
	write "x should be false";
	write x;

	x = true;
	y = false;
	x = x or y;
	write "x should be true";
	write x;

	x = false;
	x = 5 < 6;
	write "x should be true";
	write x;

	x = true;
	x = 7 < 6;
	write "x should be false";
	write x;
end

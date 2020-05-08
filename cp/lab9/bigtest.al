
int globArr[3];
int globX;

void main(int p1, boolean p2)
begin
	int i;
	int locArr[5];

	write "begin\n";

	i = 0;
	while (i < 3) do
	begin
		globArr[i] = i * i;
		i = i + 1;
	end

	write "\nthe contents of globArr is: \n";
	i = 0;
	while (i < 3) do
	begin
		write globArr[i];
		i = i + 1;
	end

	i = 0;
	while (i < 5) do
	begin
		locArr[i] = 2 + i;
		i = i + 1;
	end

	write "\nthe contents of locArr is: \n";
	i = 0;
	while (i < 5) do
	begin
		write locArr[i];
		i = i + 1;
	end

	write "\nbegin expression tests\n";
	if (1 + 2 != 2) then
	begin
		write "pass\n";
	end
	else
	begin
		write "fail\n";
	end

	if (globArr[0] > locArr[0]) then
	begin
		write "fail\n";
	end
	else
	begin
		write "pass\n";
	end

	if (not false) then
	begin
		write "pass\n";
	end
	else
	begin
		write "fail\n";
	end

	p1 = ((8 * 2) / 4) * (4 - 2);
	if (not (p1 == 8)) then
	begin
		write "fail\n";
	end
	else
	begin
		write "pass\n";
	end

	write "enter something: ";
	read globX;
	write "\nyou entered: ";
	write globX;

	p2 = true;
	if (p2) then
	begin
		write "pass\n";
	end
	else
	begin
		write "fail\n";
	end

	write "exit\n";

end


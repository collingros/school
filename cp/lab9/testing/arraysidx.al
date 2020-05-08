void main(void)
begin
	int x[10];
	int i;

	i = 0;
	while (i < 10) do
	begin
		x[i] = i;
		i = i + 1;
	end

	write x[x[2]];
	write "\n";
end

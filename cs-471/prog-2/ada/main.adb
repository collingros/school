-- collin gros
-- 09-09-2020
--
-- this program tests whether short-circuiting is present in ADA.
-- it uses two functions, one that returns true and the other that
-- returns false (each print whenever they are called) to prove
-- a function call is skipped when evaluating an if statement.
-- (short circuit)


with Ada.text_IO;
use Ada.text_IO;



-- main tests whether ada does short circuit evaluation
procedure main is
		-- retTrue: returns true and prints to stdout "retTrue!"
		function retTrue return Boolean is
		begin
			Put("retTrue!");
			New_Line;
			return TRUE;
		end retTrue;

		-- retFalse: returns false and prints to stdout "retFalse!"
		function retFalse return Boolean is
		begin
			Put("retFalse!");
			New_Line;
			return FALSE;
		end retFalse;
begin
	-- test whether ada does short circuiting with and
	-- if short circuiting, should do retFalse! and nothing else.
	if retFalse and retTrue then
		Put("executed FALSE AND TRUE");
		New_Line;
	end if;

	-- test whether ada does short circuiting with or
	-- if short circuiting, should do retTrue! and nothing else.
	if retTrue or retFalse then
		Put("executed TRUE OR FALSE");
		New_Line;
	end if;
end main;


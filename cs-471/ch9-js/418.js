// collin gros
// 10-26-2020
// cs471
//
// problem description:
	// Implement the code on page 394 n JavaScript.  (page 418 in Version 10 of
	// the book)
	// page 418 11th Global Edition
	// Determine if JavaScript implements Shallow, Deep, of Ad Hoc Binding.
//
// code was copied from the textbook - pg 418 (11th global).
// this shows that javascript uses "deep binding" because the var 'x' after
// the call to sub4 with param sub2 (in sub2) is 1. this is what sub2
// has seen all along, which means javascript looked at sub2's environment,
// meaning deep binding is used.
//

function sub1()
{
	console.log("sub1");
	var x;
	function sub2()
	{
		console.log("sub2");
		//alert(x); // Creates a dialog box with the value of x
		console.log ("x in sub2 is: ");
		// javscript uses deep binding because x's value in sub2's environment
		// is 1, and this command prints 1
		console.log(x);
	};

	function sub3()
	{
		console.log("sub3");
		var x;
		x = 3;
		console.log("x = 3 in sub3");
		console.log("calling sub4 with params sub2");
		sub4(sub2);
	};

	function sub4(subx)
	{
		console.log("sub4");
		var x;
		x = 4;
		console.log("x = 4 in sub4");
		console.log("calling ...sub[x]");
		subx();
	};

	x = 1;
	console.log("x = 1 in sub1");
	sub3();
};

sub1();

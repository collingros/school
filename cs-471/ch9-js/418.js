function sub1()
{
	console.log("sub1");
	var x;
	function sub2()
	{
		console.log("sub2");
		//alert(x); // Creates a dialog box with the value of x
		console.log(x);
	};

	function sub3()
	{
		console.log("sub3");
		var x;
		x = 3;
		sub4(sub2);
	};

	function sub4(subx)
	{
		console.log("sub4");
		var x;
		x = 4;
		subx();
	};

	x = 1;
	sub3();
};

sub1();

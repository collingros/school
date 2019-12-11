//Name= Elham Hojati
//Lab501 or Lab503
#include "project3.h"


//_________________________________________________________________________
//function for printing a position
void printmove(mov mv) {

		string s = mv.src;
		string d = mv.dst;

		cout << "mov = (" << s << "," << d << ") " << "  " << endl;

	}

//_________________________________________________________________________

//_________________________________________________________________________
//function for comparing two moves
bool compare_moves(mov mv1, mov mv2) {
	bool result;
	string s1, d1, s2, d2;

	s1 = mv1.src;
	d1 = mv1.dst;
	s2 = mv2.src;
	d2 = mv2.dst;
			//cout << s1 << s2 << d1 << d2 << endl;
	if (s1 == s2 && d1 == d2)
			result = true;
	else
			result = false;
	return result;
}
//_________________________________________________________________________

//_________________________________________________________________________
//function for returning the correct answer for the testcase
  mov answer_chooseMove(string s)
{
	mov m;
	if (s == "  WK1h   Bk3f  Wp4h  BK5h  Wb6e  WQ6f  Br8h   ")
	{


		m.src = "6f";
		m.dst = "7g";

	}
	
	return m;
}
//_________________________________________________________________________

//_________________________________________________________________________
//main function 
int main()

{
	int passed = 0;

	vector<string> testcases;
	testcases.push_back("  WK1h   Bk3f  Wp4h  BK5h  Wb6e  WQ6f  Br8h   ");  //general testcase

	mov mv1, mv2;

	for (int i = 0; i < (signed)testcases.size(); ++i) {
		if (i == 0 ) {
			mv1 = chooseMove(readPosition(testcases[i]), 2);
			mv2 = answer_chooseMove(testcases[i]);
		}



		cout << "The result of the chooseMove funcion:  ";
		printmove(mv1);
		cout << "The correct move:   ";
		printmove(mv2);


		if (compare_moves(mv1, mv2)) {
			passed = passed + 1;
			cout << "test case " << i + 1 << " has been passed." << endl;
		}
		else {
			cout << "test case " << i + 1 << " has been  failed.!!!!!!!" << endl;
		}
		cout << "_________________________" << endl;
	}

	cout << "number of passed cases:" << passed << endl;

	system("pause");
	return 0;

}

//_______________________________________________________________________
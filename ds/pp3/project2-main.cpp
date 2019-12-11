//Name= Elham Hojati
//Lab501 or Lab503
#include "project2.h"


//_________________________________________________________________________
//function for printing a position
void printmoves(set<mov> myset) {
	//cout << endl << "Printing Legal Moves: " << endl;
	cout << "{ ";
	for (set<mov>::iterator it = myset.begin(); it != myset.end(); ++it) {
		mov mymov = *it;
		string s = mymov.src;
		string d = mymov.dst;

		cout << "(" << s << "," << d << "), " << "  ";
		
	}
	cout <<" }" << endl;

}
//_________________________________________________________________________

//_________________________________________________________________________
//function for comparing two positions
bool comparelegalmoves(set<mov> mv1, set<mov> mv2) {
	bool result = true;
	if (mv1.size() != mv2.size()) {
		result = false;
		return result;
	}
	mov mymov1, mymov2;
	string s1, d1, s2, d2;
	bool find = false;
	for (set<mov>::iterator it = mv1.begin(); it != mv1.end(); ++it) {
		find = false;
		mymov1 = *it;
		s1 = mymov1.src;
		d1 = mymov1.dst;
		for (set<mov>::iterator it2 = mv2.begin(); it2 != mv2.end(); ++it2) {
			mymov2 = *it2;
			s2 = mymov2.src;
			d2 = mymov2.dst;
			//cout << s1 << s2 << d1 << d2 << endl;
			if (s1 == s2 && d1 == d2)
				find = true;
			     

		}

		if (find==false) {
			result = false;
			return result;
		}
	}
	return result;
}
//_________________________________________________________________________

//_________________________________________________________________________
//function for returning the legal moves of testcases
set<mov> give_testcase_legalMoves(string s)
{
	set<mov> myset;
	mov m;
	if (s == "Wb1a    Wk6h  WK7e   Bp7g  Bp7h    BK8h")
	{


		m.src = "1a";
		m.dst = "2b";
		myset.insert(m);

		m.src = "1a";
		m.dst = "3c";
		myset.insert(m);

		m.src = "1a";
		m.dst = "4d";
		myset.insert(m);

		m.src = "1a";
		m.dst = "5e";
		myset.insert(m);

		m.src = "1a";
		m.dst = "6f";
		myset.insert(m);

		m.src = "1a";
		m.dst = "7g";
		myset.insert(m);

		m.src = "7e";
		m.dst = "8d";
		myset.insert(m);

		m.src = "7e";
		m.dst = "8e";
		myset.insert(m);


		m.src = "7e";
		m.dst = "8f";
		myset.insert(m);


		m.src = "7e";
		m.dst = "7d";
		myset.insert(m);

		m.src = "7e";
		m.dst = "7f";
		myset.insert(m);

		m.src = "7e";
		m.dst = "6d";
		myset.insert(m);

		m.src = "7e";
		m.dst = "6e";
		myset.insert(m);

		m.src = "6h";
		m.dst = "4g";
		myset.insert(m);

		m.src = "6h";
		m.dst = "5f";
		myset.insert(m);

		m.src = "6h";
		m.dst = "7f";
		myset.insert(m);

		m.src = "6h";
		m.dst = "8g";
		myset.insert(m);

	}


	if (s == "BK1d      WK8c    Wr1h    Wr2h" || s=="  WQ1h  WK5f   BK5h  ") {
		cout << "Checkmate Testcase: " << s <<  endl;
		

	}


	if (s == " BK8f  Wp7f  WK6f") {
		cout << "Stalemate Testcase: "  << s << endl;
	}

	if (s == " WK1a   BK8h    Wr5g") {


		m.src = "8h";
		m.dst = "7h";
		myset.insert(m);
	}


	if(s==" WK1a BK8h Wp2b Br3c "){
		
		
		m.src = "1a";
		m.dst = "2a";
		myset.insert(m);

		m.src = "1a";
		m.dst = "1b";
		myset.insert(m);

		m.src = "2b";
		m.dst = "3b";
		myset.insert(m);

		m.src = "2b";
		m.dst = "4b";
		myset.insert(m);

		m.src = "2b";
		m.dst = "3c";
		myset.insert(m);


    }

	return myset;
}
//_________________________________________________________________________

//_________________________________________________________________________
//main function 
int main()

{
	int passed = 0;

	vector<string> testcases;
	testcases.push_back("Wb1a    Wk6h  WK7e   Bp7g  Bp7h    BK8h");  //general testcase
	testcases.push_back("BK1d      WK8c    Wr1h    Wr2h");           //checkmate testcase
	testcases.push_back("  WQ1h  WK5f   BK5h  ");                    //checkmate testcase 
	testcases.push_back(" BK8f  Wp7f  WK6f");                        //stalemate testcase
	testcases.push_back(" WK1a   BK8h    Wr5g");                     //general testcase 
	testcases.push_back(" WK1a BK8h Wp2b Br3c ");                     //general testcase 
	set<mov> mv1, mv2;

	for (int i = 0; i < (signed)testcases.size(); ++i) {
		if (i == 0 || i==5) {
			mv1 = legalMoves(readPosition(testcases[i]), 'W');
		    mv2 = give_testcase_legalMoves(testcases[i]);
		}

		if (i == 1 || i==2 || i==3 || i==4) {
			mv1 = legalMoves(readPosition(testcases[i]), 'B');
			mv2 = give_testcase_legalMoves(testcases[i]);
		}


		cout << "The result for the legalMoves funcion:";
		printmoves(mv1);
		cout << "The correct legal moves:";
		printmoves(mv2);

		
		if (comparelegalmoves(mv1,mv2)) {
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
// Name: Collin Gros
// Lab501
#include "project_1.h"


//_________________________________________________________________________
//function for printing a position
void printposition(position pos) {
	cout << endl << "printing position" << endl;
	for (int i = 0; i < (signed)pos.size(); ++i) {
		for (int j = 0; j < 8; ++j) {
			cout << pos[i][j] << "   ";
		}// 
		cout << endl;
	}
}
//_________________________________________________________________________

//_________________________________________________________________________
//function for comparing two positions
bool compareposition(position pos1, position pos2) {
	bool result = true;
	for (int i = 0; i < (signed)pos1.size(); ++i) {
		for (int j = 0; j < 8; ++j) {
			if (pos1[i][j] != pos2[i][j]) {
				result = false;
				return result;
			}
		}// 

	}
	return result;
}
//_________________________________________________________________________

//_________________________________________________________________________
//function for returning the position of testcases
position give_testcase_position(string s)
{
	row r1(8, "e");
	position p1(8, r1);

	if (s == "WQ4aWp4b      ") {

		p1[3][0] = "WQ";
		p1[3][1] = "Wp";

	}



	if (s == "Wp5aWQ3b Bp2c")
	{
		p1[4][0] = "Wp";
		p1[2][1] = "WQ";
		p1[1][2] = "Bp";
	}
	return p1;
}
//_________________________________________________________________________

//_________________________________________________________________________
//main function 
int main()

{
	vector<string> testcases = { "WQ4aWp4b      ", "Wp5aWQ3b Bp2c", "" };


	for (int i = 0; i < (signed)testcases.size(); ++i) {
		position pos1 = readPosition(testcases[i]);
		position pos2 = give_testcase_position(testcases[i]);
		printposition(pos1);
		printposition(pos2);
		if (compareposition(pos1, pos2) == true) {
			cout << "test case " << i + 1 << " has been passed." << endl;
		}
		if (compareposition(pos1, pos2) == false) {
			cout << "test case " << i + 1 << " has been  failed.!!!!!!!" << endl;
		}
	}



	system("pause");
	return 0;

}

//_________________________________________________________________________

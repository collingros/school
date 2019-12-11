#include <vector>
#include <iostream>


int main()
{
	std::vector<int> v (5, 100);
	v[0] = 0;

	std::cout << "by reference\n";
	int& x = v[0];
	std::cout << "x: " << x << "\n";

	v[0] = 1;
	std::cout << "x: " << x << "\n";

	v[0] = 0;
	std::cout << "\nby value\n";
	int y = v[0];
	std::cout << "y: " << y << "\n";

	v[0] = 1;
	std::cout << "y: " << y << "\n";
}

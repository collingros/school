#include <iostream>
#include <string>

int main()
{
	std::string name;
	std::cout << "What's your name?";
	getline(std::cin, name);
	std::cout << "Hello, " << name << "!\n";
}

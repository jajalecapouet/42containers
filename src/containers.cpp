#include "../includes/Test.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace ft = std;

int main(void)
{
	Test<double>	a(3);
	a[0] = 123;
	a[1] = 444;
	a[2] = 321;
	Test<double>::iterator it;

	it = a.begin();
	std::cout << "a.begin() = " << (*it) << std::endl;
	std::cout << "it[1] = " << it[1] << std::endl;
	it = a.end();
	std::cout << "a.end() = " << (*(it--)) << std::endl;
	std::cout << "a.end() = " << (*it) << std::endl;
	std::cout << "la taille de l'element est " << a.getDif() << std::endl;
}
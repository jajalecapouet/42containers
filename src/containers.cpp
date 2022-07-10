#include "../includes/Test.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace ft = std;

template < typename T >
void	displayInfo( T &container, std::string name )
{
	std::cout << "size " << name << " : " << container.size() << std::endl;
	std::cout << "capacity " << name << " : " << container.capacity() << std::endl;
	std::cout << "max_size " << name << " : " << container.max_size() << std::endl;
}

int main(void)
{

	std::cout << std::endl << "<------- Class Test ------->" << std::endl << std::endl;

	Test<std::string>	a(7, "pouet");
	Test<int>			b(9);
	a[0] = "123";
	a[1] = "444";
	a[2] = "321";
	Test<std::string>::iterator it;

	b[3] = 8;
	b.resize(2);
	b.resize(4);
	b.resize(80);
	displayInfo<Test<int> >(b, "b");
	std::cout << b[30] << std::endl;
	it = a.begin();
	std::cout << "a.begin() = " << (*it) << std::endl;
	std::cout << "it[1] = " << it[1] << std::endl;
	it = a.end();
	std::cout << "a.end() - 1 = " << (*(--it)) << std::endl;
	std::cout << "strlen = " << it->length() << std::endl;
	try
	{
		Test<std::string>	b(it, a.begin());
	}
	catch(const char* &e)
	{
		std::cerr << e << std::endl;
	}
	displayInfo<Test<std::string> >(a, "a");

	std::cout << std::endl << "<------- True vector ------->" << std::endl << std::endl;

	std::vector<int>	v(12, 4);
	displayInfo<std::vector<int> >(v, "v");
	std::vector<int>	w(3, 3);
	w.reserve(30);
	displayInfo<std::vector<int> >(w, "w");
	v = w;
	displayInfo<std::vector<int> >(v, "v");
	std::cout << v.at(4) << std::endl;
}
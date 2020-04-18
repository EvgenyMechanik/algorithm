#include <cpp/polynom.h>
#include <stdlib.h>
#include <exception>
#include <iostream>

int main()
{
	try 
	{
		APolynom ap1(std::initializer_list<Ratio>{ Ratio(1, 1), Ratio(-1, 1), Ratio(1 , 2), Ratio(-1, 6) }); /* 1 - x + (1/2)x^2 - (1/6)x^3 */
		APolynom ap2(std::initializer_list<Ratio>{ Ratio(1, 1), Ratio(1, 1), Ratio(1 , 1), Ratio(1, 1) }); /* 1 + x + x^2 + x^3 */
		std::cout << ap1 << std::endl << ap2 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}	
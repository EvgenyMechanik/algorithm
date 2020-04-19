#include <cpp/polynom.h>
#include <stdlib.h>
#include <exception>
#include <utility>
#include <iostream>

int main()
{
	try 
	{
		/* 1 - x + (1/2)x^2 - (1/6)x^3 */
		APolynom ap1(std::initializer_list<Ratio>{ Ratio(1, 1), Ratio(-1, 1), Ratio(1 , 2), Ratio(-1, 6) }); 
		/* 1 + x + x^2 + x^3 */
		APolynom ap2(std::initializer_list<Ratio>{ Ratio(1, 1), Ratio(1, 1), Ratio(1 , 1), Ratio(1, 1) });
		/* 5 - 3x + 7x^2 + 2x^3 -3x4 + x5 */
		APolynom ap3(std::initializer_list<Ratio>{ Ratio(5, 1), Ratio(-3, 1), Ratio(7 , 1), Ratio(2, 1), Ratio(-3, 1), Ratio(1,1) });
		/* 1 - x + x^2 */
		APolynom ap4(std::initializer_list<Ratio>{ Ratio(1, 1), Ratio(-1, 1), Ratio(1 , 1) });
		/* 5 - 3x + 7x^2 + 2x^3 - 3x4 */
		APolynom ap5(std::initializer_list<Ratio>{ Ratio(5, 1), Ratio(-3, 1), Ratio(7 , 1), Ratio(2, 1), Ratio(-3, 1) });
		/* 1 - x + (1/2)x^2 - (1/6)x^3 */
		LPolynom lp1(std::initializer_list<std::pair<Ratio, int>> { std::pair<Ratio, int>(Ratio(1, 1), 0), std::pair<Ratio, int>(Ratio(-1, 1), 1),
												   std::pair<Ratio, int>(Ratio(1, 2), 2), std::pair<Ratio, int>(Ratio(-1, 6), 3) });
		/* 1 + x + x^2 + x^3 */
		LPolynom lp2(std::initializer_list<std::pair<Ratio, int>> { std::pair<Ratio, int>(Ratio(1, 1), 0), std::pair<Ratio, int>(Ratio(1, 1), 1),
												   std::pair<Ratio, int>(Ratio(1, 1), 2), std::pair<Ratio, int>(Ratio(1, 1), 3) });
		/* 5 - 3x + 7x^2 + 2x^3 -3x4 + x5 */
		LPolynom lp3(std::initializer_list<std::pair<Ratio, int>> { std::pair<Ratio, int>(Ratio(5, 1), 0), std::pair<Ratio, int>(Ratio(-3, 1), 1),
												   std::pair<Ratio, int>(Ratio(7, 1), 2), std::pair<Ratio, int>(Ratio(2, 1), 3), 
												   std::pair<Ratio, int>(Ratio(-3, 1), 4), std::pair<Ratio, int>(Ratio(1, 1), 5) });
		/* 1 - x + x^2 */
		LPolynom lp4(std::initializer_list<std::pair<Ratio, int>> { std::pair<Ratio, int>(Ratio(1, 1), 0), std::pair<Ratio, int>(Ratio(-1, 1), 1),
												   std::pair<Ratio, int>(Ratio(1, 1), 2) });
		/* 5 - 3x + 7x^2 + 2x^3 - 3x4 */
		LPolynom lp5(std::initializer_list<std::pair<Ratio, int>> { std::pair<Ratio, int>(Ratio(5, 1), 0), std::pair<Ratio, int>(Ratio(-3, 1), 1),
												   std::pair<Ratio, int>(Ratio(7, 1), 2), std::pair<Ratio, int>(Ratio(2, 1), 3),
												   std::pair<Ratio, int>(Ratio(-3, 1), 4) });
		APolynom ap6 = ap1 * ap2;
		APolynom ap7 = ap1 / ap2;
		APolynom ap8 = ap3 / ap4;

		std::cout << ap1 << std::endl << ap2 << std::endl << ap3 << std::endl
				  << ap4 << std::endl << ap5 << std::endl << ap1 + ap2 << std::endl
				  << ap1 - ap2 << std::endl << ap1 * ap2 << std::endl
				  << ap1 / ap2 << std::endl << ap3 / ap4 << std::endl
		          << ap3 - ap5 << std::endl << ap5 - ap3 << std::endl;
//		          << (ap1 / ap2).evaluate(0.5) << std::endl << (ap3 / ap4).evaluate(0.5) << std::endl;
		std::cout << std::endl << std::endl;
		std::cout << lp1 << std::endl << lp2 << std::endl << lp3 << std::endl
				  << lp4 << std::endl << lp5 << std::endl << lp1 + lp2 << std::endl
				  << lp1 - lp2 << std::endl << lp1 * lp2 << std::endl
				  << lp1 / lp2 << std::endl << lp3 / lp4 << std::endl
				  << lp3 - lp5 << std::endl << lp5 - lp3 << std::endl;

	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}	
#include <polynom.h>
#include <stdlib.h>
#include <exception>

int main()
{
	try 
	{
		APolynom ap1({ Ratio(1, 1), Ratio(-1, 1), Ratio(1 , 2), Ratio(-1, 6) }, 3) /* 1 - x + (1/2)x^2 - (1/6)x^3 */
		APolynom ap2({ Ratio(1, 1), Ratio(1, 1), Ratio(1 , 1), Ratio(1, 1) }, 3) /* 1 + x + x^2 + x^3 */
		cout << ap1 << endl << ap2 << endl;
	}
	catch(const std::exception& e)
	{
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}	
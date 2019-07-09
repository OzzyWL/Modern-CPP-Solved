#include <./digit_counting.h>

int main(){

	double factor = M_PI;
	// double factor = 0.0033; // example that is NOT working

	double number = pow(10,14);

	std::cout << "Number is: " << std::setprecision(18) << number << std::endl;
	std::cout << "Factor before precision loss is: " << std::setprecision(18) << factor << std::endl;

	double wrapped_res = Warp(number, factor);
	std::cout << "Wrapped result is: " << wrapped_res << std::endl;
    
	// Assuming factor is always smaller than number or equal
	/* TODO: some numbers do not round well for example: 
	double factor = 0.0033 - because use of trunc()
	also need to fix zeros right of decimal point*/
	int sig_digits = CountSameSignificantDigits(number, factor);
	std::cout << "Significant digits between these numbers: " << sig_digits << std::endl;


	// dummy function to test cmake works (exercise 2)
	// std::cout << ReturnTrue() << std::endl;
	return 0;
}

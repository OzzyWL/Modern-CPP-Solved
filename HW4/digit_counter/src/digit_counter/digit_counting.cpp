#include <./digit_counting.h>

// see: https://www.youtube.com/watch?v=BmeImtwhfj8
int CountSameSignificantDigits(double number, double factor){

    double new_number = fabs(number + factor  - number);
    std::cout << "Factor after precision loss is:  " << new_number << std::endl;
    // copy for digits left decimal point
    double new_number2 = new_number;
    double factor2 = factor;

	// get number of digits left decimal point
	int digits_left_of_decimal =0;
	// get number to decimal point
	while (new_number2 >= 1) {
		if (new_number2 > 0){
		new_number2 /= 10.0; // base is 10
		factor2 /= 10.0; // base is 10
        
		// std::cout << "number2 is: " << new_number2 << std::endl;
		// std::cout << "rounded number2 is: " << trunc(new_number2) << std::endl;
		// std::cout << "factor2 is: " << new_number2 << std::endl;
		// std::cout << "rounded factor2 is: " << trunc(factor2) << std::endl;
		
        if  (trunc(factor2) == trunc(new_number2)){
		digits_left_of_decimal++;
		}
		}
	}
		//std::cout << "Digits to left: " << digits_left_of_decimal << std::endl;

    // initilize to 1 as already found digits to left of decimal point
	int digits_right_of_decimal = 0; 
	// get number to decimal point
	while (digits_right_of_decimal < 100 - digits_left_of_decimal ) {
		if (new_number > 0){
		new_number *= 10.0; // base is 10
		factor *= 10.0; // base is 10

		// std::cout << "number is: " << new_number << std::endl;
		// std::cout << "rounded number is: " << trunc(new_number) << std::endl;
		// std::cout << "factor is: " << factor << std::endl;
        // std::cout << "rounded factor is: " << trunc(factor) << std::endl;
		
        // truncate so I can compare to ints and
        // update the significant digits between the 2 numbers
		
        if  (trunc(factor) == trunc(new_number)){
            digits_right_of_decimal++;
		}
        else{
            break;
			}
		}
	}
    //std::cout << "Digits to right: " << digits_right_of_decimal << std::endl;

    return digits_right_of_decimal + digits_left_of_decimal;
}

double Warp(double number, double factor){

return fabs(factor + number - factor);

}

bool ReturnTrue(){

return true;
}

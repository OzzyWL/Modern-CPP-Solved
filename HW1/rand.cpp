// 1) wc -l data.dat 
// 2) grep dolor (OR dalor) data.dat | wc -l 
// 3) wc -w data.dat 
// 4) grep [^a-z]mol* data.dat | wc -l
// 5) find <the full path to test_folder>/test_folder/ -maxdepth 1 -name "*.txt" | wc -l
// 6) 
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	while (true){
		int input_guess;
		cout << "Please enter an integer value from 0 to 99: " <<  endl;
		
		// TODO: FIX so ONLY works for int inputs becaue if you enter char infinite loop
		cin >> input_guess;
		if (input_guess >= 0 && input_guess <= 99){
			cout << "The value you entered is: " << input_guess <<  endl;
		    int rand_num = 1 + std::rand()/((RAND_MAX + 1u) / 99);  // Note: 1+rand()%6 is biased
	        cout << "The random generated number is: "<< rand_num <<  endl;

		    if(input_guess == rand_num)
			{
			cout << "You guessed the number and WON!! :)" << endl;
			break;
			}
			else if(input_guess > rand_num){
			cout << "Your guess is bigger than the number, try again." << endl;

			}
			else if(input_guess < rand_num){
			cout << "Your guess is smaller than the number, try again." << endl;
				}
			}

		else{
			cout << "Input must be an INTEGER!!! value from 0 to 99: " <<  endl;
			}


	}


	return 0;
}

// g++ -std=c++11 -Wall -Wextra -Werror stack_limit.cpp -o output  
#include <iostream>

int main(){

int allocater = 1;

while(true){
    // // 1GB=1024MB, 1MB=1024KB, 1KB=1024 Bytes, 1 Byte=8 Bits
    // // Grow the allocated memory size in steps of 100 Kilobytes
    // no need to multiply by 8 if I allocate arr in double type
    const size_t size = allocater * 100 * 1024; 

    // so each double element in array will contain 8 bits 
    double my_array[size];

    // // After allocating the array do something with its elements 
    // // (like sum them up or alike) to make sure the
    // // allocation is not optimized out by the compiler
    for (uint ii = 0 ;ii < sizeof(my_array) / sizeof(double); ii++ ){
       my_array[ii]  = my_array[ii] + 3.33;
    }

    // output the size of memory in stack used of array
    std::cerr << sizeof(my_array) / 1024 / sizeof(double) << std::endl;
    
    allocater++;

}
   
return 0;

}


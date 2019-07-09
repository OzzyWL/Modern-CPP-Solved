# Modern-CPP-Solved
Exercises from course at http://www.ipb.uni-bonn.de/teaching/modern-cpp/

**Exercises Cover:** Using CMake, some Image Processing, Implementation of a strategy pattern and other topics learned in the videos such as smart pointers and memory leaks. 
I did not implement any of the Google Tests.

Tested on Ubuntu 16.04.5 LTS.

**HW1** - to run through terminal: 
```
1) g++ -std=c++11 -Wall -Wextra -Werror rand.cpp -o output
2) ./output
```
**HW2** and **HW3**:
first need to build from main directory (where data and src directories are located): 
```
1) mkdir build 
2) cd build
3) cmake ..
4) make
5) ../bin/main
```
Check data folder for some results.

**HW4**:
digit_counter and igg_image: same instructions as HW2 and HW3 above.

stack_limit:
```
1) g++ -std=c++11 -Wall -Wextra -Werror stack_limit.cpp -o output
2) ./output
```

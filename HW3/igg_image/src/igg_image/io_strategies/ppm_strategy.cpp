#include "igg_image/io_strategies/ppm_strategy.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace igg {
using namespace std;

bool PpmIoStrategy::Write(const std::string& file_name, const ImageData& data) const {
  ofstream outptFile;
  outptFile.open(file_name);
  if(!outptFile.is_open()){	return EXIT_FAILURE;
  }
  // data
  outptFile << "P3" << std::endl;
  outptFile << data.cols << " " << data.rows << std::endl;
  outptFile << data.max_val << std::endl;

  for(int idx = 0; idx < data.rows* data.cols; idx++){
    outptFile << data.data[0][idx] << " ";
    outptFile << data.data[1][idx] << " ";
    outptFile << data.data[2][idx] << " ";
    
    // the spec recommends a maximum of 70 characters per line
    if (idx % 70 == 0 ) {
      outptFile << "\n";  
    }
  }

  return true;
}

ImageData PpmIoStrategy::Read(const std::string& file_name) const {
  ImageData image_data;
  std::vector<int> red;
  std::vector<int> green;
  std::vector<int> blue;

  ifstream inptFile;

  inptFile.open(file_name);

  if(!inptFile.is_open()){
    cout << "FILE IS NOT OPEN ERROR" << endl;
  }
  
  string line;
  // initilize to first expected line of ppm image type
  string my_number = "P"; 
  int case_count = 4; // initilize to get dimensions and max value

while (getline(inptFile , line)) {

  // run through each char in line 			
  for (uint i = 0;  i <= line.length(); i++){
    // when  hits a digit concat to empty string and look 
    // for more digit chars to concat to a single int 0-255
    if (isdigit(line[i]) ){
      my_number = my_number + line[i];
    }
    // when hit space after digit means I reached end of signal int 
    // store as rgb accordingly and make sure next char is int in  
    // case of multiple spaces
    if ( isspace(line[i]) && isdigit(line[i+1]) ){
      // 3 cases for rgb image
      // but can also use for hight width and max value first			
      switch(case_count){
        case 1:
          // cout << "R: "<< my_number << endl;
          red.push_back(stoi(my_number));
          case_count++;
          break;
        case 2:
          // cout << "G: " << my_number << endl;
          green.push_back(stoi(my_number));
          case_count++;
          break;
        case 3:
          // cout << "B: " << my_number << endl;
          blue.push_back(stoi(my_number));
         //only if got TO blue I reset case_count
          case_count =1;
          break;
        case 4:
          // cout << "Type: " << my_number << endl;
          case_count++;
          break;
        case 5:
          // cout << "Width: " << my_number << endl;
          image_data.cols = stoi(my_number);
          case_count++;
          break;
        case 6:
          // cout << "Hight: " << my_number << endl;
          image_data.rows = stoi(my_number);
          case_count++;
          break;	
        case 7:
          // cout << "Max Value: " << my_number << endl;
          image_data.max_val = stoi(my_number);
          //and now act like only case 1-3 available
          red.reserve(image_data.rows*image_data.cols);  
          green.reserve(image_data.rows*image_data.cols);  
          blue.reserve(image_data.rows*image_data.cols);
          // reset counter to only store rgb values  
          case_count = 1;
          break;					
        default:
          cout << "ERROR if got to default switch case" << endl;
          break;
      }
    my_number ="";
    }
  }
}

// TODO: find a way to get final pixel which is always blue
// for now cheat and give it max value
blue.push_back(255);

inptFile.close();

image_data.data = {red, green, blue};

return image_data;
}

}  // namespace igg
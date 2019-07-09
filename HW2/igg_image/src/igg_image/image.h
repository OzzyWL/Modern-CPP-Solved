#pragma once

// #include "io_tools.h"
#include <vector>
#include <iostream>

namespace igg {

class Image {
 public:
     ///////////////////// Create the public interface here ///////////////////////
	Image();

	Image(const int rows, const int cols);

	//[Vid_3 1:36:48]	
	// Make getters const  
	// Avoid setters (it exposes it to world) and set data in constructor
	// Name getter functions as the private member they return 
	// return a const reference to not copy if a string (big type -not fundamental types)
	int rows() const {return rows_; }
	int cols() const {return cols_; }

	// define all classe's functions
	// const because just extract value
	int at(const int row, const int col) const;
	// with const This is actually a completely different function 
	// non const because I CHANGE extracted value
 	int& at(int const row, int const col); 
	// must be a reference for "image_const.at(col,row) = 255" to work

	bool FillFromPgm(const std::string& file_name) ;
	void WriteToPgm(const std::string& file_name);
	std::vector<float> ComputeHistogram(int bins);
  	void DownScale(int scale);
    	void UpScale(int scale);

 private:
  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<int> data_;
};

}  // namespace igg
